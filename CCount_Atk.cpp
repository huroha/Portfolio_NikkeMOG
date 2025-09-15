#include "pch.h"
#include "CCount_Atk.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CPanel_Tex.h"

CCount_Atk::CCount_Atk()
	: m_Atk(0)
	, m_StartWidth(0)
{
}

CCount_Atk::~CCount_Atk()
{
}


void CCount_Atk::Tick_UI()
{

	m_Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;

	if (GetName() == L"Atk_ten")
	{
		int Atk = (m_Atk / 10) % 10;
		m_StartWidth = Atk;

	}

	if (GetName() == L"Atk_one")
	{
		int Atk = (m_Atk % 10);
		m_StartWidth = Atk;
	}

}



void CCount_Atk::Render_UI()
{

	CPanel_Tex* pParent = dynamic_cast<CPanel_Tex*>(GetParentUI());
	if (pParent->GetVisible())
	{

		Vec2 vPos = GetFinalPos();
		UINT width = GetTexture()->GetWidth() / 10;
		UINT height = GetTexture()->GetHeight() / 3;


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, GetTexture()->GetDC(), m_StartWidth * width, 0, width, height, blend);
	}
}


