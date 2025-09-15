#include "pch.h"
#include "CSpawner_Snow.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CSnow.h"


CSpawner_Snow::CSpawner_Snow()
	: m_CoolTime(3.f)
	, m_Have(false)
	, m_CheckInven(0)
	, m_MissileCount(0)
{




}

CSpawner_Snow::~CSpawner_Snow()
{
}




void CSpawner_Snow::Tick()
{
	// 없다면 가지고있는지 부터 검사
	if (!m_Have)
	{

		tPlayerInfo playerInfo = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo();
		for (int i = 0; i < UINT(PlayerWeapon::NONE); ++i)
		{
			if (playerInfo.WeaponInfo[i].WeaponName == PlayerWeapon::SNOWWHITE)
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
			if (m_CoolTime > 3.f)
			{

				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Snow_Sound", L"sound\\snow.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 201; i < 221; ++i)
				{

					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CSnow* pMissile = dynamic_cast<CSnow*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetPos(GetPrevMove());
						pMissile->SetScale(30.f, 30.f);
						pMissile->SetMissileTexture(GetPlayerPrev());
						pMissile->SetVelocity(GetMissleVelocity(), 2000.f);
						break;
					}
				}

				m_CoolTime = 0;
			}
		}
		break;
		case 2:

		{
			if (m_CoolTime > 3.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Snow_Sound", L"sound\\snow.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 201; i < 221; ++i)
				{

					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CSnow* pMissile = dynamic_cast<CSnow*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetPos(GetPrevMove());
						pMissile->SetScale(30.f, 30.f);
						pMissile->SetMissileTexture(GetPlayerPrev());
						pMissile->SetVelocity(GetMissleVelocity(), 2000.f);
						if (m_MissileCount == 1)
						{
							pMissile->SetVelocity(-GetMissleVelocity(), 2000.f);
							pMissile->SetMissileTexture(ReversePrevMove(GetPlayerPrev()));
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
			if (m_CoolTime > 3.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Snow_Sound", L"sound\\snow.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 201; i < 221; ++i)
				{

					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CSnow* pMissile = dynamic_cast<CSnow*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetPos(CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos());
						pMissile->SetScale(30.f, 30.f);
						pMissile->SetMissileTexture(GetPlayerPrev());
						pMissile->SetVelocity(GetMissleVelocity(), 2000.f);

						// 대각 이동일 때
						if (GetMissleVelocity() == Vec2(1.f, 1.f) || GetMissleVelocity() == Vec2(1.f,-1.f) ||
							GetMissleVelocity() == Vec2(-1.f,1.f) || GetMissleVelocity() == Vec2(-1.f,-1.f))
						{

							if (m_MissileCount == 1)
							{
								pMissile->SetVelocity(-GetMissleVelocity(), 2000.f);
								pMissile->SetMissileTexture(ReversePrevMove(GetPlayerPrev()));
							}

							if (m_MissileCount == 2)
							{
								pMissile->SetVelocity(GetMissleVelocity() * Vec2(1.0f, -1.f), 2000.f);
								pMissile->SetMissileTexture(PREV_MOVE::RIGHT_UP);
							}
							if (m_MissileCount == 3)
							{
								pMissile->SetVelocity(GetMissleVelocity() * Vec2(-1.0f, 1.f), 2000.f);
								pMissile->SetMissileTexture(PREV_MOVE::LEFT_DOWN);
								m_MissileCount = 0;
								break;
							}
							m_MissileCount += 1;
						}
						// 직선 이동일 대
						else
						{
							if (m_MissileCount == 1)
							{
								pMissile->SetVelocity(-GetMissleVelocity(), 2000.f);
								pMissile->SetMissileTexture(ReversePrevMove(GetPlayerPrev()));
							}

							// 좌우 이동
							if (GetMissleVelocity() == Vec2(1.f, 0.f) || GetMissleVelocity() == Vec2(-1.f, 0.f))
							{
								if (m_MissileCount == 2)
								{
									pMissile->SetVelocity( Vec2(0.f, -1.f), 2000.f);
									pMissile->SetMissileTexture(PREV_MOVE::UP);
								}
								if (m_MissileCount == 3)
								{
									pMissile->SetVelocity(Vec2(0.f,1.f), 2000.f);
									pMissile->SetMissileTexture(PREV_MOVE::DOWN);
									m_MissileCount = 0;
									break;
								}
								m_MissileCount += 1;
							} 
							// 상하 이동
							else
							{
								if (m_MissileCount == 2)
								{
									pMissile->SetVelocity(Vec2(1.0f, 0.f), 2000.f);
									pMissile->SetMissileTexture(PREV_MOVE::RIGHT);
								}
								if (m_MissileCount == 3)
								{
									pMissile->SetVelocity(Vec2(-1.0f, 0.f), 2000.f);
									pMissile->SetMissileTexture(PREV_MOVE::LEFT);
									m_MissileCount = 0;
									break;
								}
								m_MissileCount += 1;
							}

						}

					}
				}

				m_CoolTime = 0;
			}
		}
		break;
		case 4:
		{
			if (m_CoolTime > 3.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Snow_Sound", L"sound\\snow.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 201; i < 221; ++i)
				{

					CSnow* pMissile = dynamic_cast<CSnow*>(GetMissileLayer()[i]);
					pMissile->ChangeLifeState();
					pMissile->SetPos(CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos());
					pMissile->SetScale(80.f, 80.f);
					pMissile->SetVelocity(GetMissleVelocity(), 2500.f);
					pMissile->SetMissileTexture(GetPlayerPrev());
					pMissile->LevelMaxTexture();

					// 대각 이동일 때
					if (GetMissleVelocity() == Vec2(1.f, 1.f) || GetMissleVelocity() == Vec2(1.f, -1.f) ||
						GetMissleVelocity() == Vec2(-1.f, 1.f) || GetMissleVelocity() == Vec2(-1.f, -1.f))
					{

						if (m_MissileCount == 1)
						{
							pMissile->SetVelocity(-GetMissleVelocity(), 2500.f);
							pMissile->SetMissileTexture(ReversePrevMove(GetPlayerPrev()));
						}

						if (m_MissileCount == 2)
						{
							pMissile->SetVelocity(GetMissleVelocity() * Vec2(1.0f, -1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::RIGHT_UP);
						}
						if (m_MissileCount == 3)
						{
							pMissile->SetVelocity(GetMissleVelocity() * Vec2(-1.0f, 1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::LEFT_DOWN);
							m_MissileCount = 0;
							break;
						}
						m_MissileCount += 1;
					}
					// 직선 이동일 대
					else
					{
						if (m_MissileCount == 1)
						{
							pMissile->SetVelocity(-GetMissleVelocity(), 2500.f);
							pMissile->SetMissileTexture(ReversePrevMove(GetPlayerPrev()));
						}

						// 좌우 이동
						if (GetMissleVelocity() == Vec2(1.f, 0.f) || GetMissleVelocity() == Vec2(-1.f, 0.f))
						{
							if (m_MissileCount == 2)
							{
								pMissile->SetVelocity(Vec2(0.f, -1.f), 2500.f);
								pMissile->SetMissileTexture(PREV_MOVE::UP);
							}
							if (m_MissileCount == 3)
							{
								pMissile->SetVelocity(Vec2(0.f, 1.f), 2500.f);
								pMissile->SetMissileTexture(PREV_MOVE::DOWN);
								m_MissileCount = 0;
								break;
							}
							m_MissileCount += 1;
						}
						// 상하 이동
						else
						{
							if (m_MissileCount == 2)
							{
								pMissile->SetVelocity(Vec2(1.0f, 0.f), 2500.f);
								pMissile->SetMissileTexture(PREV_MOVE::RIGHT);
							}
							if (m_MissileCount == 3)
							{
								pMissile->SetVelocity(Vec2(-1.0f, 0.f), 2500.f);
								pMissile->SetMissileTexture(PREV_MOVE::LEFT);
								m_MissileCount = 0;
								break;
							}
							m_MissileCount += 1;
						}

						

					}
				}

				m_CoolTime = 0;
			}

		}
		break;
		case 5:
		{
			if (m_CoolTime > 3.f)
			{
				CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Snow_Sound", L"sound\\snow.wav");
				pBGM->Play();
				pBGM->SetVolume(25.f);
				for (int i = 201; i < 221; ++i)
				{

					if (GetMissileLayer()[i]->IsDead() == true)
					{
						CSnow* pMissile = dynamic_cast<CSnow*>(GetMissileLayer()[i]);
						pMissile->ChangeLifeState();
						pMissile->SetPos(GetPrevMove());
						pMissile->SetScale(80.f, 80.f);
						pMissile->SetColliderSize(Vec2(80.f, 80.f));
						pMissile->SetVelocity(Vec2(1.f,0.f), 2500.f);
						pMissile->SetMissileTexture(PREV_MOVE::RIGHT);
						pMissile->LevelMaxTexture();
						if (m_MissileCount == 1)
						{
							pMissile->SetVelocity(Vec2(-1.f, 0.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::LEFT);
						}
						if (m_MissileCount == 2)
						{
							pMissile->SetVelocity(Vec2(0.f, 1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::DOWN);
						}
						if (m_MissileCount == 3)
						{
							pMissile->SetVelocity(Vec2(0.f, -1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::UP);
						}
						if (m_MissileCount == 4)
						{
							pMissile->SetVelocity(Vec2(1.f, 1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::RIGHT_DOWN);
						}
						if (m_MissileCount == 5)
						{
							pMissile->SetVelocity(Vec2(1.f, -1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::RIGHT_UP);
						}
						if (m_MissileCount == 6)
						{
							pMissile->SetVelocity(Vec2(-1.f, 1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::LEFT_DOWN);
						}
						if (m_MissileCount == 7)
						{
							pMissile->SetVelocity(Vec2(-1.f, -1.f), 2500.f);
							pMissile->SetMissileTexture(PREV_MOVE::LEFT_UP);;
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

PREV_MOVE CSpawner_Snow::ReversePrevMove(PREV_MOVE _Prev)
{
	if (_Prev == PREV_MOVE::LEFT_UP)
		return PREV_MOVE::RIGHT_DOWN;
	else if (_Prev == PREV_MOVE::UP)
		return PREV_MOVE::DOWN;
	else if (_Prev == PREV_MOVE::RIGHT_UP)
		return PREV_MOVE::LEFT_DOWN;
	else if (_Prev == PREV_MOVE::LEFT)
		return PREV_MOVE::RIGHT;
	else if (_Prev == PREV_MOVE::RIGHT)
		return PREV_MOVE::LEFT;
	else if (_Prev == PREV_MOVE::LEFT_DOWN)
		return PREV_MOVE::RIGHT_UP;
	else if (_Prev == PREV_MOVE::DOWN)
		return PREV_MOVE::UP;
	else if (_Prev == PREV_MOVE::RIGHT_DOWN)
		return PREV_MOVE::LEFT_UP;
	else
		return PREV_MOVE::LEFT;


}
