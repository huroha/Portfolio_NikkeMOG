#include "pch.h"
#include "CTail.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CBoss.h"
#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CEffectSpawner.h"
#include "CSound.h"

CTail::CTail()
	: m_Boss(nullptr)
	, m_Animator(nullptr)
	, m_Alpha(255.f)
	, m_HpCheck(0.f)
{
	m_Boss = CLevelMgr::Get()->GetCurrentLevel()->GetBoss();

	m_HpCheck = (m_Boss->GetMonsterInfo().HP / 10) * 4;

	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"Tail";
	desc.FPS = 8;
	desc.FrmCount = 8;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"BossTail", L"texture\\indi_tail_1200_200.png");
	desc.SliceSize = Vec2(150.f, 200.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);


	m_Animator->Play(L"Tail", true);

}

CTail::~CTail()
{
}


void CTail::Tick()
{

	float HPRemain = m_Boss->GetMonsterInfo().HP;
	if (!m_Boss->IsDead())
	{
		SetPos(Vec2(m_Boss->GetPos().x, m_Boss->GetPos().y-135.f));
		m_Alpha = m_Boss->GetAlpha();
	}
	
	if (HPRemain < m_HpCheck)
	{
		CEffectSpawner* EffectSpawner = dynamic_cast<CEffectSpawner*>(CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::SPAWNER)[11]);

	
		EffectSpawner->EffectOn(this,40);


		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"TailDeath", L"sound\\TailExplosion.wav");
		pBGM->Play();
		pBGM->SetVolume(50.f);


		SetDead(true);

	}
}

void CTail::Render()
{
	if(m_Boss->IsTrace() == false && !m_Boss->IsDead())
		m_Animator->Render();
}
