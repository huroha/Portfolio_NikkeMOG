#include "pch.h"
#include "CBoss.h"
#include "CStateMachine.h"
#include "CTrace_Normal.h"
#include "CTrace_Fast.h"
#include "CAttack_Basic1.h"
#include "CAttack_Basic2.h"
#include "CAttack_Trace.h"
#include "CAttack_Thunder.h"


#include "CSpawner_Indi.h"

#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"

#include "CPanel_Tex.h"
#include "CLevel_Start.h"
#include "CPauseMgr.h"
#include "CSound.h"
#include "CDarkUI.h"

CBoss::CBoss()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Info{}
	, m_MissileSpawner(nullptr)
	, m_CheckHit(false)
	, m_DmgDelayCount(0)
	, m_Time(0.f)
	, m_Alpha(255.f)
{
	// 보스 Info 채우기
	m_Info.Atk =35;
	m_Info.Def = 20;
	m_Info.HP = 15000;
	m_Info.Speed = 100.f;


	// 보스 에니메이션
	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"Indivilia_Move";
	desc.FPS = 10;
	desc.FrmCount = 6;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Indi_Move", L"texture\\Indi_Move.png");
	desc.SliceSize = Vec2(300.f, 200.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);



	desc.AnimName = L"Boss_BasicAttack";
	desc.FrmCount = 8;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Indi_BasicAttack", L"texture\\Indi_BasicAttack.png");
	m_Animator->CreateAnimation(desc);


	desc.AnimName = L"Dig_Move_Left";
	desc.FrmCount = 4;
	desc.FPS = 8;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Dig_IndiLeft", L"texture\\DigMove_LEFT.png");
	m_Animator->CreateAnimation(desc);


	desc.AnimName = L"Dig_Move_Right";
	desc.FrmCount = 4;
	desc.FPS = 8;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Dig_IndiRight", L"texture\\DigMove_RIGHT.png");
	m_Animator->CreateAnimation(desc);


	m_Animator->Play(L"Indivilia_Move", true);


	// Collider 
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(300.f, 200.f));

	
	// RigidBody
	m_RigidBody = AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::PLATFOMER);
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxSpeed(150.f);
	m_RigidBody->SetFriction(1000.f);



	// StateMachine
	CStateMachine* pSM = AddComponent(new CStateMachine);
	pSM->AddState(L"TraceState_Normal", new CTrace_Normal);
	pSM->AddState(L"TraceState_Fast", new CTrace_Fast);
	pSM->AddState(L"AttackState_1", new CAttack_Basic1);
	pSM->AddState(L"AttackState_2", new CAttack_Basic2);
	pSM->AddState(L"AttackState_Trace", new CAttack_Trace);
	pSM->AddState(L"AttackState_Thunder", new CAttack_Thunder);
	//pSM->AddState(L"DeadState", new CBoss_Dead);



	pSM->ChangeState(L"TraceState_Normal");




	// 미사일 스포너를 알고있어야 함.
	m_MissileSpawner = dynamic_cast<CSpawner_Indi*>(CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::SPAWNER)[10]);

}

CBoss::~CBoss()
{
}





void CBoss::Tick()
{

	if (m_Info.HP < 1)
	{
		Boss_Dead();
	}

	if (m_DmgDelayCount != 0)
	{
		m_Time += DT;
		if (m_Time > 0.7f)
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

void CBoss::Render()
{

	m_Animator->Render();

}

void CBoss::Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::PLAYER)
	{

		CRigidBody* pRigid = GetRigidBody();
		Vec2 vDir = (_OtherObj->GetPos() - GetPos());
		vDir.Normalize();
		vDir *= 300.f;
		pRigid->AddVelocity(vDir);
	}






}

void CBoss::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::PLAYER_PROJECTILE)
	{
		m_CheckHit = true;
		m_DmgDelayCount++;
	}

}


void CBoss::Boss_Dead()
{
	if (!IsDead())
	{
		//m_Animator->Play(L"Indivilia_Dead", false);

		CLevel_Start* pStart = dynamic_cast<CLevel_Start*>(CLevelMgr::Get()->GetCurrentLevel());
		pStart->GetResultMenu()->ChangeVisibleState();
		pStart->GetDarkFilter()->ChangeVisibleState();

		CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->PlayVoice(PlayerVoice::CLEAR);
		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Clear_BGM", L"sound\\Morning Star.wav");
		pBGM->PlayToBGM();
		pBGM->SetVolume(20.f);


		CPauseMgr::Get()->ChangePauseState();

	}


	// 이거 써도 될거같기도

	ChangeLifeState();

}
