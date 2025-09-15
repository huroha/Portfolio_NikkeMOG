#include "pch.h"
#include "CSpawner_Indi.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CDig_Missile.h"
#include "CBoss.h"
#include "CBasic_Missile.h"
#include "CTimeMgr.h"
#include "CTrace_Missile.h"
#include "CCamera.h"
#include "CThunder_Missile.h"
#include "time.h"
#include "CAssetMgr.h"
#include "CSound.h"


CSpawner_Indi::CSpawner_Indi()
	: m_BossProjectileLayer{}
	, m_Boss(nullptr)
	, m_CoolTime(0.f)
	, m_ShootCount(0)
	, m_Angle(0.f)
	, m_Round(0.f,0.f)
{

	m_BossProjectileLayer = CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::ENEMY_PROJECTILE);


}

CSpawner_Indi::~CSpawner_Indi()
{
}




void CSpawner_Indi::Tick()
{
	m_CoolTime += DT;


	m_Angle += 1500.f * DT;
	if (m_Angle >= 360.0f)
		m_Angle -= 360.0f;

	// 오브젝트 위치 업데이트
	float radian = m_Angle * (PI / 180.0f);
	float x = cos(radian);
	float y = sin(radian);



	m_Round = Vec2(x, y);


}



void CSpawner_Indi::DigAttack()
{
	CCamera::Get()->SetCamShake(100.f, 10.f, 0.7f);
	// 땅에서 솟구치는 공격
	CDig_Missile* pDig = dynamic_cast<CDig_Missile*>(m_BossProjectileLayer[m_BossProjectileLayer.size() - 1]);
	pDig->SetScale(200.f, 300.f);
	pDig->SetPos(CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos());
	pDig->ChangeLifeState();

	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"DigAttack", L"sound\\dig.wav");
	pBGM->Play();
	pBGM->SetVolume(100.f);

}

void CSpawner_Indi::BasicAttack_1()
{
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Basic", L"sound\\bossbasic.wav");
	pBGM->Play();
	pBGM->SetVolume(80.f);


	for (int i = 0; i < 50; ++i)
	{
		CBasic_Missile* pBasic = dynamic_cast<CBasic_Missile*>(m_BossProjectileLayer[i]);
		if (pBasic->IsDead() == true)
		{
			pBasic->SetScale(40.f, 40.f);
			pBasic->SetPos(CLevelMgr::Get()->GetCurrentLevel()->GetBoss()->GetPos());
			pBasic->SetSpeed(600.f);
			pBasic->CheckVelocity();
			pBasic->ChangeLifeState();

			break;
			
		}

		

	}

}

void CSpawner_Indi::BasicAttack_2()
{
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Basic2", L"sound\\bossbasic.wav");
	pBGM->Play();
	pBGM->SetVolume(80.f);

	for (int i = 0; i < 50; ++i)
	{
		CBasic_Missile* pBasic = dynamic_cast<CBasic_Missile*>(m_BossProjectileLayer[i]);
		if (pBasic->IsDead() == true)
		{
			pBasic->SetScale(40.f, 40.f);
			pBasic->SetPos(CLevelMgr::Get()->GetCurrentLevel()->GetBoss()->GetPos());
			// 여기에 round 적용
			pBasic->SetVelocity(m_Round *550.f);
			pBasic->ChangeLifeState();

			break;

		}

	}

}

void CSpawner_Indi::TraceAttack()
{
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Trace", L"sound\\Trace.wav");
	pBGM->Play();
	pBGM->SetVolume(50.f);


	for (int i = 50; i < 60; ++i)
	{
		CTrace_Missile* pTrace = dynamic_cast<CTrace_Missile*>(m_BossProjectileLayer[i]);
		if (pTrace->IsDead() == true)
		{
			pTrace->SetScale(40.f, 40.f);
			pTrace->SetPos(CLevelMgr::Get()->GetCurrentLevel()->GetBoss()->GetPos());
			pTrace->SetVelocitySpeed(Vec2(0.f,-1.f), 500.f);
			pTrace->ChangeLifeState();
			pTrace->SetSpeed2(600.f);

			break;

		}

	}


}

void CSpawner_Indi::ThunderAttack()
{
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"ThunderAttack", L"sound\\thunder.wav");
	pBGM->Play();
	pBGM->SetVolume(30.f);
	
	Vec2 vPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos();
	for (int i = 60; i < 70; ++i)
	{
		CThunder_Missile* pThunder = dynamic_cast<CThunder_Missile*>(m_BossProjectileLayer[i]);
		if (pThunder->IsDead() == true)
		{
			pThunder->SetScale(64.f, 256.f);
			pThunder->SetPos(Vec2(vPlayer.x, vPlayer.y-86.f));
			pThunder->ChangeLifeState();

			break;

		}

	}


}




