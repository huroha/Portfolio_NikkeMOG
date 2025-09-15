#include "pch.h"
#include "CWeapon_UI.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CPanel_Tex.h"
#include "CEngine.h"
#include "CTexture.h"

CWeapon_UI::CWeapon_UI()
	: m_Texture(nullptr)
	, m_Player(nullptr)
	, m_StartWidth(0)
{

	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
}

CWeapon_UI::~CWeapon_UI()
{
}





void CWeapon_UI::Tick_UI()
{
	if (GetName() == L"Weapon_1")
	{
		CheckWeapon(0);
	}
	else if (GetName() == L"Weapon_2")
	{
		CheckWeapon(1);
	}
	else if (GetName() == L"Weapon_3")
	{
		CheckWeapon(2);
	}
	else if (GetName() == L"Weapon_4")
	{
		CheckWeapon(3);
	}
	else if (GetName() == L"Weapon_5")
	{
		CheckWeapon(4);
	}
	else if (GetName() == L"Weapon_6")
	{
		CheckWeapon(5);
	}
}



void CWeapon_UI::Render_UI()
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
			, width, height, m_Texture->GetDC(), m_StartWidth * width, 0, width, height, blend);

	}
}

void CWeapon_UI::CheckWeapon(UINT _order)
{
	m_StartWidth = UINT(m_Player->GetPlayerInfo().WeaponInfo[_order].WeaponName);
}
