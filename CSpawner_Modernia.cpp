#include "pch.h"
#include "CSpawner_Modernia.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CModernia.h"
#include "CTimeMgr.h"
#include "CBoss.h"


CSpawner_Modernia::CSpawner_Modernia()
	: m_CoolTime(11.f)
	, m_Have(false)
	, m_CheckInven(0)
{

}

CSpawner_Modernia::~CSpawner_Modernia()
{
}



void CSpawner_Modernia::Tick()
{


	// 없다면 가지고있는지 부터 검사
	if (!m_Have)
	{

		tPlayerInfo playerInfo = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo();
		for (int i = 0; i < UINT(PlayerWeapon::NONE); ++i)
		{
			if (playerInfo.WeaponInfo[i].WeaponName == PlayerWeapon::MODERNIA)
			{
				m_Have = true;
				m_CheckInven = i;
				break;
			}
			
		}

	}


	// 가지고 있으면 관리 시작
	else
	{
		UINT WeaponLevel = (UINT)CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().WeaponInfo[m_CheckInven].Level;
		m_CoolTime += DT;

		switch (WeaponLevel)
		{
		case 1:

		{
			if (m_CoolTime > 10.f)
			{

				if (GetMissileLayer()[200]->IsDead() == true)
				{
					CModernia* pMissile = dynamic_cast<CModernia*>(GetMissileLayer()[200]);
					pMissile->ChangeLifeState();
					pMissile->ChangeLockOn();
					pMissile->SetScale(200.f, 150.f);
					pMissile->PlaySoundModer();
				}
				m_CoolTime = 0;
			}


		}
			break;
		case 2:

		{
			if (m_CoolTime > 10.f)
			{

				if (GetMissileLayer()[200]->IsDead() == true)
				{
					CModernia* pMissile = dynamic_cast<CModernia*>(GetMissileLayer()[200]);
					pMissile->ChangeLifeState();
					pMissile->ChangeLockOn();
					pMissile->SetScale(250.f, 200.f);
					pMissile->ChangeAnimation(2);
					pMissile->PlaySoundModer();
					pMissile->SetColliderSize(Vec2(250.f, 200.f));
				}
				m_CoolTime = 0;
			}


		}

			break;
		case 3:
		{
			if (m_CoolTime > 8.f)
			{

				if (GetMissileLayer()[200]->IsDead() == true)
				{
					CModernia* pMissile = dynamic_cast<CModernia*>(GetMissileLayer()[200]);
					pMissile->ChangeLifeState();
					pMissile->ChangeLockOn();
					pMissile->SetScale(300.f, 250.f);
					pMissile->ChangeAnimation(3);
					pMissile->PlaySoundModer();
					pMissile->SetColliderSize(Vec2(300.f, 250.f));
				}
				m_CoolTime = 0;
			}


		}
			break;
		case 4:
		{
			if (m_CoolTime > 8.f)
			{

				if (GetMissileLayer()[200]->IsDead() == true)
				{
					CModernia* pMissile = dynamic_cast<CModernia*>(GetMissileLayer()[200]);
					pMissile->ChangeLifeState();
					pMissile->ChangeLockOn();
					pMissile->SetScale(350.f, 300.f);
					pMissile->ChangeAnimation(4);
					pMissile->PlaySoundModer();
					pMissile->SetColliderSize(Vec2(350.f, 300.f));
				}
				m_CoolTime = 0;
			}


		}
			break;
		case 5:
		{


			if (GetMissileLayer()[200]->IsDead() == true)
			{
				CModernia* pMissile = dynamic_cast<CModernia*>(GetMissileLayer()[200]);
				pMissile->ChangeLifeState();
				pMissile->LevelMax();
				pMissile->SetScale(350.f, 300.f);
				pMissile->ChangeAnimation(4);
				pMissile->PlaySoundModer();
				pMissile->SetColliderSize(Vec2(350.f, 300.f));
				pMissile->SetLifeTime(0.f);
				
			}


		}
			break;


		}


		if (CLevelMgr::Get()->GetCurrentLevel()->GetBoss()->GetMonsterInfo().HP <= 0)
		{
			CModernia* pMissile = dynamic_cast<CModernia*>(GetMissileLayer()[200]);
			pMissile->StopSound();
		}

	}


}
