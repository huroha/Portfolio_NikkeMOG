#include "pch.h"
#include "CCount_MaxHP.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CPanel_Tex.h"

CCount_MaxHP::CCount_MaxHP()
	: m_MaxHP(0)
	, m_StartWidth(0)
{
	
}

CCount_MaxHP::~CCount_MaxHP()
{
}


void CCount_MaxHP::Tick_UI()
{
	m_MaxHP = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().MaxHP;

	if (GetName() == L"MaxHP_ten")
	{
		int maxHP = (m_MaxHP / 10) % 10;
		m_StartWidth = maxHP;

	}

	if (GetName() == L"MaxHP_hun")
	{
		int maxHP = (m_MaxHP / 100);
		m_StartWidth = maxHP;
	}


}



void CCount_MaxHP::Render_UI()
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

