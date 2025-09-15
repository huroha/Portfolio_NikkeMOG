#include "pch.h"
#include "CPassive_UI.h"
#include "CPlayer.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CTexture.h"
#include "CPanel_Tex.h"
#include "CEngine.h"

CPassive_UI::CPassive_UI()
	: m_Texture(nullptr)
	, m_Player(nullptr)
	, m_StartWidth(6)
{
	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
}

CPassive_UI::~CPassive_UI()
{
}


void CPassive_UI::Tick_UI()
{
	if (GetName() == L"Passive_1")
	{
		CheckPassive(0);
	}
	else if (GetName() == L"Passive_2")
	{
		CheckPassive(1);
	}
	else if (GetName() == L"Passive_3")
	{
		CheckPassive(2);
	}
	else if (GetName() == L"Passive_4")
	{
		CheckPassive(3);
	}
	else if (GetName() == L"Passive_5")
	{
		CheckPassive(4);
	}
	else if (GetName() == L"Passive_6")
	{
		CheckPassive(5);
	}

}

void CPassive_UI::Render_UI()
{

	CPanel_Tex* pParent = dynamic_cast<CPanel_Tex*>(GetParentUI());
	if (pParent->GetVisible())
	{

		Vec2 vPos = GetFinalPos();
		UINT width = m_Texture->GetWidth() / 7;
		UINT height = m_Texture->GetHeight();


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, m_Texture->GetDC(), m_StartWidth * width,   0, width, height, blend);

	}
}

void CPassive_UI::CheckPassive(UINT _order)
{
	m_StartWidth = UINT(m_Player->GetPlayerInfo().PassiveInfo[_order].PassiveName);
	
}
