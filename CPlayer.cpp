#include "pch.h"
#include "CPlayer.h"

#include "CDebugMgr.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMissile.h"
#include "CGuidedMissile.h"

#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CRigidBody.h"
#include "CCamera.h"

#include "CLogMgr.h"


#include "CStateMachine.h"
#include "CPlayer_IDLE.h"
#include "CPlayer_MOVE.h"
#include "CEnemy.h"

#include "CPauseMgr.h"
#include "CPanel_Tex.h"
#include "CBtnUI_Tex.h"

#include "CLevel_Start.h"
#include "CItem.h"
#include "CBoss.h"
#include "CSound.h"
#include "CDarkUI.h"


CPlayer::CPlayer()
	: m_Texture(nullptr)
	, m_Body(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_SM(nullptr)
	, m_Skill(nullptr)
	, m_Info{}
	, m_Time2(0.f)
	, m_DmgDelayCount(0)
	, m_InCountBoss(false)
	, m_Alpha(255.f)
	, m_CheckHit(false)
	, m_Sound{}
	, m_BustTime(0.f)
	, m_SkillCool(true)
	, m_AccessSkill(false)
	, m_SoundCheck(0)
{
	// Palyer Info 설정
	m_Info.HP = 100.f;
	m_Info.MaxHP = 100.f;
	m_Info.Atk = 10.f;
	m_Info.Def = 0.f;
	m_Info.Speed = 300.f;
	m_Info.Level = 1;
	m_Info.Exp = 0.f;
	m_Info.PrevMove = PREV_MOVE::NONE;
	m_Info.SlayCount = 0;
	m_Info.WeaponInfo[0].WeaponName = PlayerWeapon::CROWN;
	m_Info.WeaponInfo[0].Level = 1;

	for (int i = 1; i < 6; ++i)
	{
		m_Info.WeaponInfo[i].WeaponName = PlayerWeapon::NONE;
		m_Info.WeaponInfo[i].Level = 0;
	}

	for (int i = 0; i < 6; ++i)
	{
		m_Info.PassiveInfo[i].PassiveName = PlayerPassive::NONE;
		m_Info.PassiveInfo[i].Level = 0;

	}

	// 컴포넌트 설정
	m_Body = AddComponent(new CCollider);
	m_Body->SetName(L"Body Collider");
	m_Body->SetOffset(Vec2(0.f, 4.f));
	m_Body->SetScale(Vec2(44.f, 54.f));



	// RigidBody
	m_RigidBody = AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::TOPVIEW);
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxSpeed(300.f);
	m_RigidBody->SetFriction(2000.f);
	m_RigidBody->SetJumpSpeed(600.f);


	// FSM 추가
	m_SM = AddComponent(new CStateMachine);
	m_SM->AddState(L"Player_Idle_LEFT", new CPlayer_IDLE);
	m_SM->AddState(L"Player_Idle_RIGHT", new CPlayer_IDLE);
	m_SM->AddState(L"Player_Move_LEFT", new CPlayer_MOVE);
	m_SM->AddState(L"Player_Move_RIGHT", new CPlayer_MOVE);
	



	// Player 에 Animator 컴포넌트 추가
	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"MOVE_LEFT";
	desc.FPS = 15;
	desc.FrmCount = 6;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Crown_Move", L"texture\\MOVE.png");
	desc.SliceSize = Vec2(50.f, 60.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);	
	m_Animator->CreateAnimation(desc);

	desc.AnimName = L"MOVE_RIGHT";
	desc.StartLeftTop = Vec2(0.f, 60.f);
	m_Animator->CreateAnimation(desc);



	tAnimDesc desc2 = {};

	desc2.AnimName = L"IDLE_LEFT";
	desc2.FPS = 6;
	desc2.FrmCount = 6;
	desc2.pAtlas = CAssetMgr::Get()->LoadTexture(L"Crown_Idle", L"texture\\IDLE.png");
	desc2.SliceSize = Vec2(50.f, 60.f);
	desc2.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc2);


	desc2.AnimName = L"IDLE_RIGHT";
	desc2.StartLeftTop = Vec2(0.f, 60.f);
	desc2.FrmCount = 6;
	desc2.FPS = 6;
	m_Animator->CreateAnimation(desc2);

	// Animation 정보 저장하기
	m_Animator->SaveAnimation(L"animation\\Player\\");


	//m_Animator->LoadAnimation(L"animation\\Player\\IDLE_DOWN.anim");
	//m_Animator->LoadAnimation(L"animation\\Player\\IDLE_LEFT.anim");
	//m_Animator->LoadAnimation(L"animation\\Player\\IDLE_RIGHT.anim");
	//m_Animator->LoadAnimation(L"animation\\Player\\IDLE_UP.anim");
	//m_Animator->LoadAnimation(L"animation\\Player\\MOVE_DOWN.anim");
	//m_Animator->LoadAnimation(L"animation\\Player\\MOVE_LEFT.anim");
	//m_Animator->LoadAnimation(L"animation\\Player\\MOVE_RIGHT.anim");
	//m_Animator->LoadAnimation(L"animation\\Player\\MOVE_UP.anim");

	// Animation 플레이
	m_Animator->Play(L"IDLE_LEFT", true);


	// Sound 설정
	m_Sound[(UINT)PlayerVoice::HIT] = CAssetMgr::Get()->LoadSound(L"hit_voice", L"sound\\hit_voice_[cut_0sec].wav");
	m_Sound[(UINT)PlayerVoice::BUST] = CAssetMgr::Get()->LoadSound(L"bust_voice", L"sound\\bust_voice.wav");
	m_Sound[(UINT)PlayerVoice::CLEAR] = CAssetMgr::Get()->LoadSound(L"clear_voice", L"sound\\clear_voice_fix.wav");
	m_Sound[(UINT)PlayerVoice::FAIL] = CAssetMgr::Get()->LoadSound(L"fail_voice", L"sound\\fail_voice.wav");
	m_Sound[(UINT)PlayerVoice::RELOAD] = CAssetMgr::Get()->LoadSound(L"reload_voice", L"sound\\reload_voice.wav");


	m_Sound[(UINT)PlayerVoice::HIT]->SetVolume(100.f);
	m_Sound[(UINT)PlayerVoice::BUST]->SetVolume(100.f);
	m_Sound[(UINT)PlayerVoice::CLEAR]->SetVolume(80.f);
	m_Sound[(UINT)PlayerVoice::FAIL]->SetVolume(100.f);
	m_Sound[(UINT)PlayerVoice::RELOAD]->SetVolume(70.f);


	//m_Sound->Play();
	//m_Sound->SetVolume(100.f);
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Body(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_SM(nullptr)
	, m_Skill(nullptr)
	, m_Info(_Other.m_Info)
	, m_DmgDelayCount(0)
	, m_InCountBoss(false)
	, m_Alpha(_Other.m_Alpha)
	, m_Sound{}
{
	m_Body = (CCollider*)GetComponentByName(L"Body Collider");
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
	m_SM = GetComponent<CStateMachine>();
}

CPlayer::~CPlayer()
{
	
}



void CPlayer::Tick()
{
	if(m_SM->CurState() == nullptr)
		m_SM->ChangeState(L"Player_Idle_RIGHT");


	
	if (KEY_PRESSED(KEY::LEFT)|| KEY_PRESSED(KEY::A))
	{
		if (KEY_PRESSED(KEY::RIGHT) || KEY_PRESSED(KEY::D))
			return;
		m_RigidBody->AddVelocity(Vec2(-m_Info.Speed, 0.f));
	}	
	if (KEY_PRESSED(KEY::RIGHT)|| KEY_PRESSED(KEY::D))
	{
		if ((KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::A)))
			return;
		m_RigidBody->AddVelocity(Vec2(m_Info.Speed, 0.f));

	}

	if (KEY_PRESSED(KEY::UP)|| KEY_PRESSED(KEY::W))
	{
		if (KEY_PRESSED(KEY::DOWN) || KEY_PRESSED(KEY::S))
			return;
		m_RigidBody->AddVelocity(Vec2(0.f, -m_Info.Speed));
	}
	if (KEY_PRESSED(KEY::DOWN) || KEY_PRESSED(KEY::S))
	{
		if (KEY_PRESSED(KEY::UP) || KEY_PRESSED(KEY::W))
			return;
		m_RigidBody->AddVelocity(Vec2(0.f, m_Info.Speed));
	}
	

	if (KEY_TAP(KEY::LEFT) || KEY_TAP(KEY::A))
	{
		m_SM->ChangeState(L"Player_Move_LEFT");
		m_Info.PrevMove = PREV_MOVE::LEFT;

		if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::UP))
		{
			m_Info.PrevMove = PREV_MOVE::LEFT_UP;
		}
		else if (KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::DOWN))
		{
			m_Info.PrevMove = PREV_MOVE::LEFT_DOWN;
		}
		else if (KEY_PRESSED(KEY::RIGHT) || KEY_PRESSED(KEY::D))
		{
			m_Info.PrevMove = PREV_MOVE::RIGHT;
		}
	}


	if (KEY_TAP(KEY::RIGHT) || KEY_TAP(KEY::D))
	{

		m_SM->ChangeState(L"Player_Move_RIGHT");
		m_Info.PrevMove = PREV_MOVE::RIGHT;

		if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::UP))
		{
			m_Info.PrevMove = PREV_MOVE::RIGHT_UP;
		}
		else if (KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::DOWN))
		{
			m_Info.PrevMove = PREV_MOVE::RIGHT_DOWN;
		}
		else if (KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::A))
		{
			m_Info.PrevMove = PREV_MOVE::LEFT;
		}
	}

	if (KEY_TAP(KEY::W) || KEY_TAP(KEY::UP))
	{
		if (m_SM->CurState()->GetName() == L"Player_Idle_LEFT" || m_SM->CurState()->GetName() == L"Player_Move_LEFT")
			m_SM->ChangeState(L"Player_Move_LEFT");
		else
			m_SM->ChangeState(L"Player_Move_RIGHT");
		m_Info.PrevMove = PREV_MOVE::UP;

		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::LEFT))
		{
			m_Info.PrevMove = PREV_MOVE::LEFT_UP;
		}
		else if (KEY_PRESSED(KEY::D) || KEY_PRESSED(KEY::RIGHT))
		{
			m_Info.PrevMove = PREV_MOVE::RIGHT_UP;
		}
		else if (KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::DOWN))
		{
			m_Info.PrevMove = PREV_MOVE::DOWN;
		}
	}

	if (KEY_TAP(KEY::DOWN) || KEY_TAP(KEY::S))
	{
		
		if (m_SM->CurState()->GetName() == L"Player_Idle_LEFT" || m_SM->CurState()->GetName() == L"Player_Move_LEFT")
			m_SM->ChangeState(L"Player_Move_LEFT");
		else
			m_SM->ChangeState(L"Player_Move_RIGHT");
		m_Info.PrevMove = PREV_MOVE::DOWN;


		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::LEFT))
		{
			m_Info.PrevMove = PREV_MOVE::LEFT_DOWN;
		}
		else if (KEY_PRESSED(KEY::D) || KEY_PRESSED(KEY::RIGHT))
		{
			m_Info.PrevMove = PREV_MOVE::RIGHT_DOWN;
		}
		else if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::UP))
		{
			m_Info.PrevMove = PREV_MOVE::UP;
		}
	}


	if (KEY_RELEASED(KEY::LEFT) || KEY_RELEASED(KEY::A))
	{

		if (m_Info.PrevMove == PREV_MOVE::LEFT_UP)
		{
			m_Info.PrevMove = PREV_MOVE::UP;
			m_SM->ChangeState(L"Player_Move_RIGHT");
		}
		else if (m_Info.PrevMove == PREV_MOVE::LEFT_DOWN)
		{
			m_Info.PrevMove = PREV_MOVE::DOWN;
			m_SM->ChangeState(L"Player_Move_RIGHT");
		}

		if (KEY_PRESSED(KEY::UP) || KEY_PRESSED(KEY::W) || (KEY_PRESSED(KEY::DOWN) || KEY_PRESSED(KEY::S)))
			return;
		m_SM->ChangeState(L"Player_Idle_LEFT");
		if (KEY_PRESSED(KEY::RIGHT) || KEY_PRESSED(KEY::D))
		{
			m_SM->ChangeState(L"Player_Move_RIGHT");
			m_Info.PrevMove = PREV_MOVE::RIGHT;
		}


	}

	if (KEY_RELEASED(KEY::RIGHT) || KEY_RELEASED(KEY::D))
	{
		if (m_Info.PrevMove == PREV_MOVE::RIGHT_UP)
		{
			m_Info.PrevMove = PREV_MOVE::UP;
			m_SM->ChangeState(L"Player_Move_LEFT");
		}
		else if (m_Info.PrevMove == PREV_MOVE::RIGHT_DOWN)
		{
			m_Info.PrevMove = PREV_MOVE::DOWN;
			m_SM->ChangeState(L"Player_Move_LEFT");
		}

		if (KEY_PRESSED(KEY::UP) || KEY_PRESSED(KEY::W) || (KEY_PRESSED(KEY::DOWN) || KEY_PRESSED(KEY::S)))
			return;
		m_SM->ChangeState(L"Player_Idle_RIGHT");
		if (KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::A))
		{
			m_SM->ChangeState(L"Player_Move_LEFT");
			m_Info.PrevMove = PREV_MOVE::LEFT;
		}


	}

	if (KEY_RELEASED(KEY::W) || KEY_RELEASED(KEY::UP))
	{

		if (m_Info.PrevMove == PREV_MOVE::RIGHT_UP)
		{
			m_Info.PrevMove = PREV_MOVE::RIGHT;
		}
		else if (m_Info.PrevMove == PREV_MOVE::LEFT_UP)
		{
			m_Info.PrevMove = PREV_MOVE::LEFT;
		}

		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::LEFT) || (KEY_PRESSED(KEY::D) || KEY_PRESSED(KEY::RIGHT)))
			return;
		if (KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::DOWN))
		{
			m_Info.PrevMove = PREV_MOVE::DOWN;
			return;
		}

		if(m_SM->CurState()->GetName() == L"Player_Move_RIGHT" || m_SM->CurState()->GetName() == L"Player_Idle_RIGHT")
			m_SM->ChangeState(L"Player_Idle_RIGHT");
		else
			m_SM->ChangeState(L"Player_Idle_LEFT");



	}
	if (KEY_RELEASED(KEY::S) || KEY_RELEASED(KEY::DOWN))
	{

		if (m_Info.PrevMove == PREV_MOVE::RIGHT_DOWN)
		{
			m_Info.PrevMove = PREV_MOVE::RIGHT;
		}
		else if (m_Info.PrevMove == PREV_MOVE::LEFT_DOWN)
		{
			m_Info.PrevMove = PREV_MOVE::LEFT;
		}


		if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::LEFT) || (KEY_PRESSED(KEY::D) || KEY_PRESSED(KEY::RIGHT)))
			return;
		if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::UP))
		{
			m_Info.PrevMove = PREV_MOVE::UP;
			return;
		}

		if (m_SM->CurState()->GetName() == L"Player_Move_RIGHT" || m_SM->CurState()->GetName() == L"Player_Idle_RIGHT")
			m_SM->ChangeState(L"Player_Idle_RIGHT");
		else
			m_SM->ChangeState(L"Player_Idle_LEFT");


	}


	if (KEY_TAP(KEY::R))
	{		

		if (IsAccess())
		{

			Skill_On();
			m_AccessSkill = false;
			m_SoundCheck = 0;
		}

	}

	//if (KEY_TAP(KEY::F))
	//{

	//	GainExp(30.f);
	//	m_Info.Coin += 10;

	//}
	//if (KEY_TAP(KEY::G))
	//{

	//	m_Info.SlayCount += 1000;

	//}
	//if (KEY_TAP(KEY::H))
	//{

	//	HPRestore();

	//}
	//if (KEY_TAP(KEY::PGUP))
	//{
	//	m_Info.Atk += 10.f;

	//}
	//if (KEY_TAP(KEY::PGDOWN))
	//{
	//	m_Info.Atk = 5.f;
	//}


	if (IsAccess())
	{
		m_SoundCheck += 1;
		if (m_SoundCheck == 1)
		{
			CSound* pBGM = CAssetMgr::Get()->LoadSound(L"BustReady", L"sound\\BustReady.wav");
			pBGM->Play();
			pBGM->SetVolume(20.f);
		}
	}
	

	// 피격무적..?
	if (m_DmgDelayCount != 0)
	{
		m_Time2 += DT;
		if (m_Time2 > 0.7f)
		{
			m_DmgDelayCount = 0;
			m_Time2 = 0;
			m_Alpha = 255;
			m_CheckHit = false;
		}
	}

	if (m_CheckHit)
	{
		static float dir = 1.f;
		m_Alpha += DT * 2000.f * dir;
		if (m_Alpha >= 255.f)
		{
			m_Alpha = 255.f;
			dir = -1.f;
		}
		else if (m_Alpha < 0.f)
		{
			m_Alpha = 0.f;
			dir = 1.f;
		}
	}
	
	if (!m_SkillCool)
	{
		m_BustTime += DT;
	}

	if (m_BustTime > 4.f)
	{
		Skill_Off();
		m_BustTime = 0;
	}

}

void CPlayer::Render()
{
	
	m_Animator->Render();


}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

	

	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::ENEMY && m_DmgDelayCount == 0)
	{

		if (_OtherObj->GetName() == L"Boss_Indivilia")
		{
			CBoss* pEnemy = dynamic_cast<CBoss*>(_OtherObj);
			if (m_Info.HP > 0)
			{
				float dmg = pEnemy->GetMonsterInfo().Atk - GetPlayerInfo().Def;
				if (dmg > 0)
				{
					HPReduce(dmg);
				}
			}
			m_CheckHit = true;
		}

		else
		{
			m_CheckHit = true;
			CEnemy* pEnemy = dynamic_cast<CEnemy*>(_OtherObj);
			if (m_Info.HP > 0)
			{
				float dmg = pEnemy->GetMonsterInfo().Atk - GetPlayerInfo().Def;
				HPReduce(dmg);
			}
		}

		++m_DmgDelayCount;
	
	}

	// 보스 미사일 HP 감소 처리할 것.
	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::ENEMY_PROJECTILE)
	{
		HPReduce(15);
		m_CheckHit = true;
		++m_DmgDelayCount;
	}


}

void CPlayer::Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::ENEMY)
	{

		CRigidBody* pRigid = (CRigidBody*)_OtherObj->GetComponent(COMPONENT_TYPE::RIGIDBODY);
		Vec2 vDir = pRigid->GetVelocity();
		m_RigidBody->AddVelocity(vDir);

	}

}




void CPlayer::GainExp(float _Exp)
{

	m_Info.Exp += _Exp;
	if (m_Info.Exp >= 200.f)
	{
		float remainExp = m_Info.Exp - 200.f;
		if (remainExp != 0.f)
		{
			m_Info.Exp = remainExp;
		}
		m_Info.Exp = remainExp;

		m_Info.Level += 1;



		CLevel_Start* pCurlevel = dynamic_cast<CLevel_Start*>(CLevelMgr::Get()->GetCurrentLevel());
		pCurlevel->VisibleSkill_BG(GetPlayerInfo(),false);
		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"LevelUP", L"sound\\LevelUP.wav");
		pBGM->Play();
		pBGM->SetVolume(20.f);

		CPauseMgr::Get()->ChangePauseState();

	}


}



UINT CPlayer::GetPassiveLevel(PlayerPassive _Passive)
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_Info.PassiveInfo[i].PassiveName == (PlayerPassive)_Passive)
		{
			return m_Info.PassiveInfo[i].Level;
		}
	}

	return (UINT)PlayerPassive::NONE;
}

UINT CPlayer::GetWeaponLevel(PlayerWeapon _Weapon)
{
	for (int i = 0; i < (UINT)PlayerWeapon::NONE; ++i)
	{
		if (m_Info.WeaponInfo[i].WeaponName == (PlayerWeapon)_Weapon)
		{
			return m_Info.WeaponInfo[i].Level;
		}
	}

	return (UINT)PlayerWeapon::NONE;
}




void CPlayer::LevelUp_Passive(PlayerPassive _PassiveName, UINT _PassiveLevel)
{
	if (_PassiveName == PlayerPassive::ATK && _PassiveLevel < 5)
	{
		m_Info.Atk += (_PassiveLevel + 1);
		LOG(LOG_LEVEL::LOG, L"ATK 증가");
	}

	else if (_PassiveName == PlayerPassive::DEF && _PassiveLevel < 5)
	{
		m_Info.Def += (_PassiveLevel + 1);
		LOG(LOG_LEVEL::LOG, L"DEF 증가");
	}

	else if (_PassiveName == PlayerPassive::SPEED && _PassiveLevel < 5)
	{
		m_Info.Speed += 30;
		m_RigidBody->SetMaxSpeed(m_Info.Speed);
		LOG(LOG_LEVEL::LOG, L"SPEED 증가");
	}


	else if (_PassiveName == PlayerPassive::HP && _PassiveLevel < 5)
	{
		m_Info.MaxHP += 10 * (_PassiveLevel + 1);
		LOG(LOG_LEVEL::LOG, L"Max HP 증가");

	}
	else if (_PassiveName == PlayerPassive::MAGNET && _PassiveLevel < 5)
	{
		// 아이템 접근해서 detect range 늘리기
		vector<CObj*> ItemLayer = CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::ITEM);
		for (int i = 0; i < ItemLayer.size(); ++i)
		{
			CItem* pItem = dynamic_cast<CItem*>(ItemLayer[i]);
			pItem->MagnetLevelUp();
		}
		LOG(LOG_LEVEL::LOG, L"아이템 획득 범위 증가");

	}

	else if (_PassiveName == PlayerPassive::ALLPOWER && _PassiveLevel < 5)
	{
		m_Info.Atk += (_PassiveLevel + 1);
		m_Info.Def += (_PassiveLevel + 1);
		m_Info.MaxHP += 10 * (_PassiveLevel + 1);
		LOG(LOG_LEVEL::LOG, L"ALL Power 증가");

	}
	// 레밸이 Max 에 도달할 시 Coin 습득으로 변경
	else
	{
		m_Info.Coin += 50;
		LOG(LOG_LEVEL::LOG, L"패시브 LV MAX Coin 획득");
	}




}

void CPlayer::LevelUp_Weapon(PlayerWeapon _WeaponName, UINT _WeaponLevel)
{


	if(_WeaponLevel >= 5)
	{
		m_Info.Coin += 50;
		LOG(LOG_LEVEL::LOG, L"무기 LV MAX Coin 획득 ");

	}



}

void CPlayer::Skill_On()
{
	PlayVoice(PlayerVoice::BUST);
	m_SkillCool = false;
	m_Skill->SetVisibleState(true);
	m_Info.Def += 50.f;
	m_Info.Atk += 10.f;
	
}

void CPlayer::Skill_Off()
{
	m_SkillCool = true;
	m_AccessSkill = false;
	m_Skill->SetVisibleState(false);
	m_Info.Def -= 50.f;
	m_Info.Atk -= 10.f;
}

void CPlayer::PlayVoice(PlayerVoice _choice)
{
	m_Sound[(UINT)_choice]->Play();
}




void CPlayer::GainPassive(PlayerPassive _PassiveName)
{
	// 구현해야 할 것.

	// 패시브가 없다면 추가하기

	// 있으면 레밸에 +1 함

	// 패시브 검사 우선

	for (int i = 0; i < 6; ++i)
	{
		if (m_Info.PassiveInfo[i].PassiveName == _PassiveName)
		{
			LevelUp_Passive(_PassiveName, m_Info.PassiveInfo[i].Level);
			if (m_Info.PassiveInfo[i].Level == 5)
				return;
			m_Info.PassiveInfo[i].Level += 1;
			return;
		}

	}
	// 없으면 패시브 추가

	for (int i = 0; i < 6; ++i)
	{
		if (m_Info.PassiveInfo[i].PassiveName == PlayerPassive::NONE)
		{
			LevelUp_Passive(_PassiveName, 0);
			m_Info.PassiveInfo[i].PassiveName = _PassiveName;
			m_Info.PassiveInfo[i].Level += 1;
			return;
		}
	}
	



}

void CPlayer::GainWeapon(PlayerWeapon _WeaponName)
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_Info.WeaponInfo[i].WeaponName == _WeaponName)
		{
			LevelUp_Weapon(_WeaponName, m_Info.WeaponInfo[i].Level);
			if (m_Info.WeaponInfo[i].Level == 5)
				return;
			m_Info.WeaponInfo[i].Level += 1;
			return;
		}

	}
	// 없으면 무기 추가

	for (int i = 0; i < 6; ++i)
	{
		if (m_Info.WeaponInfo[i].WeaponName == PlayerWeapon::NONE)
		{
			LevelUp_Weapon(_WeaponName, 0);
			m_Info.WeaponInfo[i].WeaponName = _WeaponName;
			m_Info.WeaponInfo[i].Level += 1;
			return;
		}
	}

}


void CPlayer::HPRestore()
{
	if (m_Info.HP < 50)
	{
		m_Sound[(UINT)PlayerVoice::RELOAD]->Play();
	}
	m_Info.HP += 30;
	
	if (m_Info.HP >= m_Info.MaxHP)
	{
		m_Info.HP = m_Info.MaxHP;

	}

}

void CPlayer::HPReduce_Dig()
{

	m_Info.HP -= 40;
	if (m_Info.HP <= 0)
	{
		m_Info.HP = 0;;
		CLevel_Start* pStart = dynamic_cast<CLevel_Start*>(CLevelMgr::Get()->GetCurrentLevel());
		pStart->GetResultMenu()->SetStartWidth(1);
		pStart->GetResultMenu()->SetVisibleState(true);
		CPauseMgr::Get()->ChangePauseState();
	}
	LOG(LOG_LEVEL::LOG, L"DIG Attack으로 HP감소");

}

void CPlayer::HPReduce(float _Dmg)
{
	float DMG = _Dmg - m_Info.Def;
	if (DMG > 0)
	{
		m_Info.HP -= DMG;

	}
	if (m_Info.HP <= 0)
	{
		m_Info.HP = 0;
		CLevel_Start* pStart = dynamic_cast<CLevel_Start*>(CLevelMgr::Get()->GetCurrentLevel());
		pStart->GetResultMenu()->SetStartWidth(1);
		pStart->GetResultMenu()->SetVisibleState(true);
		pStart->GetDarkFilter()->ChangeVisibleState();

		m_Sound[(UINT)PlayerVoice::FAIL]->Play();
		//PlayVoice(PlayerVoice::FAIL);
		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Fail_BGM", L"sound\\failbgm.wav");
		pBGM->PlayToBGM();
		pBGM->SetVolume(40.f);

		CPauseMgr::Get()->ChangePauseState();
	}





}



