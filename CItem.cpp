#include "pch.h"
#include "CItem.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CTexture.h"

#include "CLogMgr.h"
#include "CStateMachine.h"
#include "CItem_Idle.h"
#include "CItem_Magnet.h"
#include "CItem_Dead.h"

CItem::CItem()
	: m_Texture(nullptr)
	, m_Player(nullptr)
	, m_StartWidth(0)
	, m_DetectRange(120.f)
	, m_DeleteRange(20.f)
	, m_Speed(400.f)
{

	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	CStateMachine* pSM = AddComponent(new CStateMachine);
	pSM->AddState(L"IdleState", new CItem_Idle);
	pSM->AddState(L"MagnetState", new CItem_Magnet);
	pSM->AddState(L"DeadState", new CItem_Dead);

	pSM->ChangeState(L"IdleState");
}

CItem::CItem(const CItem& _Other)
	: CObj(_Other)
	, m_Texture(_Other.m_Texture)
	, m_Player(_Other.m_Player)
	, m_StartWidth(_Other.m_StartWidth)
	, m_DetectRange(_Other.m_DetectRange)
	, m_DeleteRange(_Other.m_DeleteRange)
	, m_Speed(_Other.m_Speed)
{
}

CItem::~CItem()
{
}


void CItem::DeleteAndGainExp()
{
	//DeleteObject(this);
	SetDead(true);
	if (m_Player->GetPlayerInfo().Level < 10)
	{
		m_Player->GainExp(30.f);
	}
	else if (m_Player->GetPlayerInfo().Level >= 10 && m_Player->GetPlayerInfo().Level < 20)
	{
		m_Player->GainExp(10.f);
	}
	else
	{
		m_Player->GainExp(5.f);
	}

}

void CItem::DeleteAndGainExp_2()
{
	SetDead(true);
	if (m_Player->GetPlayerInfo().Level < 10)
	{
		m_Player->GainExp(60.f);
	}
	else if (m_Player->GetPlayerInfo().Level >= 10 && m_Player->GetPlayerInfo().Level < 20)
	{
		m_Player->GainExp(20.f);
	}
	else
	{
		m_Player->GainExp(10.f);
	}

}

void CItem::DeleteAndGainExp_3()
{
	SetDead(true);
	if (m_Player->GetPlayerInfo().Level < 10)
	{
		m_Player->GainExp(120.f);
	}
	else if (m_Player->GetPlayerInfo().Level >= 10 && m_Player->GetPlayerInfo().Level < 20)
	{
		m_Player->GainExp(30.f);
	}
	else
	{
		m_Player->GainExp(20.f);
	}
}

void CItem::DeleteAndGainCoin()
{
	//DeleteObject(this);
	SetDead(true);
	m_Player->CoinCountUp(1);
}

void CItem::DeleteAndGainHP()
{

	SetDead(true);
	m_Player->HPRestore();

}


void CItem::Tick()
{


}

void CItem::Render()
{

	Vec2 vPos = GetRenderPos();
	UINT width = m_Texture->GetWidth() / 7;
	UINT height = m_Texture->GetHeight();


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
		, width, height, m_Texture->GetDC(), width* m_StartWidth, 0, width, height, blend);


}
