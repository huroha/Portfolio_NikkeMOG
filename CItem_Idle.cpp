#include "pch.h"
#include "CItem_Idle.h"
#include "CItem.h"

CItem_Idle::CItem_Idle()
	: m_LifeTime(0.f)
{
}

CItem_Idle::~CItem_Idle()
{
}

void CItem_Idle::Enter()
{
	m_LifeTime = 0;

}

void CItem_Idle::FinalTick()
{
	m_LifeTime += DT;
	// ������ �νĹ��� ���� Player �� �ִ��� Ȯ���Ѵ�.
	CItem* pItem = GetOwner<CItem>();

	float DetectRange = pItem->GetDetectRange();

	// DetecteRange ����� ������
	DrawDebugShape(DEBUG_SHAPE::CIRCLE, PEN_TYPE::BLUE, BRUSH_TYPE::HOLLOW
		, pItem->GetRenderPos(), Vec2(DetectRange * 2.f, DetectRange * 2.f));


	// ���࿡ �νĹ��� ���� Player �� �־����� �ڽ��� ���¸� TraceState ���·� �����Ѵ�.
	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

	float Distance = pItem->GetPos().Distance(pPlayer->GetPos());

	if (Distance < DetectRange )
	{

		
		GetStateMachine()->ChangeState(L"MagnetState");
	}
	if (m_LifeTime > 30.f)
	{
		pItem->SetDead(true);
		m_LifeTime = 0;
	}
}

void CItem_Idle::Exit()
{

}
