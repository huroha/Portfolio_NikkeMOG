#include "pch.h"
#include "CItem_Dead.h"
#include "CItem.h"

#include "CLogMgr.h"
#include "CSound.h"
#include "CAssetMgr.h"

CItem_Dead::CItem_Dead()
{
	
}

CItem_Dead::~CItem_Dead()
{
}



void CItem_Dead::Enter()
{
	CItem* pItem = GetOwner<CItem>();
	if (pItem->GetName() == L"Item_Coin")
	{
		pItem->DeleteAndGainCoin();
		GetStateMachine()->ChangeState(L"IdleState");
	}
	else if (pItem->GetName() == L"Item_Exp")
	{
		pItem->DeleteAndGainExp();
		GetStateMachine()->ChangeState(L"IdleState");
	}
	else if (pItem->GetName() == L"Item_HP")
	{
		pItem->DeleteAndGainHP();
		GetStateMachine()->ChangeState(L"IdleState");
	}

	else if (pItem->GetName() == L"Item_Exp2")
	{
		pItem->DeleteAndGainExp_2();
		GetStateMachine()->ChangeState(L"IdleState");
	}
	else if (pItem->GetName() == L"Item_Exp3")
	{
		pItem->DeleteAndGainExp_3();
		GetStateMachine()->ChangeState(L"IdleState");
	}



	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Item", L"sound\\coin.wav");
	pBGM->Play();
	pBGM->SetVolume(4.f);

}

void CItem_Dead::FinalTick()
{
}

void CItem_Dead::Exit()
{
}
