#include "pch.h"
#include "CSpawner_Killo.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKillo.h"


CSpawner_Killo::CSpawner_Killo()
	: m_Have(false)
	, m_CheckInven(0)
	, m_Once(0)
{

}



CSpawner_Killo::~CSpawner_Killo()
{

}


void CSpawner_Killo::Tick()
{
	// 없다면 가지고있는지 부터 검사
	if (!m_Have)
	{

		tPlayerInfo playerInfo = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo();
		for (int i = 0; i < UINT(PlayerWeapon::NONE); ++i)
		{
			if (playerInfo.WeaponInfo[i].WeaponName == PlayerWeapon::KILLO)
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

		switch (WeaponLevel)
		{
		case 1:
		{

			if (m_Once == 0)
			{

				if (GetMissileLayer()[250]->IsDead() == true)
				{
					CKillo* pMissile = dynamic_cast<CKillo*>(GetMissileLayer()[250]);
					pMissile->ChangeLifeState();
					pMissile->SetScale(70.f, 80.f);
					pMissile->SetColliderSize(Vec2(70.f, 80.f));
					m_Once+=1;
				}
			}


		}
		break;
		case 2:

		{
			if (m_Once == 1)
			{

				CKillo* pMissile = dynamic_cast<CKillo*>(GetMissileLayer()[250]);
				pMissile->SetWeaponDMG(1.f);
				m_Once += 1;
			}


		}

		break;
		case 3:
		{
			if (m_Once == 2)
			{

				CKillo* pMissile = dynamic_cast<CKillo*>(GetMissileLayer()[250]);
				pMissile->ChangeDmgDelay(0.07f);
				pMissile->SetWeaponDMG(2.f);
				m_Once += 1;
			}
		}
		break;
		case 4:
		{
			if (m_Once == 3)
			{

				CKillo* pMissile = dynamic_cast<CKillo*>(GetMissileLayer()[250]);
				pMissile->ChangeDmgDelay(0.05f);
				pMissile->SetWeaponDMG(3.f);
				pMissile->SetScale(90.f, 100.f);
				pMissile->SetLvMaxAnimation();
				pMissile->SetColliderSize(Vec2(90.f, 100.f));
				m_Once += 1;
			}

		}
		break;
		case 5:
		{
			if (m_Once == 4)
			{
				CKillo* pMissile = dynamic_cast<CKillo*>(GetMissileLayer()[250]);
				pMissile->ChangeDmgDelay(0.03f);
				pMissile->SetWeaponDMG(5.f);
				pMissile->SetScale(90.f, 100.f);
				pMissile->SetColliderSize(Vec2(90.f, 100.f));
				m_Once += 1;
			}

			

		}
		break;


		}


	}
}