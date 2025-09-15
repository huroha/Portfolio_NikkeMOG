#include "pch.h"
#include "CSpawner_Gren.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CGren.h"

CSpawner_Gren::CSpawner_Gren()
	: m_CoolTime(4.f)
	, m_Have(false)
	, m_CheckInven(0)
	, m_MissileCount(0)

{
}

CSpawner_Gren::~CSpawner_Gren()
{
}


void CSpawner_Gren::Tick()
{
	// 없다면 가지고있는지 부터 검사
	if (!m_Have)
	{

		tPlayerInfo playerInfo = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo();
		for (int i = 0; i < UINT(PlayerWeapon::NONE); ++i)
		{
			if (playerInfo.WeaponInfo[i].WeaponName == PlayerWeapon::GREN)
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
			if (m_CoolTime > 4.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Gren_Sound", L"sound\\gren.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 240; i < 250; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CGren* pMissile = dynamic_cast<CGren*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(60.f, 40.f);
						pMissile->SetAngle(0.f);
						
						break;
					}

				}

				m_CoolTime = 0;
			}

		}
		break;
		case 2:

		{
			if (m_CoolTime > 4.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Gren_Sound", L"sound\\gren.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 240; i < 250; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CGren* pMissile = dynamic_cast<CGren*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(60.f, 40.f);
						pMissile->SetAngle(0.f);

						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(90.f);
							m_MissileCount = 0;
							break;
						}
						m_MissileCount += 1;
					}

				}

				m_CoolTime = 0;
			}

		}

		break;
		case 3:
		{
			if (m_CoolTime > 4.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Gren_Sound", L"sound\\gren.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 240; i < 250; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CGren* pMissile = dynamic_cast<CGren*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(60.f, 40.f);
						pMissile->SetAngle(0.f);

						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(45.f);
						}

						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(90.f);
							m_MissileCount = 0;
							break;
						}
						m_MissileCount += 1;
					}

				}

				m_CoolTime = 0;
			}


		}
		break;
		case 4:
		{
			if (m_CoolTime > 4.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Gren_Sound", L"sound\\gren.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 240; i < 250; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CGren* pMissile = dynamic_cast<CGren*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(80.f, 60.f);
						pMissile->SetColliderSize(Vec2(80.f, 60.f));
						pMissile->SetAddRadian(200.f);
						pMissile->SetSpeed(350.f);
						pMissile->SetLvMaxAnimation();
						pMissile->SetAngle(0.f);

						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(45.f);
						}

						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(90.f);
							m_MissileCount = 0;
							break;
						}
						m_MissileCount += 1;
					}

				}

				m_CoolTime = 0;
			}


		}
		break;
		case 5:
		{
		
			if (m_CoolTime > 2.5f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Gren_Sound", L"sound\\gren.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 240; i < 250; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CGren* pMissile = dynamic_cast<CGren*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(80.f, 60.f);
						pMissile->SetColliderSize(Vec2(80.f, 60.f));
						pMissile->SetAddRadian(200.f);
						pMissile->SetSpeed(350.f);
						pMissile->SetLvMaxAnimation();
						pMissile->SetAngle(0.f);

						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(90.f);
						}

						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(180.f);
						}
						if (m_MissileCount == 3)
						{
							pMissile->SetAngle(270.f);
							m_MissileCount = 0;
							break;
						}
						m_MissileCount += 1;
					}

				}

				m_CoolTime = 0;
			}

		}
		break;


		}


	}

}