#include "pch.h"
#include "CAttack_Thunder.h"
#include "CBoss.h"
#include "CAnimator.h"
#include "CSpawner_Indi.h"


CAttack_Thunder::CAttack_Thunder()
{
}

CAttack_Thunder::~CAttack_Thunder()
{
}



void CAttack_Thunder::Enter()
{
	m_Boss = GetOwner<CBoss>();
	m_CoolTime = 0;
	m_Boss->GetAnimator()->Play(L"Boss_BasicAttack", true);
}

void CAttack_Thunder::FinalTick()
{
	m_CoolTime += DT;



	if (m_ShootCount > 8)
	{
		GetStateMachine()->ChangeState(L"TraceState_Normal");
	}



	if (m_CoolTime > 0.3f)
	{
		m_Boss->GetMissileSpawner()->ThunderAttack();
		m_CoolTime = 0;
		m_ShootCount += 1;

	}
}

void CAttack_Thunder::Exit()
{
	m_ShootCount = 0;
	m_Boss->GetAnimator()->Play(L"Indivilia_Move", true);
}
