#include "pch.h"

#include "CPlayer_IDLE.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CLogMgr.h"

CPlayer_IDLE::CPlayer_IDLE()
	: m_Animator(nullptr)
	, m_Once(false)
{
}

CPlayer_IDLE::~CPlayer_IDLE()
{
}


void CPlayer_IDLE::Enter()
{
	m_Once=true;
	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	m_Animator = pPlayer->GetAnim();
}

void CPlayer_IDLE::FinalTick()
{
	if (m_Once)
	{
		if (GetName() == L"Player_Idle_LEFT")
			m_Animator->Play(L"IDLE_LEFT", true);
		else
			m_Animator->Play(L"IDLE_RIGHT", true);
	}
	m_Once = false;

	
}

void CPlayer_IDLE::Exit()
{
}