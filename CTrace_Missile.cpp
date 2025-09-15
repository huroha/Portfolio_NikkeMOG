#include "pch.h"
#include "CTrace_Missile.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAssetMgr.h"


CTrace_Missile::CTrace_Missile()
	: m_TargetPlayer(nullptr)
	, m_DetectRange(1200.f)
	, m_RotateSpeed(180.f)
	, m_Speed2(0.f)
	, m_HP(100.f)
{
	m_TargetPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

	// Enemy1 Animator 컴포넌트 추가
	CAnimator* pAnimator = GetAnimator();

	tAnimDesc desc = {};
	desc.AnimName = L"Bose_Trace";
	desc.FPS = 20;
	desc.FrmCount = 4;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Bose_Trace", L"texture\\tracemissile.png");
	desc.SliceSize = Vec2(40.f, 40.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	pAnimator->CreateAnimation(desc);


	pAnimator->Play(L"Bose_Trace", true);

}

CTrace_Missile::CTrace_Missile(const CTrace_Missile& _Other)
	: CBasic_Missile(_Other)
	, m_TargetPlayer(nullptr)
	, m_DetectRange(_Other.m_DetectRange)
	, m_RotateSpeed(_Other.m_RotateSpeed)
	, m_Speed2(_Other.m_Speed2)
	, m_HP(_Other.m_HP)
{
}

CTrace_Missile::~CTrace_Missile()
{
}


void CTrace_Missile::Tick()
{

	if (m_HP < 0 && !IsDead())
	{
		SetDead(true);
		m_HP = 100.f;
	}



	if (m_TargetPlayer)
	{
		Trace();
		m_Speed2 += 500.f * DT;
	}



	CBasic_Missile::Tick();
	


}



void CTrace_Missile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == int(LAYER_TYPE::PLAYER) || _OtherObj->GetLayerType() == int(LAYER_TYPE::PLAYER_PROJECTILE))
	{
		m_HP -= 30.f;
	}
	

}



void CTrace_Missile::Trace()
{
	Vec2 vCurDir = GetVelocity();

	
	vCurDir.Normalize();

	Vec2 vTargetDir = m_TargetPlayer->GetPos() - GetPos();

	if (0.f < vCurDir.x * vTargetDir.y - vCurDir.y * vTargetDir.x)
	{
		vCurDir = RotateDir(vCurDir, m_RotateSpeed * DT);
	}
	else
	{
		vCurDir = RotateDir(vCurDir, -m_RotateSpeed * DT);
	}

	SetVelocitySpeed(vCurDir, m_Speed2);
}
