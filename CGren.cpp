#include "pch.h"
#include "CGren.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CEngine.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CBoss.h"

CGren::CGren()
	: m_Animator(nullptr)
	, m_LifeTime(0.f)
	, m_LimitTime(2.f)
	, m_Radius(50.f)
	, m_Angle(0.f)
	, m_Speed(300.f)
	, m_AddRadian(150.f)
{
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(60.f, 40.f));

	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"Gren_Small";
	desc.FPS = 15;
	desc.FrmCount = 6;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Skill_Gren1", L"texture\\gren_360_40.png");
	desc.SliceSize = Vec2(60.f, 40.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);


	desc.AnimName = L"Gren_Big";
	desc.SliceSize = Vec2(80.f, 60.f);
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Skill_Gren2", L"texture\\gren_480_60.png");
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);


	m_Animator->Play(L"Gren_Small",true);

}

CGren::~CGren()
{
}





void CGren::Tick()
{

	m_LifeTime += DT;


	Vec2 playerPos = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos();

	// 각도 업데이트
	m_Angle += m_Speed * DT;
	if (m_Angle >= 360.0f)
		m_Angle -= 360.0f;

	// 오브젝트 위치 업데이트
	float radian = m_Angle * (PI / 180.0f);
	float x = m_Radius * cos(radian);
	float y = m_Radius * sin(radian);

	m_Radius += m_AddRadian * DT;

	playerPos.x += x;
	playerPos.y += y;

	SetPos(playerPos);



	if (m_LifeTime > m_LimitTime)
	{
		SetDead(true);
		m_LifeTime = 0;
		m_Radius = 50.f;
	}


}

void CGren::Render()
{
	m_Animator->Render();
}

void CGren::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{


	if (_OtherObj->GetName() == L"Boss_Indivilia")
	{
		CBoss* pEnemy = dynamic_cast<CBoss*>(_OtherObj);
		UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
		pEnemy->HPReduce((Atk));
		_OwnCollider->ResetOverlapCount();
	}
	else
	{

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(_OtherObj);
		if (pEnemy)
		{
			UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
			pEnemy->HPReduce((Atk));
			_OwnCollider->ResetOverlapCount();
		}
		

	}

}



void CGren::SetColliderSize(Vec2 _Size)
{

	m_Collider->SetScale(_Size);

}

void CGren::SetLvMaxAnimation()
{
	m_Animator->Play(L"Gren_Big", true);
}
