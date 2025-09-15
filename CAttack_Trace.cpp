#include "pch.h"
#include "CAttack_Trace.h"
#include "CBoss.h"
#include "CSpawner_Indi.h"
#include "CAnimator.h"

CAttack_Trace::CAttack_Trace()
	: m_Boss(nullptr)
	, m_CoolTime(0.f)
	, m_ShootCount(0)
	, m_Wait(false)
{
}

CAttack_Trace::~CAttack_Trace()
{
}



void CAttack_Trace::Enter()
{
	m_Boss = GetOwner<CBoss>();
	m_CoolTime = 0;
	m_Wait = true;
	m_Boss->GetAnimator()->Play(L"Boss_BasicAttack", true);
}

void CAttack_Trace::FinalTick()
{

	m_CoolTime += DT;


	if (m_ShootCount > 4)
	{
		m_Wait = false;
		if (m_CoolTime > 1.f)
		{
			GetStateMachine()->ChangeState(L"TraceState_Normal");
		}
	}

	if (m_CoolTime > 0.3f && m_Wait)
	{
		m_Boss->GetMissileSpawner()->TraceAttack();
		m_CoolTime = 0;
		m_ShootCount += 1;

	}



}

void CAttack_Trace::Exit()
{
	m_ShootCount = 0;
	m_Boss->GetAnimator()->Play(L"Indivilia_Move", true);
}
