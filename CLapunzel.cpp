#include "pch.h"
#include "CLapunzel.h"
#include "CCollider.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CEnemy.h"
#include "CBoss.h"

CLapunzel::CLapunzel()
	: m_Texture(nullptr)
	, m_Collider(nullptr)
	, m_Radius(100.f)
	, m_Angle(0.f)
	, m_Speed(200.f)
	, m_Dir(1)
	, m_Time(0.f)
	, m_Delay(0.f)
	, m_LifeTime(0.f)
	, m_LimitTime(4.f)
	, m_TextureSizeUp(0)
{
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(30.f, 30.f));
	
}

CLapunzel::~CLapunzel()
{
}



void CLapunzel::Tick()
{

	m_Delay += DT;
	m_LifeTime += DT;



	Vec2 playerPos = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer()->GetPos();

	// 각도 업데이트
	m_Angle += m_Speed * DT;
	if (m_Angle >= 360.0f)
		m_Angle -= 360.0f;

	// 오브젝트 위치 업데이트
	float radian = m_Angle * (PI / 180.0f);
	float x = m_Radius * cos(radian) * m_Dir;
	float y = m_Radius * sin(radian);

	playerPos.x += x;
	playerPos.y += y;

	SetPos(playerPos);

    

	if (m_LifeTime > m_LimitTime )
	{
		SetDead(true);
		m_LifeTime = 0;
	}



}

void CLapunzel::Render()
{


	Vec2 vPos = GetRenderPos();
	UINT width = m_Texture->GetWidth() - 10 + (m_TextureSizeUp*10);
	UINT height = m_Texture->GetHeight() - 40 + (m_TextureSizeUp * 10);


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
		, width , height, m_Texture->GetDC(), 0, m_TextureSizeUp*30, width , height, blend);

}


void CLapunzel::SetColliderSize(Vec2 _Size)
{

	m_Collider->SetScale(_Size);
}

void CLapunzel::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
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
