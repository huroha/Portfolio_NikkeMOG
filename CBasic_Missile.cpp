#include "pch.h"
#include "CBasic_Missile.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAssetMgr.h"


CBasic_Missile::CBasic_Missile()
	: m_Animator(nullptr)
	, m_LifeTime(0.f)
	, m_Velocity(0.f,0.f)
	, m_Speed(0.f)
{

	CCollider* pCollider = AddComponent(new CCollider);
	pCollider->SetScale(Vec2(30.f, 30.f));

	// Enemy1 Animator ÄÄÆ÷³ÍÆ® Ãß°¡
	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"Bose_Basic";
	desc.FPS = 10;
	desc.FrmCount = 4;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Bose_Basic", L"texture\\boss_missile.png");
	desc.SliceSize = Vec2(40.f, 40.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);


	m_Animator->Play(L"Bose_Basic", true);


}

CBasic_Missile::~CBasic_Missile()
{

}



void CBasic_Missile::CheckVelocity()
{
	Vec2 vDir = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos() - GetPos();
	vDir.Normalize();
	m_Velocity = vDir * m_Speed;

}



void CBasic_Missile::Tick()
{

	Vec2 vPos = GetPos();

	vPos += m_Velocity * DT;

	SetPos(vPos);

	m_LifeTime += DT;

	if (m_LifeTime > 3.f)
	{

		SetDead(true);
		m_LifeTime = 0;
	}


}

void CBasic_Missile::Render()
{
	m_Animator->Render();
}
