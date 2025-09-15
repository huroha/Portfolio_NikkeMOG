#include "pch.h"
#include "CSpawner_Lapun.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CLapunzel.h"


CSpawner_Lapun::CSpawner_Lapun()
	: m_CoolTime(5.f)
	, m_Have(false)
	, m_CheckInven(0)
	, m_MissileCount(0)
{
}

CSpawner_Lapun::~CSpawner_Lapun()
{
}




void CSpawner_Lapun::Tick()
{

	// 없다면 가지고있는지 부터 검사
	if (!m_Have)
	{

		tPlayerInfo playerInfo = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo();
		for (int i = 0; i < UINT(PlayerWeapon::NONE); ++i)
		{
			if (playerInfo.WeaponInfo[i].WeaponName == PlayerWeapon::LAPUNGEL)
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
			if (m_CoolTime > 5.5f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Lapunzel_Sound", L"sound\\lapunzel.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 221; i < 240; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CLapunzel* pMissile = dynamic_cast<CLapunzel*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(30.f, 30.f);
						pMissile->SetAngle(0.f);
						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(120.f);
							
						}
						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(240.f);
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
		case 2:

		{
			if (m_CoolTime > 5.5f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Lapunzel_Sound", L"sound\\lapunzel.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 221; i < 240; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CLapunzel* pMissile = dynamic_cast<CLapunzel*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(30.f, 30.f);
						pMissile->SetAngle(0.f);
						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(120.f);

						}
						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(240.f);
							
						}
						if (m_MissileCount == 3)
						{
							pMissile->SetAngle(0.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(180.f);
							pMissile->ChangeDir(-1);
						}

						if (m_MissileCount == 4)
						{
							pMissile->SetAngle(180.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(180.f);
							pMissile->ChangeDir(-1);
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
			if (m_CoolTime > 5.5f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Lapunzel_Sound", L"sound\\lapunzel.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 221; i < 240; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CLapunzel* pMissile = dynamic_cast<CLapunzel*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(30.f, 30.f);
						pMissile->SetAngle(0.f);
						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(120.f);

						}
						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(240.f);

						}
						if (m_MissileCount == 3)
						{
							pMissile->SetAngle(0.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
						}

						if (m_MissileCount == 4)
						{
							pMissile->SetAngle(90.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
							
						}
						if (m_MissileCount == 5)
						{
							pMissile->SetAngle(180.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
						}
						if (m_MissileCount == 6)
						{
							pMissile->SetAngle(270.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
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
			if (m_CoolTime > 5.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Lapunzel_Sound", L"sound\\lapunzel.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 221; i < 240; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CLapunzel* pMissile = dynamic_cast<CLapunzel*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(30.f, 30.f);
						pMissile->SetAngle(0.f);
						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(120.f);

						}
						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(240.f);

						}
						if (m_MissileCount == 3)
						{
							pMissile->SetAngle(0.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
						}

						if (m_MissileCount == 4)
						{
							pMissile->SetAngle(90.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);

						}
						if (m_MissileCount == 5)
						{
							pMissile->SetAngle(180.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
						}
						if (m_MissileCount == 6)
						{
							pMissile->SetAngle(270.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);

						}
						if (m_MissileCount == 7)
						{
							pMissile->SetAngle(0.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(80.f);
							pMissile->ChangeDir(1);
						}
						if (m_MissileCount == 8)
						{
							pMissile->SetAngle(180.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(80.f);
							pMissile->ChangeDir(1);
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
			if (m_CoolTime > 4.5f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Lapunzel_Sound", L"sound\\lapunzel.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 221; i < 240; ++i)
				{
					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CLapunzel* pMissile = dynamic_cast<CLapunzel*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetScale(40.f, 40.f);
						pMissile->SetColliderSize(Vec2(40.f, 40.f));
						pMissile->SetTextureSizeUp();
						pMissile->SetAngle(0.f);
						if (m_MissileCount == 1)
						{
							pMissile->SetAngle(120.f);

						}
						if (m_MissileCount == 2)
						{
							pMissile->SetAngle(240.f);

						}
						if (m_MissileCount == 3)
						{
							pMissile->SetAngle(0.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
						}

						if (m_MissileCount == 4)
						{
							pMissile->SetAngle(90.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);

						}
						if (m_MissileCount == 5)
						{
							pMissile->SetAngle(180.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);
						}
						if (m_MissileCount == 6)
						{
							pMissile->SetAngle(270.f);
							pMissile->SetRadius(160.f);
							pMissile->SetSpeed(160.f);
							pMissile->ChangeDir(-1);

						}
						if (m_MissileCount == 7)
						{
							pMissile->SetAngle(0.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(60.f);
							pMissile->ChangeDir(1);
						}
						if (m_MissileCount == 8)
						{
							pMissile->SetAngle(60.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(60.f);
							pMissile->ChangeDir(1);
							
						}
						if (m_MissileCount == 9)
						{
							pMissile->SetAngle(120.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(60.f);
							pMissile->ChangeDir(1);
						}
						if (m_MissileCount == 10)
						{
							pMissile->SetAngle(180.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(60.f);
							pMissile->ChangeDir(1);
						}

						if (m_MissileCount == 11)
						{
							pMissile->SetAngle(240.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(60.f);
							pMissile->ChangeDir(1);
						}

						if (m_MissileCount == 12)
						{
							pMissile->SetAngle(300.f);
							pMissile->SetRadius(240.f);
							pMissile->SetSpeed(60.f);
							pMissile->ChangeDir(1);
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
