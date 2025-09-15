#include "pch.h"
#include "CEnemySpawner.h"
#include "CEnemy.h"
#include "CEnemy1.h"
#include "CTimeMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"


#include "CAssetMgr.h"
#include "time.h"
#include "CKeyMgr.h"
#include "CCollider.h"

#include "CLogMgr.h"

CEnemySpawner::CEnemySpawner()
	: m_Player(nullptr)
	, m_EnemyLayer{}
	, m_CoolTime(0.f)
{
	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	m_EnemyLayer = CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::ENEMY);
}

CEnemySpawner::~CEnemySpawner()
{
}



void CEnemySpawner::Tick()
{
	m_CoolTime += DT;
	Vec2 vPlayer = m_Player->GetPos();
	srand((UINT)time(nullptr));

	//if (KEY_PRESSED(KEY::NUM_1))
	//{
	//	m_CoolTime += DT;
	//}

	UINT playerLevel = m_Player->GetPlayerInfo().Level;


	if (playerLevel < 3)
	{
		m_SpawnLevel = 3;
	}
	else if (playerLevel >= 3 && playerLevel < 8)
	{
		m_SpawnLevel = 5;
	}

	else if (playerLevel >= 8 && playerLevel <15)
	{
		m_SpawnLevel = 8;
	}
	else
	{
		m_SpawnLevel = 10;
	}


	if (m_CoolTime > 1.5f)
	{
		for (int i = 0; i < m_SpawnLevel; ++i)
		{
			for (int i = 0; i < m_EnemyLayer.size()-1; ++i)
			{
				if (m_EnemyLayer[i]->IsDead() == true)
				{

					int randomX = rand() % 200 + 150;
					int randomY = rand() % 200 + 150;
					int randomDir = rand() % 2;
					int randomDir2 = rand() % 2;

					int vDir = 0;
					int vDir2 = 0;
					vDir = randomDir == 0 ? -1 : 1;
					vDir2 = randomDir2 == 0 ? -1 : 1;

					
					CEnemy* pRespawnEnemy = dynamic_cast<CEnemy*>(m_EnemyLayer[i]);
					pRespawnEnemy->HPRestore(10.f + float(m_Player->GetPlayerInfo().Level / 5) * 5.f);
					pRespawnEnemy->AtkUP(10.f + float(m_Player->GetPlayerInfo().Level / 10) * 5.f);
					pRespawnEnemy->GetCollider()->ResetOverlapCount();
					pRespawnEnemy->SetPos(Vec2(vPlayer.x + (vDir * randomX), vPlayer.y + (vDir2 * randomY)));
					pRespawnEnemy->ChangeLifeState();
					m_CoolTime = 0;
					break;
				}
			}
		}

	}


}