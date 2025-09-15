#include "pch.h"
#include "CCount_Def.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CPanel_Tex.h"


CCount_Def::CCount_Def()
	: m_Def(0)
	, m_StartWidth(0)
{
}

CCount_Def::~CCount_Def()
{
}


void CCount_Def::Tick_UI()
{

	m_Def = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Def;

	if (GetName() == L"Def_ten")
	{

		int Def = (m_Def / 10) % 10;
		m_StartWidth = Def;
	}


	if (GetName() == L"Def_one")
	{
		int Def = (m_Def % 10);
		m_StartWidth = Def;
	}
}

void CCount_Def::Render_UI()
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
