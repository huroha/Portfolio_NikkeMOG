#include "pch.h"
#include "CAttack_Basic1.h"
#include "CBoss.h"
#include "CSpawner_Indi.h"
#include "CAnimator.h"

CAttack_Basic1::CAttack_Basic1()
	: m_Boss(nullptr)
	, m_CoolTime(0.f)
	, m_RepeatTime(0.f)
	, m_ShootCount(0)
{
}

CAttack_Basic1::~CAttack_Basic1()
{
}


void CAttack_Basic1::Enter()
{
	m_Boss = GetOwner<CBoss>();
	m_CoolTime = 0;
	// 가능하다면 여기에도 에니메이션 모션 다른거 추가..
	m_Boss->GetAnimator()->Play(L"Boss_BasicAttack", true);
}

void CAttack_Basic1::FinalTick()
{
	m_CoolTime += DT;



	if (m_ShootCount > 6)
	{
		GetStateMachine()->ChangeState(L"TraceState_Normal");
	}



	if (m_CoolTime > 0.1f)
	{
		m_Boss->GetMissileSpawner()->BasicAttack_1();
		m_CoolTime = 0;
		m_ShootCount += 1;

	}




	

}

void CAttack_Basic1::Exit()
{
	m_ShootCount = 0;
	m_Boss->GetAnimator()->Play(L"Indivilia_Move", true);
}
