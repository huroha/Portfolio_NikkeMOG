#include "pch.h"
#include "CUI.h"

#include "CEngine.h"
#include "CKeyMgr.h"

CUI::CUI()
	: m_Parent(nullptr)
	, m_MouseOn(false)
	, m_MouseOn_Prev(false)
	, m_LbtnDown(false)
{
}

CUI::CUI(const CUI& _Other)
	: CObj(_Other)
	, m_Parent(nullptr)
	, m_MouseOn(false)
	, m_MouseOn_Prev(false)
	, m_LbtnDown(false)
{
	for (size_t i = 0; i < _Other.m_vecChild.size(); ++i)
	{
		AddChildUI(_Other.m_vecChild[i]->Clone());		
	}
}

CUI::~CUI()
{
	Release_Vector(m_vecChild);
}

void CUI::Tick()
{
	// ���� ��ġ ���
	m_FinalPos = GetPos();

	if (m_Parent)
	{
		m_FinalPos += m_Parent->GetFinalPos();
	}

	// ���콺 üũ
	MouseOnCheck();

	// UI Tick
	Tick_UI();

	// �ڽ� UI Tick
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Tick();
	}
}

void CUI::Render()
{
	// UI ������ Render
	Render_UI();

	// �ڽ� UI �� Render
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Render();
	}
}


void CUI::Render_UI()
{
	PEN_TYPE Pen = PEN_TYPE::GREEN;
	if (m_MouseOn)
	{
		Pen = PEN_TYPE::BLUE;
	}

	if (m_LbtnDown)
	{
		Pen = PEN_TYPE::RED;
	}

	SELECT_PEN(BackDC, Pen);
	SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

	Vec2 vScale = GetScale();
	Rectangle(BackDC, (int)m_FinalPos.x, (int)m_FinalPos.y
		, (int)m_FinalPos.x + (int)vScale.x, (int)m_FinalPos.y + (int)vScale.y);
}

void CUI::MouseOnCheck()
{
	// ���콺�� UI ���� �ö���ִ��� Ȯ���Ѵ�.
	m_MouseOn_Prev = m_MouseOn;

	Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();	
	Vec2 vScale = GetScale();

	if (m_FinalPos.x <= vMousePos.x && vMousePos.x <= m_FinalPos.x + vScale.x
		&& m_FinalPos.y <= vMousePos.y && vMousePos.y <= m_FinalPos.y + vScale.y)
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}
}
