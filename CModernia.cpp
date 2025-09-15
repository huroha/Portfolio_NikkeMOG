#include "pch.h"
#include "CModernia.h"
#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CEnemy.h"
#include "time.h"
#include "CPlayer.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CBoss.h"
#include "CSound.h"

CModernia::CModernia()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_LifeTime(0.f)
	, m_LimitTime(3.f)
	, m_Infinite(false)
	, m_DelayDMG(0.f)
	, m_bDelay(false)
	, m_DelayCool(0.2f)
	, m_CurDir(200.f,-200.f)
	, m_Seed(0)
	, m_Skill_Lv(1)
	, m_Sound(nullptr)
{
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(200.f, 150.f));



	// Animation 만들기
	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"Modernia_lv1";
	desc.FPS = 15;
	desc.FrmCount = 5;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Skill_Modernia", L"texture\\Skill_Modernia.png");
	desc.SliceSize = Vec2(200.f, 150.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);


	desc.AnimName = L"Modernia_lv2";
	desc.SliceSize = Vec2(250.f, 200.f);
	desc.StartLeftTop = Vec2(0.f, 150.f);
	m_Animator->CreateAnimation(desc);


	desc.AnimName = L"Modernia_lv3";
	desc.SliceSize = Vec2(300.f, 250.f);
	desc.StartLeftTop = Vec2(0.f, 350.f);
	m_Animator->CreateAnimation(desc);




	desc.AnimName = L"Modernia_lv4";
	desc.SliceSize = Vec2(350.f, 300.f);
	desc.StartLeftTop = Vec2(0.f, 600.f);
	m_Animator->CreateAnimation(desc);

	m_Animator->Play(L"Modernia_lv1", true);


	m_Sound = CAssetMgr::Get()->LoadSound(L"Moder_Sound3", L"sound\\moder_Fix.wav");
	//m_Sound->Play();
	//m_Sound->SetVolume(25.f);

}

CModernia::~CModernia()
{
}





void CModernia::Tick()
{
	

	if(!m_Infinite)
	{
		m_LifeTime += DT;
	}
	else
	{
		// Level MAX 일때,

		Vec2 playerPos = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos();
		Vec2 vPos = GetPos();

		
		if (m_CurDir == Vec2(0.f, 0.f))
		{
			return;
		}

		vPos += m_CurDir * DT;
		SetPos(vPos);


		if ((playerPos-vPos).x > 640.f || (playerPos - vPos).x < -640.f)
		{
			m_CurDir = playerPos - vPos;
			m_CurDir.Normalize();
			m_CurDir = m_CurDir * (CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Speed + 70.f);
		}
		else if ((playerPos - vPos).y > 360.f || (playerPos - vPos).y < -340.f)
		{
			m_CurDir = playerPos - vPos;
			m_CurDir.Normalize();
			m_CurDir = m_CurDir * (CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Speed + 70.f);
		}

	}
	m_DelayDMG += DT;



	if (m_LifeTime > m_LimitTime && !m_Infinite)
	{
		SetDead(true);
		m_LifeTime = 0;
		ChangeLockOn();
		m_Sound->Stop();
		
	}


	


	if( m_DelayDMG > m_DelayCool)
	{

		OnOffCollider(m_bDelay);
		m_DelayDMG = 0;
		
	}






}

void CModernia::Render()
{
	/*SELECT_BRUSH(BackDC, BRUSH_TYPE::GRAY);

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	Rectangle(BackDC, vPos.x - (vScale.x / 2.f), vPos.y - (vScale.y / 2.f)
		, vPos.x + (vScale.x / 2.f), vPos.y + (vScale.y / 2.f));*/
	m_Animator->Render();
}



void CModernia::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{


	if (!m_bDelay && _OtherObj->GetName() != L"Boss_Indivilia")
	{
		CEnemy* pEnemy = dynamic_cast<CEnemy*>(_OtherObj);
		if (pEnemy)
		{
			UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
			pEnemy->HPReduce((Atk / 2));
			_OwnCollider->ResetOverlapCount();
		}
	

	}

	else if(!m_bDelay && _OtherObj->GetName() == L"Boss_Indivilia")
	{
		CBoss* pEnemy = dynamic_cast<CBoss*>(_OtherObj);

		UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
		_OwnCollider->ResetOverlapCount();
		pEnemy->HPReduce((Atk / 2));

		
	}


}

void CModernia::ChangeLockOn()
{

	m_Seed += 1;
	srand((UINT)time(nullptr) + m_Seed);

	CPlayer* player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

	int randomX = rand() % 500 + 50;
	int randomY = rand() % 300 + 10;
	int randomDir = rand() % 2;
	int randomDir2 = rand() % 2;

	int vDir = 0;
	int vDir2 = 0;
	vDir = randomDir == 0 ? -1 : 1;
	vDir2 = randomDir2 == 0 ? -1 : 1;

	SetPos(Vec2(player->GetPos().x + (vDir * randomX), player->GetPos().y + (vDir2 * randomY)));


}

void CModernia::SetColliderSize(Vec2 _Size)
{
	m_Collider->SetScale(_Size);
}

void CModernia::OnOffCollider(bool _trigger)
{

	if (_trigger)
	{
		m_Collider->Activate();
		m_bDelay = false;
	}
	else
	{
		m_Collider->Deactivate();
		m_bDelay = true;
	}
}

void CModernia::SetLifeTime(float _time)
{

	m_LifeTime = _time;

}


void CModernia::PlaySoundModer()
{
	m_Sound->Play(true);
	m_Sound->SetVolume(55.f);
}

void CModernia::StopSound()
{
	m_Sound->Stop();
}

void CModernia::ChangeAnimation(UINT _Level)
{

	switch (_Level)
	{
	case 1:
	{
		m_Animator->Play(L"Modernia_lv1", true);
	}
		break;

	case 2:
	{
		m_Animator->Play(L"Modernia_lv2", true);
	}
		break;

	case 3:
	{
		m_Animator->Play(L"Modernia_lv3", true);
	}
		break;
	case 4:
	{
		m_Animator->Play(L"Modernia_lv4", true);
	}
		break;

	}


}
