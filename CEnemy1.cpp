#include "pch.h"
#include "CEnemy1.h"

#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CLevel.h"

#include "CItem.h"
#include "CAssetMgr.h"
#include "CLogMgr.h"

#include "time.h"
#include "CTimeMgr.h"


#include "CItemSpawner.h"
#include "CEffectSpawner.h"
#include "CSound.h"
#include <random>



CEnemy1::CEnemy1()
	: m_Animator(nullptr)
	, m_Rand(0)
	, m_Seed(0)
	, m_CheckHit(false)
	, m_DmgDelayCount(0)
	, m_Alpha(255.f)
	, m_Time(0.f)
{


	// Enemy1 Animator 컴포넌트 추가
	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"MOVE";
	desc.FPS = 10;
	desc.FrmCount = 4;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Enemy1", L"texture\\Enemy1.png");
	desc.SliceSize = Vec2(64.f, 80.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);	
	m_Animator->CreateAnimation(desc);


	desc.AnimName = L"MOVE2";
	desc.FPS = 10;
	desc.FrmCount = 4;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Enemy2", L"texture\\Enemy2_s.png");
	desc.SliceSize = Vec2(40.f, 44.f);
	m_Animator->CreateAnimation(desc);




	m_Animator->Play(L"MOVE", true);


	// Info 채우기
	SetMonsterInfo(10.f, 10.f, 10.f, 0.f, 100.f, 100.f);


}

CEnemy1::CEnemy1(const CEnemy1& _Other)
	: CEnemy(_Other)
	, m_Animator(nullptr)
	, m_Rand(0)
	, m_Seed(0)
	, m_CheckHit(false)
	, m_DmgDelayCount(0)
	, m_Alpha(255.f)
	, m_Time(0.f)
{
	m_Animator = GetComponent<CAnimator>();
}

CEnemy1::~CEnemy1()
{
}


void CEnemy1::Render()
{
	m_Animator->Render();
}

void CEnemy1::Tick()
{


	CEnemy::Tick();

	

	if (GetMonsterInfo().HP < 1)
	{
		Dead();
	}

	if (GetLifeTime() > 60.f)
	{
		ChangeLifeState();
		InitLifeTime();
	}

	if (m_DmgDelayCount != 0)
	{
		m_Time += DT;
		if (m_Time > 0.3f)
		{
			m_DmgDelayCount = 0;
			m_Time = 0;
			m_Alpha = 255;
			m_CheckHit = false;
		}
	}

	if (m_CheckHit)
	{
		static float dir = 1.f;
		m_Alpha += DT * 2000.f * dir;
		if (m_Alpha >= 255.f)
		{
			m_Alpha = 255.f;
			dir = -1.f;
		}
		else if (m_Alpha < 0.f)
		{
			m_Alpha = 0.f;
			dir = 1.f;
		}
	}


}

void CEnemy1::Dead()
{
	m_Seed += UINT(GetID() + GetPos().x);
	
	if (!IsDead())
	{
		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->SlayCountUp();
		CEffectSpawner* EffectSpawner = dynamic_cast<CEffectSpawner*>(CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::SPAWNER)[11]);
		EffectSpawner->EffectOn(this);
		
		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Death", L"sound\\explosion.wav");

		pBGM->Play();
		pBGM->SetVolume(10.f);

		InitHit();

		if (!CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->IsBossInCount())
		{
			srand(m_Seed);
			int choseItem = rand() % 100;


			if (choseItem < 5)
			{
				m_Rand = 0;
			}
			else if (choseItem >= 5 && choseItem < 40)
			{
				m_Rand = 1;
			}
			else if (choseItem >= 40 && choseItem < 90)
			{
				m_Rand = 2;
			}
			else if (choseItem >= 90 && choseItem < 97)
			{
				m_Rand = 3;
			}
			else if (choseItem >= 97 && choseItem < 100)
			{
				m_Rand = 4;
			}


			CItemSpawner* ItemSpawner = dynamic_cast<CItemSpawner*>(CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::SPAWNER)[0]);
			ItemSpawner->DropItem(m_Rand, this);

		}
		
	}


	// 삭제 대신에 다시 풀피로 부-활
	ChangeLifeState();

}

void CEnemy1::ChangeEnemy()
{
	m_Animator->Play(L"MOVE2", true);
}

void CEnemy1::SetEnemy2Collider()
{

	CCollider* pCollier = GetCollider();
	pCollier->SetScale(Vec2(38.f, 42.f));
}

void CEnemy1::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::PLAYER_PROJECTILE)
	{
		m_CheckHit = true;
		m_DmgDelayCount++;
	}

}

void CEnemy1::Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::PLAYER )
	{

		CRigidBody* pRigid = GetRigidBody();
		Vec2 vDir = (_OtherObj->GetPos() - GetPos());
		vDir.Normalize();
		vDir *= 300.f;
		pRigid->AddVelocity(vDir);
	}

	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::ENEMY)
	{	
		CRigidBody* pRigid = GetRigidBody();
		Vec2 vDir = _OtherObj->GetPos() - GetPos();
		vDir.Normalize();
		vDir *= -400.f;
		pRigid->AddVelocity(vDir);
	}


}

void CEnemy1::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

	//ChangeStop();

}
