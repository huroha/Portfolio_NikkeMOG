#include "pch.h"
#include "CCount_UI.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPanel_Tex.h"

CCount_UI::CCount_UI()
	: m_Texture(nullptr)
	, m_Player(nullptr)
	, m_StartHeight(0)
	, m_StartWidth(0)
	, vStartPosx(0.f)
	, vStartPosy(0.f)
	, m_Visible(false)
{
	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
}

CCount_UI::~CCount_UI()
{
}




void CCount_UI::SetTextColor(UINT _num)
{
	if (_num == 1)
		m_StartHeight = 1;
	else
		m_StartHeight = 2;
}

void CCount_UI::Tick_UI()
{
	UINT coin = m_Player->GetPlayerInfo().Coin;
	UINT slay = m_Player->GetPlayerInfo().SlayCount;


	if (GetName() == L"Coin_one")
	{

		// 1의 자리만
		if (coin < 10)
		{
			m_Visible = true;
			m_StartWidth = coin % 10;
			SetPos(Vec2(-70.f+vStartPosx,7.f+ vStartPosy));

		}
		// 십의자리
		else if (coin < 100)
		{
			m_StartWidth = coin % 10;
			SetPos(Vec2(-62.f + vStartPosx, 7.f + vStartPosy));
		}
		// 백의자리
		else if (coin < 1000)
		{
			m_StartWidth = coin % 10;
			SetPos(Vec2(-54.f + vStartPosx, 7.f + vStartPosy));
		}
		else
		{
			m_StartWidth = coin % 10;
			SetPos(Vec2(-46.f + vStartPosx, 7.f + vStartPosy));
		}
	}
	else if (GetName() == L"Coin_ten")
	{

		if (coin < 10)
		{
			m_Visible = false;
		}

		// 십의자리
		if ( 9 < coin && coin < 100)
		{
			m_Visible = true;
			m_StartWidth = coin / 10;
			SetPos(Vec2(-70.f + vStartPosx, 7.f + vStartPosy));
		}
		// 백의자리
		else if (coin > 99 && coin <=999)
		{
			m_Visible = true;
			m_StartWidth = (coin / 10) % 10;
			SetPos(Vec2(-62.f + vStartPosx, 7.f + vStartPosy));
		}
		else if (coin > 999)
		{
			m_StartWidth = (coin / 10) % 10;
			SetPos(Vec2(-54.f + vStartPosx, 7.f + vStartPosy));
		}
	}
	else if (GetName() == L"Coin_hun")
	{

		if (coin < 100)
		{
			m_Visible = false;
		}
		if (coin > 99 && coin <= 999)
		{

			m_Visible = true;
			m_StartWidth = coin / 100;
			SetPos(Vec2(-70.f + vStartPosx, 7.f + vStartPosy));
		}
		else if (coin > 999)
		{
			m_StartWidth = (coin / 100) % 10;
			SetPos(Vec2(-62.f + vStartPosx, 7.f + vStartPosy));
		}
	}

	else if (GetName() == L"Coin_chun")
	{
		if (coin < 1000)
		{
			m_Visible = false;
		}
		if (coin > 999)
		{
			m_Visible = true;
			m_StartWidth = coin / 1000;
			SetPos(Vec2(-70.f + vStartPosx, 7.f + vStartPosy));
		}
	}




	if (GetName() == L"Slay_one")
	{

		// 1의 자리만
		if (slay < 10)
		{
			m_Visible = true;
			m_StartWidth = slay % 10;
			SetPos(Vec2(-8.f + vStartPosx, 7.f + vStartPosy));

		}
		// 십의자리
		else if (slay < 100)
		{
			m_StartWidth = slay % 10;
			SetPos(Vec2(0.f + vStartPosx, 7.f + vStartPosy));
		}
		// 백의자리
		else if (slay <1000)
		{
			m_StartWidth = slay % 10;
			SetPos(Vec2(8.f + vStartPosx, 7.f + vStartPosy));
		}
		else
		{
			m_StartWidth = slay % 10;
			SetPos(Vec2(16.f + vStartPosx, 7.f + vStartPosy));
		}
	}
	else if (GetName() == L"Slay_ten")
	{

		// 십의자리
		if (9 < slay && slay < 100)
		{
			m_Visible = true;
			m_StartWidth = slay / 10;
			SetPos(Vec2(-8.f + vStartPosx, 7.f + vStartPosy));
		}
		// 백의자리
		else if (slay > 99 && slay <1000)
		{
			m_Visible = true;
			m_StartWidth = (slay / 10) % 10;
			SetPos(Vec2(0.f + vStartPosx, 7.f + vStartPosy));
		}
		else if (slay > 999)
		{
			m_StartWidth = (slay / 10) % 10;
			SetPos(Vec2(8.f + vStartPosx, 7.f + vStartPosy));
		}
	}
	else if (GetName() == L"Slay_hun")
	{
		if (slay > 99 && slay <1000)
		{
			m_Visible = true;
			m_StartWidth = slay / 100;
			SetPos(Vec2(-8.f + vStartPosx, 7.f + vStartPosy));
		}
		else if (slay > 999)
		{
			m_StartWidth = (slay / 100) % 10;
			SetPos(Vec2(0.f + vStartPosx, 7.f + vStartPosy));
		}
	}
	else if (GetName() == L"Slay_chun")
	{
		if (slay > 999)
		{
			m_Visible = true;
			m_StartWidth = slay / 1000;
			SetPos(Vec2(-8.f + vStartPosx, 7.f + vStartPosy));
		}
	}


}



void CCount_UI::Render_UI()
{
	CPanel_Tex* pParent = dynamic_cast<CPanel_Tex*>(GetParentUI());
	if (pParent->GetVisible())
	{

		if (m_Visible)
		{

			Vec2 vPos = GetFinalPos();
			UINT width = m_Texture->GetWidth() / 10;
			UINT height = m_Texture->GetHeight() / 3;


			BLENDFUNCTION blend = {};
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
				, width, height, m_Texture->GetDC(), m_StartWidth * width, m_StartHeight * height, width, height, blend);

		}

	}

	
}
