#include "pch.h"
#include "CLevel_UI.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

CLevel_UI::CLevel_UI()
	: m_Texture(nullptr)
	, m_StartWidth(0)
	, m_StartHeight(0)
{
}

CLevel_UI::~CLevel_UI()
{
}


void CLevel_UI::SetLevelTex()
{

	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	
	UINT level = pPlayer->GetPlayerInfo().Level;

	if (GetName() == L"Level_UI_ten")
	{
		m_StartWidth = level / 10;
		m_StartHeight = 2;
	}
	else
	{
		m_StartWidth = level % 10;
		m_StartHeight = 0;
	}


}

void CLevel_UI::Tick_UI()
{

	SetLevelTex();


}

void CLevel_UI::Render_UI()
{
	HDC dc = CEngine::Get()->GetBackDC();

	Vec2 vPos = GetFinalPos();
	UINT width = m_Texture->GetWidth() / 10;
	UINT height = m_Texture->GetHeight();


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC, (int)vPos.x - width / 2 , (int)vPos.y - height / 2
		, width, height, m_Texture->GetDC(), width *m_StartWidth, 0, width, height, blend);

	// GetDC() 다음의 0, 0 이 시작지점이다. 이거 조정하면 될듯.
}




