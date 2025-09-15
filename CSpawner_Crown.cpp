#include "pch.h"
#include "CSpawner_Crown.h"

#include "CPlayer.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSound.h"
#include "CAssetMgr.h"

CSpawner_Crown::CSpawner_Crown()
	: m_Crown{}
	, m_CoolTime(0.f)
	, m_sec(false)
	, m_third(false)
{
	m_Crown.Level = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().WeaponInfo[0].Level;
	m_Crown.WeaponName = PlayerWeapon::CROWN;

	m_sound = CAssetMgr::Get()->LoadSound(L"crown_Missile", L"sound\\crown.wav");

	//m_sound->PlayToBGM(true);
	//m_sound->SetVolume(100.f);
}

CSpawner_Crown::~CSpawner_Crown()
{
}


void CSpawner_Crown::Tick()
{
	UINT WeaponLevel = (UINT)CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().WeaponInfo[0].Level;


	m_CoolTime += DT;


	switch (WeaponLevel)
	{

	case 1:
	{
		if ( m_CoolTime > 0.7f)
		{
			m_sound->Play();
			m_sound->SetVolume(3.f);
			for (int i = 0; i < 200; ++i)
			{
				
				if (GetMissileLayer()[i]->IsDead() == true)
				{
					CMissile* pMissile = dynamic_cast<CMissile*>(GetMissileLayer()[i]);
					pMissile->ChangeLifeState();
					pMissile->SetPos(GetPlayerPos());
					pMissile->SetMissileTexture(GetPlayerPrev());
					pMissile->SetScale(20.f, 20.f);
					pMissile->SetVelocity(GetMissleVelocity(), 500.f);
					pMissile->SetLifeTime(0.f);
					break;
				}
			}

			m_CoolTime = 0;
		}


	}
		break;
	case 2:
	{
		if (m_CoolTime > 0.4f)
		{
			m_sound->Play();
			m_sound->SetVolume(3.f);
			for (int i = 0; i < 200; ++i)
			{

				if (GetMissileLayer()[i]->IsDead() == true)
				{
					CMissile* pMissile = dynamic_cast<CMissile*>(GetMissileLayer()[i]);
					pMissile->ChangeLifeState();
					pMissile->SetPos(GetPlayerPos());
					pMissile->SetMissileTexture(GetPlayerPrev());
					pMissile->SetScale(20.f, 20.f);
					pMissile->SetLifeTime(0.f);
					pMissile->SetVelocity(GetMissleVelocity(), 600.f);
					break;
				}
			}

			m_CoolTime = 0;
		}


	}
		break;
	case 3:
	{
		if (m_CoolTime > 0.4f)
		{
			m_sound->Play();
			m_sound->SetVolume(3.f);
			for (int i = 0; i < 200; ++i)
			{

				if (GetMissileLayer()[i]->IsDead() == true)
				{
					CMissile* pMissile = dynamic_cast<CMissile*>(GetMissileLayer()[i]);
					pMissile->ChangeLifeState();
					pMissile->SetPos(GetPlayerPos());
					pMissile->SetMissileTexture(GetPlayerPrev());
					pMissile->SetScale(20.f, 20.f);
					pMissile->SetLifeTime(0.f);
					if (!m_sec)
					{
						pMissile->SetVelocity(GetMissleVelocity() + 0.1f, 600.f);
						m_sec = true;
					}
					else
					{
						pMissile->SetVelocity(GetMissleVelocity() - 0.1f, 600.f);
						m_sec = false;
						break;
					}
				}
			}

			m_CoolTime = 0;
		}


	}
		break;

	case 4:
	{
		if (m_CoolTime > 0.4f)
		{
			m_sound->Play();
			m_sound->SetVolume(3.f);
			for (int i = 0; i < 200; ++i)
			{

				if (GetMissileLayer()[i]->IsDead() == true)
				{
					CMissile* pMissile = dynamic_cast<CMissile*>(GetMissileLayer()[i]);
					pMissile->ChangeLifeState();
					pMissile->SetPos(GetPlayerPos());
					pMissile->SetScale(20.f, 20.f);
					pMissile->SetLifeTime(0.f);
					pMissile->SetMissileTexture(GetPlayerPrev());
					if (!m_sec && !m_third)
					{
						pMissile->SetVelocity(GetMissleVelocity() + 0.1f, 700.f);
						m_sec = true;
					}
					else if(m_sec && !m_third)
					{
						pMissile->SetVelocity(GetMissleVelocity() - 0.1f, 700.f);
						m_sec = false;
						m_third = true;
					}
					else
					{
						pMissile->SetVelocity(GetMissleVelocity(), 700.f);
						m_third = false;
						break;
					}
				}
			}

			m_CoolTime = 0;
		}


	}
		break;
	case 5:
	{
		if (m_CoolTime > 0.2f)
		{
			m_sound->Play();
			m_sound->SetVolume(2.f);
			for (int i = 0; i < 200; ++i)
			{

				if (GetMissileLayer()[i]->IsDead() == true)
				{
					CMissile* pMissile = dynamic_cast<CMissile*>(GetMissileLayer()[i]);
					pMissile->ChangeLifeState();
					pMissile->SetPos(GetPlayerPos());
					pMissile->SetScale(20.f, 20.f);
					pMissile->SetMissileTexture(GetPlayerPrev());
					pMissile->SetLifeTime(0.f);
					if (!m_sec && !m_third)
					{
						pMissile->SetVelocity(GetMissleVelocity() + 0.1f, 750.f);
						m_sec = true;
					}
					else if (m_sec && !m_third)
					{
						pMissile->SetVelocity(GetMissleVelocity() - 0.1f, 750.f);
						m_sec = false;
						m_third = true;
					}
					else
					{
						pMissile->SetVelocity(GetMissleVelocity(), 750.f);
						m_third = false;
						break;
					}
				}
			}

			m_CoolTime = 0;
		}


	}
		break;


	}



}