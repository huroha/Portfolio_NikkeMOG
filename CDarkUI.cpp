#include "pch.h"
#include "CDarkUI.h"
#include "CEngine.h"
#include "CTexture.h"

CDarkUI::CDarkUI()
	: m_Texture(nullptr)
	, m_Visible(false)
{


}

CDarkUI::~CDarkUI()
{
}




void CDarkUI::Render_UI()
{
	if (m_Visible)
	{
		HDC dc = CEngine::Get()->GetBackDC();

		Vec2 vPos = GetFinalPos();
		UINT width = m_Texture->GetWidth();
		UINT height = m_Texture->GetHeight();


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, m_Texture->GetDC(), 0, 0, width, height, blend);
	}
}

void CDarkUI::Tick_UI()
{
}
