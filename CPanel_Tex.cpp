#include "pch.h"
#include "CPanel_Tex.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CLogMgr.h"
#include "CLevel_Start.h"


CPanel_Tex::CPanel_Tex()
	: m_Texture(nullptr)
	, m_Visible(true)
	, m_StartWidth(0)
	, m_CutSize(1)
{


}


CPanel_Tex::~CPanel_Tex()
{

}




void CPanel_Tex::Tick_UI()
{

}

void CPanel_Tex::Render_UI()
{

	if (m_Visible)
	{
		HDC dc = CEngine::Get()->GetBackDC();

		Vec2 vPos = GetFinalPos();
		UINT width = m_Texture->GetWidth() / m_CutSize;
		UINT height = m_Texture->GetHeight();


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, m_Texture->GetDC(), m_StartWidth*width, 0, width, height, blend);
	}
}

void CPanel_Tex::BeginHovered()
{
}


