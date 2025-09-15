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
		// Trace ������ ���͸� �˾Ƴ���.
		CEnemy* pEnemy = GetOwner<CEnemy>();

		// Player �� �����Ѵ�.
		CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

		Vec2 vDir = pPlayer->GetPos() - pEnemy->GetPos();
		vDir.Normalize();

		
		Vec2 vPos = pEnemy->GetPos() + vDir * pEnemy->GetMonsterInfo().Speed * DT;
		pEnemy->SetPos(vPos);

		// ���� Player �� Ž������ �̻����� �־����� 
		// or ������ ������ ���ķ� �����ð��� ���� ���
		// or �ʱ���ġ���� �����Ÿ� �̻� �߰��Ѱ��
		float Distance = pEnemy->GetPos().Distance(pPlayer->GetPos());
		if (pEnemy->GetMonsterInfo().DetectRange < Distance)
		{
			m_Return = true;
		}
	}

	else
	{
		// ���� ��ġ�� ���ư���.
		CEnemy* pEnemy = GetOwner<CEnemy>();
		Vec2 vDir = m_InitPos - pEnemy->GetPos();
		vDir.Normalize();
		Vec2 vNewPos = pEnemy->GetPos() + vDir * pEnemy->GetMonsterInfo().Speed * 2.f * DT;
		pEnemy->SetPos(vNewPos);

		// �ʱ���ġ�� ������ �ǵ��ƿ��� IdleState �� ����
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