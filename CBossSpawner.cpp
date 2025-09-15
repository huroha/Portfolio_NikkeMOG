#include "pch.h"
#include "CBossSpawner.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CBoss.h"
#include "CSoundMgr.h"
#include "CSound.h"
#include "CAssetMgr.h"

CBossSpawner::CBossSpawner()
	: m_EnemyLayer{}
	, m_CheckPlayerInfo{}
	, m_Once(false)
{

	m_EnemyLayer = CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::ENEMY);

}

CBossSpawner::~CBossSpawner()
{


}




void CBossSpawner::Tick()
{
	m_CheckPlayerInfo = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo();

	// 설정!!! 할!!! 것!!!!!
	if (m_CheckPlayerInfo.Level > 2 && m_CheckPlayerInfo.SlayCount > 6000)
	
	{
		if (!m_Once)
		{
			CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
			CBoss* pBoss = CLevelMgr::Get()->GetCurrentLevel()->GetBoss();
			pBoss->SetPos(pPlayer->GetPos().x + 300.f, pPlayer->GetPos().y - 150.f);
			pBoss->ChangeLifeState();
			pPlayer->SetBossInCount(true);
			m_Once = true;

			CSound* pBGM = CAssetMgr::Get()->LoadSound(L"goddess", L"sound\\NIKKE - Goddess of Victory (Over Zone) Piano Cover.wav");

			pBGM->PlayToBGM(true);
			pBGM->SetVolume(40.f);

		}

	}



}
