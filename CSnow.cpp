#include "pch.h"
#include "CSnow.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CEngine.h"
#include "CCollider.h"
#include "CEnemy.h"

#include "CTexture.h"
#include "CAssetMgr.h"
#include "CBoss.h"


CSnow::CSnow()
	: m_Animator(nullptr)
	, m_Texture(nullptr)
	, m_BoxLazer(nullptr)
	, m_LazerLifeTime(0.f)
	, m_StartWidth(0)
{
	m_BoxLazer = AddComponent(new CCollider);
	m_BoxLazer->SetScale(Vec2(30.f, 30.f));
}

CSnow::~CSnow()
{
}





void CSnow::Tick()
{
	// 구현 목표

	// 1. Prev 방향으로 Animation 진행과 동시에
	// 2. 일정 쿨타임이 돌면 Prev방향으로 빠르게 미사일 발사.
	Vec2 vPos = GetPos();

	// velocity를 스포너에서 받아와야함.

	vPos += m_Velocity * DT;
	SetPos(vPos);


	m_LazerLifeTime += DT;


	if (m_LazerLifeTime > 1.f)
	{
		SetDead(true);
		m_LazerLifeTime = 0;
	}


}

void CSnow::Render()
{

	Vec2 vPos = GetRenderPos();
	UINT width = m_Texture->GetWidth() / 8;
	UINT height = m_Texture->GetHeight();


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
		, width, height, m_Texture->GetDC(), width * m_StartWidth, 0, width, height, blend);

}

void CSnow::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Boss_Indivilia")
	{
		CBoss* pEnemy = dynamic_cast<CBoss*>(_OtherObj);
		UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
		pEnemy->HPReduce((Atk * 2));
		_OwnCollider->ResetOverlapCount();
	}
	else
	{
		CEnemy* pEnemy = dynamic_cast<CEnemy*>(_OtherObj);
		if (pEnemy)
		{
			UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
			pEnemy->HPReduce((Atk * 2));
			_OwnCollider->ResetOverlapCount();
		}
		
	}



}


void CSnow::SetColliderSize(Vec2 _size)
{
	m_BoxLazer->SetScale(_size);
}

void CSnow::LevelMaxTexture()
{
	m_Texture = CAssetMgr::Get()->LoadTexture(L"Snow_Lv5", L"texture\\snow_lv5.png");

}


void CSnow::SetMissileTexture(PREV_MOVE _PlayerPrevMove)
{
	m_StartWidth = UINT(_PlayerPrevMove);
	if (_PlayerPrevMove == PREV_MOVE::NONE)
		m_StartWidth = 4;

}