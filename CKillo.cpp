#include "pch.h"
#include "CKillo.h"
#include "CEngine.h"
#include "CEnemy.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CLevel.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CBoss.h"

CKillo::CKillo()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_DelayDMG(0.f)
	, m_DelayCool(0.1f)
	, m_bDelay(false)
	, m_WeaponAtk(0.f)
{

	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(60.f, 70.f));

	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"Killo_lv0";
	desc.FPS = 10;
	desc.FrmCount = 4;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Skill_Killo1", L"texture\\killo_280_80.png");
	desc.SliceSize = Vec2(70.f, 80.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);


	desc.AnimName = L"Killo_lv5";
	desc.FPS = 15;
	desc.SliceSize = Vec2(90.f, 100.f);
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Skill_Killo2", L"texture\\killo_360_100.png");
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);


	m_Animator->Play(L"Killo_lv0", true);


}

CKillo::~CKillo()
{
}





void CKillo::SetLvMaxAnimation()
{
	m_Animator->Play(L"Killo_lv5",true);
}

void CKillo::Tick()
{

	m_DelayDMG += DT;


	if (m_DelayDMG > m_DelayCool)
	{

		OnOffCollider(m_bDelay);
		m_DelayDMG = 0;

	}

	Vec2 playerPos = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos();
	SetPos(playerPos);


}




void CKillo::Render()
{

	m_Animator->Render();
}



void CKillo::OnOffCollider(bool _trigger)
{
	if (_trigger)
	{
		m_Collider->Activate();
		m_bDelay = false;
	}
	else
	{
		m_Collider->Deactivate();
		m_bDelay = true;
	}


}

void CKillo::SetColliderSize(Vec2 _Size)
{

	m_Collider->SetScale(_Size);
}




void CKillo::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{


	if (_OtherObj->GetName() == L"Boss_Indivilia")
	{
		CBoss* pEnemy = dynamic_cast<CBoss*>(_OtherObj);
		UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
		pEnemy->HPReduce(Atk / 10 + m_WeaponAtk);
		_OwnCollider->ResetOverlapCount();
	}

	else
	{
		CEnemy* pEnemy = dynamic_cast<CEnemy*>(_OtherObj);
		if (pEnemy)
		{
			float Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
			pEnemy->HPReduce(Atk / 10 + m_WeaponAtk);
			_OwnCollider->ResetOverlapCount();
		}
		
	}
}


