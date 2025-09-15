#include "pch.h"
#include "CTrace_Fast.h"
#include "CBoss.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CSpawner_Indi.h"


CTrace_Fast::CTrace_Fast()
	: m_Boss(nullptr)
	, m_DigAttackRange(0.f)
{
	m_DigAttackRange = 150.f;
	
}

CTrace_Fast::~CTrace_Fast()
{
}



void CTrace_Fast::Enter()
{
	m_Boss = GetOwner<CBoss>();
	CRigidBody* Rigid = m_Boss->GetRigidBody();
	Rigid->SetMaxSpeed(500.f);

	m_Boss->SetTrace(true);

	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	Vec2 vDir = pPlayer->GetPos() - m_Boss->GetPos();
	if (vDir.x > 0)
		m_Boss->GetAnimator()->Play(L"Dig_Move_Right",true);
	else
		m_Boss->GetAnimator()->Play(L"Dig_Move_Left", true);
}

void CTrace_Fast::FinalTick()
{
	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	Vec2 vDir = pPlayer->GetPos() - m_Boss->GetPos();

	float Distance = vDir.Length();
	vDir.Normalize();


	CRigidBody* Rigid = m_Boss->GetRigidBody();
	Rigid->AddVelocity(vDir * 500.f);
	
	// Enemy Projectile 스포너한테 하나 만들라고 해야겠다.

	if (m_DigAttackRange > Distance)
	{
		LOG(LOG_LEVEL::LOG, L"일반으로 전환");
		GetStateMachine()->ChangeState(L"TraceState_Normal");
		m_Boss->GetMissileSpawner()->DigAttack();

	}


}

void CTrace_Fast::Exit()
{
	CRigidBody* Rigid = m_Boss->GetRigidBody();
	Rigid->SetMaxSpeed(150.f);
	m_Boss->GetAnimator()->Play(L"Indivilia_Move", true);
	m_Boss->SetTrace(false);

}
