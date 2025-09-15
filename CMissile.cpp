#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CTexture.h"
#include "CBoss.h"

CMissile::CMissile()
	: m_Texture(nullptr)
	, m_Collider(nullptr)
	, m_Velocity(1.f, 0.f)
	, m_Mass(1.f)
	, m_LifeTime(0.f)
	, m_LimitTime(1.f)
	, m_StartWidth(0)
	, m_TargetObj(nullptr)
	, m_DetectRange(500.f)
	, m_OneTime(false)
{
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(20.f, 20.f));
}

CMissile::CMissile(const CMissile& _Other)
	: CObj(_Other)
	, m_Texture(_Other.m_Texture)
	, m_Collider(nullptr)
	, m_Velocity(0.f, 0.f)
	, m_Mass(1.f)
	, m_LifeTime(0.f)
	, m_LimitTime(5.f)
	, m_StartWidth(0)
	, m_TargetObj(nullptr)
	, m_DetectRange(_Other.m_DetectRange)
	, m_OneTime(false)
{
	m_Collider = GetComponent<CCollider>();
}

CMissile::~CMissile()
{
}



void CMissile::SetMissileTexture(PREV_MOVE _PlayerPrevMove)
{
	m_StartWidth = UINT(_PlayerPrevMove);
	if (_PlayerPrevMove == PREV_MOVE::NONE)
		m_StartWidth = 4;

}

void CMissile::Tick()
{
	if (m_TargetObj == nullptr && m_OneTime == false)
	{

		m_OneTime = true;
		FindTarget();



		if (IsValid(m_TargetObj))
		{
			Trace();
		}


	}
		

	// 2. 타겟을 추적한다.
	


	Vec2 vPos = GetPos();

	vPos += m_Velocity * DT;

	SetPos(vPos);

	m_LifeTime += DT;

	if (m_LifeTime > m_LimitTime)
	{
		SetDead(true);
		m_TargetObj = nullptr;
		m_LifeTime = 0;
		m_OneTime = false;
	}



}

void CMissile::Render()
{
	Vec2 vPos = GetRenderPos();
	UINT width = m_Texture->GetWidth();
	UINT height = m_Texture->GetHeight();


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
		, width, height, m_Texture->GetDC(), 0 , 0, width, height, blend);

}

void CMissile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (!IsDead())
	{
		if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::ENEMY)
		{
			SetDead(true);
			_OwnCollider->ResetOverlapCount();
			m_TargetObj = nullptr;
			m_OneTime = false;
		}
	}
	

	if (_OtherObj->GetName() == L"Boss_Indivilia")
	{
		CBoss* pEnemy = dynamic_cast<CBoss*>(_OtherObj);
		UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
		pEnemy->HPReduce((Atk));
	}
	else
	{

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(_OtherObj);
		if (pEnemy)
		{
			UINT Atk = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPlayerInfo().Atk;
			pEnemy->HPReduce((Atk));
		}
	
	}


}



void CMissile::FindTarget()
{
	if (IsValid(m_TargetObj))
		return;

	// 탐지범위
	float MinDist = m_DetectRange;

	// 미사일의 위치
	Vec2 vMissilePos = GetPos();

	// 미사일(본인)과 가장 가까운 몬스터를 찾는다.
	CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetLayer(LAYER_TYPE::ENEMY);

	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		if (vecMon[i]->IsDead() == true)
			continue;
		Vec2 vDiff = vecMon[i]->GetPos() - vMissilePos;
		float Dist = vDiff.Length();

		//float Dist = vMissilePos.Distance(vecMon[i]->GetPos());

		if (Dist < MinDist)
		{
			MinDist = Dist;
			m_TargetObj = vecMon[i];
			
		}
	}
}



void CMissile::Trace()
{
	Vec2 vDir = m_TargetObj->GetPos() - GetPos();
	vDir.Normalize();
	SetVelocity(vDir, 500.f);
	 
	//Vec2 vDir = m_TargetObj->GetPos() - GetPos();
	//vDir.Normalize();
	//Vec2 vForce = vDir * 2000.f;
	//Vec2 Accel = vForce / GetMass();
	//AddVelocity(Accel * DT);

}
