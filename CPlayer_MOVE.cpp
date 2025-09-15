#include "pch.h"

#include "CPlayer_MOVE.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CLogMgr.h"

CPlayer_MOVE::CPlayer_MOVE()
	: m_Animator(nullptr)
	, m_Once(false)
{
}

CPlayer_MOVE::~CPlayer_MOVE()
{
}


void CPlayer_MOVE::Enter()
{
	m_Once = true;
	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	m_Animator = pPlayer->GetAnim();
}

void CPlayer_MOVE::FinalTick()
{
	if (m_Once)
	{
		if (GetName() == L"Player_Move_LEFT")
			m_Animator->Play(L"MOVE_LEFT", true);
		else
			m_Animator->Play(L"MOVE_RIGHT", true);
	}
	m_Once = false;


}

void CPlayer_MOVE::Exit()
{
}