#include "pch.h"
#include "CEffect_Dead.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CEngine.h"


CEffect_Dead::CEffect_Dead()
	: m_Animator(nullptr)
	, m_Texture(nullptr)
	, m_LifeTime(0.f)
	, m_LimitTime(1.f)
{
	m_Animator = AddComponent(new CAnimator);



	tAnimDesc desc = {};
	desc.AnimName = L"Enemy_Dead";
	desc.FPS = 9;
	desc.FrmCount = 9;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Enemy_Dead_Effect", L"texture\\Death_effect.png");
	desc.SliceSize = Vec2(100.f, 100.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);




	desc.AnimName = L"Enemy_Dead_Tail";
	desc.FPS = 30;
	desc.FrmCount = 25;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Enemy_Dead_Tail", L"texture\\TailExplosion.png");
	desc.SliceSize = Vec2(300.f, 300.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);

	m_Animator->Play(L"Enemy_Dead", true);

}



CEffect_Dead::~CEffect_Dead()
{
}




void CEffect_Dead::Tick()
{
	m_LifeTime += DT;



	if (m_LifeTime > m_LimitTime)
	{
		SetDead(true);
		m_LifeTime = 0;
		m_Animator->ResetAnim();
	}



}

void CEffect_Dead::Render()
{
	m_Animator->Render();
}

void CEffect_Dead::ChangeAnim()
{
	m_Animator->Play(L"Enemy_Dead_Tail",false);
}
