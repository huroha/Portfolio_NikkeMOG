#include "pch.h"
#include "CIdleState.h"


#include "CEnemy.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	LOG(LOG_LEVEL::WARNING, L"Enter IdleState");
	LOG(LOG_LEVEL::WARNING, L"Enter IdleState");
}

void CIdleState::FinalTick()
{
	// ������ �νĹ��� ���� Player �� �ִ��� Ȯ���Ѵ�.
	CEnemy* pMonster = GetOwner<CEnemy>();

	float DetectRange = pMonster->GetMonsterInfo().DetectRange;

	// DetecteRange ����� ������
	DrawDebugShape(DEBUG_SHAPE::CIRCLE, PEN_TYPE::BLUE, BRUSH_TYPE::HOLLOW
		         , pMonster->GetRenderPos(), Vec2(DetectRange * 2.f, DetectRange * 2.f));


	// ���࿡ �νĹ��� ���� Player �� �־����� �ڽ��� ���¸� TraceState ���·� �����Ѵ�.
	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

	float Distance = pMonster->GetPos().Distance(pPlayer->GetPos());

	if (Distance < DetectRange)
	{
		GetStateMachine()->ChangeState(L"TraceState");
	}
}

void CIdleState::Exit()
{
	LOG(LOG_LEVEL::WARNING, L"Exit IdleState");
	LOG(LOG_LEVEL::WARNING, L"Exit IdleState");
}
