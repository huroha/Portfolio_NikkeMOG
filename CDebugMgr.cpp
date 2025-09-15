#include "pch.h"
#include "CDebugMgr.h"

#include "CTimeMgr.h"
#include "CEngine.h"
#include "CKeyMgr.h"

CDebugMgr::CDebugMgr()
	: m_DbgOnOff(false)
{

}

CDebugMgr::~CDebugMgr()
{

}

void CDebugMgr::Tick()
{
	//if (KEY_TAP(KEY::NUM_9))
	//{
	//	m_DbgOnOff ? m_DbgOnOff = false : m_DbgOnOff = true;
	//}


	// ����� �������� �׸� DC �� �����´�(����� DC)
	HDC hBackDC = CEngine::Get()->GetBackDC();

	// ����� ������ �������� ��� �׸������ؼ� �ݺ����� ����.
	list<tDebugShapeInfo>::iterator iter = m_DbgList.begin();
	for ( ; iter != m_DbgList.end(); )
	{
		if (m_DbgOnOff)
		{
			// ����� DC �� ��û�� ���� �����ϰ� �Ѵ�.
			SELECT_PEN(hBackDC, (*iter).Pen);

			// ����� DC �� ��û�� �귯���� �����ϰ� �Ѵ�.
			SELECT_BRUSH(hBackDC, (*iter).BRUSH);


			switch ((*iter).Shape)
			{
			case DEBUG_SHAPE::RECT:
				Rectangle(hBackDC
					, (*iter).Position.x - (*iter).Scale.x / 2.f
					, (*iter).Position.y - (*iter).Scale.y / 2.f
					, (*iter).Position.x + (*iter).Scale.x / 2.f
					, (*iter).Position.y + (*iter).Scale.y / 2.f);
				break;
			case DEBUG_SHAPE::CIRCLE:
				Ellipse(hBackDC
					, (*iter).Position.x - (*iter).Scale.x / 2.f
					, (*iter).Position.y - (*iter).Scale.y / 2.f
					, (*iter).Position.x + (*iter).Scale.x / 2.f
					, (*iter).Position.y + (*iter).Scale.y / 2.f);
				break;
			case DEBUG_SHAPE::CROSS:
				MoveToEx(hBackDC, (*iter).Position.x - (*iter).Scale.x / 2.f, (*iter).Position.y, nullptr);
				LineTo(hBackDC, (*iter).Position.x + (*iter).Scale.x / 2.f, (*iter).Position.y);

				MoveToEx(hBackDC, (*iter).Position.x, (*iter).Position.y - (*iter).Scale.y / 2.f, nullptr);
				LineTo(hBackDC, (*iter).Position.x, (*iter).Position.y + (*iter).Scale.y / 2.f);
				break;
			case DEBUG_SHAPE::LINE:
				MoveToEx(hBackDC, (*iter).Position.x, (*iter).Position.y, nullptr);
				LineTo(hBackDC, (*iter).Scale.x, (*iter).Scale.y);
				break;
			}
		}
		
		// �ð��� üũ�ϴٰ�, DebugShape �����ð��� �ѱ��, ����Ʈ���� ������ �����Ѵ�.
		(*iter).Time += DT;
		if ((*iter).Duration < (*iter).Time)
		{
			iter = m_DbgList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}