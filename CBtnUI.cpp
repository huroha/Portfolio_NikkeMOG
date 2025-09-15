#include "pch.h"
#include "CBtnUI.h"

#include "Resource.h"
#include "CEngine.h"
#include "CLogMgr.h"
#include "CPanel_Tex.h"


CBtnUI::CBtnUI()
	: m_CallBack(nullptr)
	, m_Inst(nullptr)
	, m_MemFunc(nullptr)
	, m_MemFunc_1(nullptr)
	, m_MemFunc_2(nullptr)
	, m_IsVisible(true)
{
}

CBtnUI::~CBtnUI()
{
}

LRESULT CALLBACK TileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void CBtnUI::LBtnDown()
{

}

void CBtnUI::LBtnClicked()
{

	


	if (GetParentUI())
	{
		CPanel_Tex* pParent = dynamic_cast<CPanel_Tex*>(GetParentUI());
		if (pParent != nullptr)
		{
			m_IsVisible = pParent->GetVisible();
		}
		
	}
	
	if (m_IsVisible)
	{
		LOG(LOG_LEVEL::LOG, L"Lbtn Clicked");
		if (m_CallBack)
		{
			m_CallBack();
		}

		if (m_Inst && m_MemFunc)
		{
			(m_Inst->*m_MemFunc)();
		}

		if (m_Inst && m_MemFunc_1)
		{
			(m_Inst->*m_MemFunc_1)(m_Param1);
		}

	}
	
}



void CBtnUI::Render_UI()
{
	//PEN_TYPE Pen = PEN_TYPE::GREEN;
	//if (IsMouseOn())
	//{
	//	Pen = PEN_TYPE::BLUE;
	//}

	//if (IsLBtnDown())
	//{
	//	Pen = PEN_TYPE::RED;
	//}

	//SELECT_PEN(BackDC, Pen);
	//SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

	//Vec2 vFinalPos = GetFinalPos();
	//Vec2 vScale = GetScale();
	//Rectangle(BackDC, (int)vFinalPos.x, (int)vFinalPos.y
	//	, (int)vFinalPos.x + (int)vScale.x, (int)vFinalPos.y + (int)vScale.y);
}