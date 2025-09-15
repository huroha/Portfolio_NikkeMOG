#include "pch.h"
#include "CEnemy.h"


#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include "CTimeMgr.h"

#include "CTexture.h"

#include "CStateMachine.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"


#include "CRigidBody.h"






CEnemy::CEnemy()
	: m_Texture(nullptr)
	, m_Info{}
	, m_bStop(false)
	, m_Time(0.f)
{
	m_Info.DetectRange = 100.f;
	m_Info.Speed = 100.f;


	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(50.f, 50.f));


	// RigidBody 추가
	m_RigidBody = AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::PLATFOMER);
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxSpeed(100.f);
	m_RigidBody->SetFriction(1000.f);


	// State
	//CStateMachine* pSM = AddComponent(new CStateMachine);
	//pSM->AddState(L"IdleState", new CIdleState);
	//pSM->AddState(L"TraceState", new CTraceState);
	//pSM->AddState(L"AttackState", new CAttackState);

	//pSM->ChangeState(L"IdleState");

	// Search

}

CEnemy::CEnemy(const CEnemy& _Other)
	: CObj(_Other)
	, m_Info(_Other.m_Info)
	, m_Texture(_Other.m_Texture)
	, m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Time(0.f)
	, m_bStop(false)
{
	m_Collider = GetComponent<CCollider>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CEnemy::~CEnemy()
{
}



void CEnemy::Tick()
{
	// Player 를 추적한다.
	m_Time += DT;


	// 움찔거림 추가
	if (!m_bStop && m_Time > 0.2f)
	{
		CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
		Vec2 vDir = pPlayer->GetPos() - GetPos();
		vDir.Normalize();
		m_RigidBody->AddVelocity(vDir * 100.f);
	}



}

void CEnemy::Render()
{
	HDC dc = CEngine::Get()->GetBackDC();

	Vec2 vPos = GetRenderPos();	
	UINT width = m_Texture->GetWidth();
	UINT height = m_Texture->GetHeight();
	
	// TransparentBlt
	/*{
		TransparentBlt(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, m_Texture->GetDC(), 0, 0, width, height, RGB(255, 0, 255));
	}*/

	// AlphaBlending
	{
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;
				
		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
				  , width, height, m_Texture->GetDC(), 0, 0, width, height, blend);
	}
}

void CEnemy::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	return;

	/*if (L"Player" == _OtherObj->GetName())
	{
		DeleteObject(this);
	}*/


}



void CEnemy::SetMonsterInfo(float _HP, float _MaxHP, float _Atk, float _Def, float _Speed, float _DetectRange)
{
	m_Info.HP = _HP;
	m_Info.MaxHP = _MaxHP;
	m_Info.Atk = _Atk;
	m_Info.Def = _Def;
	m_Info.Speed = _Speed;
	m_Info.DetectRange = _DetectRange;
}
