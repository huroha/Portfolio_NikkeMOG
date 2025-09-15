#include "pch.h"
#include "CUIMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_PreventFrame(0)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Tick()
{
	if (m_PreventFrame)
	{
		--m_PreventFrame;
		return;
	}

	// ���콺 ���ʹ�ư�� ���¸� üũ�Ѵ�.
	KEY_STATE LbtnState = CKeyMgr::Get()->GetKeyState(KEY::LBTN);

	// ���� ������ Ȯ��
	CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();

	// UI Layer �� �����´�
	vector<CObj*>& vecUI = pCurLevel->GetLayer(LAYER_TYPE::UI);
	
	vector<CObj*>::reverse_iterator iter = vecUI.rbegin();

	for (; iter != vecUI.rend(); ++iter)
	{
		// �θ� UI Ȯ��
		CUI* pUI = dynamic_cast<CUI*>((*iter));
		assert(pUI);

		// �θ�UI �� �Է��ؼ� ���� �̺�Ʈ�� ������ �켱���� UI �� �˾Ƴ�
		CUI* pPriorityUI = GetPriorityUI(pUI);
		if (nullptr == pPriorityUI)
		{
			StatusCheck(pUI);
			continue;
		}
									
		if (LbtnState == KEY_STATE::TAP)
		{
			pPriorityUI->m_LbtnDown = true;
			pPriorityUI->LBtnDown();

			// ���Ϳ��� ���� �ڷ� ������.
			vecUI.erase((iter + 1).base());
			vecUI.push_back(pUI);

			break;
		}

		if (LbtnState == KEY_STATE::RELEASED)
		{
			pPriorityUI->LBtnUp();
			if (pPriorityUI->m_LbtnDown)
			{
				pPriorityUI->LBtnClicked();
			}
			StatusCheck(pUI);			
		}

		StatusCheck(pUI);
		break;
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _ParentUI)
{
	// ���콺 ���ʹ�ư�� ���¸� üũ�Ѵ�.
	KEY_STATE LbtnState = CKeyMgr::Get()->GetKeyState(KEY::LBTN);

	// ��ȯ��ų �켱���� UI ������
	CUI* pPriorityUI = nullptr;

	static list<CUI*> queue;
	queue.clear();

	// �ֻ��� �θ�UI �Է�
	queue.push_back(_ParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		// ���콺�� �ش� UI ���� �־����� PriorityUI �� �����Ѵ�.
		if (pUI->m_MouseOn)
		{
			pPriorityUI = pUI;
		}
		
		// ���콺 On ���� �̺�Ʈ
		if (false == pUI->m_MouseOn_Prev && pUI->m_MouseOn)
			pUI->BeginHovered();
		else if (pUI->m_MouseOn_Prev && pUI->m_MouseOn)
			pUI->OnHovered();
		else if (pUI->m_MouseOn_Prev && !pUI->m_MouseOn)
			pUI->EndHovered();

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	return pPriorityUI;
}

void CUIMgr::StatusCheck(CUI* _ParentUI)
{
	// ���콺 ���ʹ�ư�� ���¸� üũ�Ѵ�.
	KEY_STATE LbtnState = CKeyMgr::Get()->GetKeyState(KEY::LBTN);

	static list<CUI*> queue;
	queue.clear();

	// �ֻ��� �θ�UI �Է�
	queue.push_back(_ParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}

		// ���ʹ�ư�� ������ ���¸�, ��� UI ���� �������¸� false �� �����Ѵ�.
		if (LbtnState == KEY_STATE::RELEASED)
		{
			pUI->m_LbtnDown = false;
		}
	}
}