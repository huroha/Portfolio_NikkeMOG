#include "pch.h"
#include "CItem_Magnet.h"
#include "CItem.h"

CItem_Magnet::CItem_Magnet()
	: m_TurnDead(false)
{
}


CItem_Magnet::~CItem_Magnet()
{
}


void CItem_Magnet::Enter()
{
	//LOG(LOG_LEVEL::LOG, L"Magnet State Enter");
}


void CItem_Magnet::FinalTick()
{
	if (false == m_TurnDead)
	{
		// Trace 상태의 몬스터를 알아낸다.
		CItem* pItem = GetOwner<CItem>();
		// Player 를 추적한다.
		CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

		Vec2 vDir = pPlayer->GetPos() - pItem->GetPos();
		vDir.Normalize();

		Vec2 vPos = pItem->GetPos() + vDir * pItem->GetSpeed() * DT;
		pItem->SetPos(vPos);


		// DetecteRange 디버그 렌더링
		DrawDebugShape(DEBUG_SHAPE::CIRCLE, PEN_TYPE::BLUE, BRUSH_TYPE::HOLLOW
			, pItem->GetRenderPos(), Vec2(pItem->GetDetectRange() * 2.f, pItem->GetDetectRange() * 2.f));


		float Distance = pItem->GetPos().Distance(pPlayer->GetPos());
		if (pItem->GetDeleteRange() > Distance)
		{
			m_TurnDead = true;
		}

		if (Distance > pItem->GetDetectRange())
		{
			GetStateMachine()->ChangeState(L"IdleState");
		}
	}

	else
	{
		GetStateMachine()->ChangeState(L"DeadState");
		m_TurnDead = false;
	}


}



void CItem_Magnet::Exit()
{
}

