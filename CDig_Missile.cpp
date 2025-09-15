#include "pch.h"
#include "CDig_Missile.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CAssetMgr.h"


CDig_Missile::CDig_Missile()
	: m_Animator(nullptr)
	, m_LifeTime(0.f)
{
	CCollider* pCollider = AddComponent(new CCollider);
	pCollider->SetScale(Vec2(200.f, 300.f));

	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"BOOM";
	desc.FPS = 30;
	desc.FrmCount = 15;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"SendBoom", L"texture\\Dig.png");
	desc.SliceSize = Vec2(200.f, 300.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);

	m_Animator->Play(L"BOOM", false);

}

CDig_Missile::~CDig_Missile()
{
}




void CDig_Missile::Tick()
{
	if (!IsDead())
	{
		m_LifeTime += DT;
	}


	if (m_LifeTime > 0.5f)
	{
		ChangeLifeState();
		m_LifeTime = 0;
		m_Animator->ResetAnim();
	}




}

void CDig_Missile::Render()
{
	m_Animator->Render();

}

void CDig_Missile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::PLAYER)
	{

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
		pPlayer->HPReduce_Dig();
	}

}
