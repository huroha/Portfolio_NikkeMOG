#include "pch.h"
#include "CBtnUI_Tex.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CPanel_Tex.h"

CBtnUI_Tex::CBtnUI_Tex()
	: m_NormalImg(nullptr)
	, m_StartWidth(0)
	, m_StartHeight(0)
	, m_SizeW(1)
	, m_SizeH(1)
	, m_Visible(true)
	, m_ChangeWidth(false)
{


}

CBtnUI_Tex::~CBtnUI_Tex()
{
}





void CBtnUI_Tex::Tick_UI()
{

		CPanel_Tex* pParent = dynamic_cast<CPanel_Tex*>(GetParentUI());
		m_Visible = pParent->GetVisible();

}




void CBtnUI_Tex::Render_UI()
{

	if (m_Visible)
	{



		HDC dc = CEngine::Get()->GetBackDC();

		Vec2 vPos = GetFinalPos();
		UINT width = m_NormalImg->GetWidth() / m_SizeW;
		UINT height = m_NormalImg->GetHeight() / m_SizeH;


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC, (int)vPos.x, (int)vPos.y
			, width, height, m_NormalImg->GetDC(), width * m_StartWidth, height * m_StartHeight, width, height, blend);


		/*PEN_TYPE Pen = PEN_TYPE::GREEN;


		if (IsMouseOn())
		{
			Pen = PEN_TYPE::BLUE;
			
		}
		else {
			if(m_ChangeWidth)
				m_StartWidth = 0;
		}

		if (IsLBtnDown())
		{
			if (m_ChangeWidth)
				m_StartWidth = 1;
			Pen = PEN_TYPE::RED;
		}

		SELECT_PEN(BackDC, Pen);
		SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

		Vec2 vFinalPos = GetFinalPos();
		Vec2 vScale = Vec2(width, height);
		Rectangle(BackDC, (int)vFinalPos.x, (int)vFinalPos.y
			, (int)vFinalPos.x + (int)vScale.x, (int)vFinalPos.y + (int)vScale.y);*/

	}

}





