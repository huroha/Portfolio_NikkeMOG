#include "pch.h"
#include "CAttack_Basic2.h"
#include "CBoss.h"
#include "CSpawner_Indi.h"
#include "CAnimator.h"

CAttack_Basic2::CAttack_Basic2()
	: m_Boss(nullptr)
	, m_CoolTime(0.f)
	, m_ShootCount(0)
	, m_Wait(true)
{
}

CAttack_Basic2::~CAttack_Basic2()
{
}





void CAttack_Basic2::Enter()
{
	m_Boss = GetOwner<CBoss>();
	m_CoolTime = 0;
	m_Wait = true;
	m_Boss->GetAnimator()->Play(L"Boss_BasicAttack", true);
}

void CAttack_Basic2::FinalTick()
{
	m_CoolTime += DT;


	if (m_ShootCount > 29)
	{
		m_Wait = false;
		if (m_CoolTime > 1.f)
		{
			GetStateMachine()->ChangeState(L"TraceState_Normal");
		}
	}


	if (m_CoolTime > 0.01f && m_Wait)
	{
		m_Boss->GetMissileSpawner()->BasicAttack_2();
		m_CoolTime = 0;
		m_ShootCount += 1;
	}

}

void CAttack_Basic2::Exit()
{
	m_ShootCount = 0;
	m_Boss->GetAnimator()->Play(L"Indivilia_Move", true);
}
