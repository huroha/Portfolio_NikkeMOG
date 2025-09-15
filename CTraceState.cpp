#include "pch.h"
#include "CTraceState.h"

#include "CEnemy.h"

CTraceState::CTraceState()
	: m_Return(false)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	LOG(LOG_LEVEL::WARNING, L"Enter TraceState");
	LOG(LOG_LEVEL::WARNING, L"Enter TraceState");

	CEnemy* pEnemy = GetOwner<CEnemy>();
	m_InitPos = pEnemy->GetPos();
}

void CTraceState::FinalTick()
{
	if (false == m_Return)
	{
		// Trace 상태의 몬스터를 알아낸다.
		CEnemy* pEnemy = GetOwner<CEnemy>();

		// Player 를 추적한다.
		CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

		Vec2 vDir = pPlayer->GetPos() - pEnemy->GetPos();
		vDir.Normalize();

		
		Vec2 vPos = pEnemy->GetPos() + vDir * pEnemy->GetMonsterInfo().Speed * DT;
		pEnemy->SetPos(vPos);

		// 만약 Player 가 탐지범위 이상으로 멀어지면 
		// or 추적을 시작한 이후로 일정시간이 지난 경우
		// or 초기위치에서 일정거리 이상 추격한경우
		float Distance = pEnemy->GetPos().Distance(pPlayer->GetPos());
		if (pEnemy->GetMonsterInfo().DetectRange < Distance)
		{
			m_Return = true;
		}
	}

	else
	{
		// 원래 위치로 돌아간다.
		CEnemy* pEnemy = GetOwner<CEnemy>();
		Vec2 vDir = m_InitPos - pEnemy->GetPos();
		vDir.Normalize();
		Vec2 vNewPos = pEnemy->GetPos() + vDir * pEnemy->GetMonsterInfo().Speed * 2.f * DT;
		pEnemy->SetPos(vNewPos);

		// 초기위치로 완전히 되돌아오면 IdleState 로 변경
		if (pEnemy->GetPos().Distance(m_InitPos) < 0.1f)
		{
			pEnemy->SetPos(m_InitPos);
			GetStateMachine()->ChangeState(L"IdleState");
		}
	}
}

void CTraceState::Exit()
{
	LOG(LOG_LEVEL::WARNING, L"Exit TraceState");
	LOG(LOG_LEVEL::WARNING, L"Exit TraceState");
	m_Return = false;
}