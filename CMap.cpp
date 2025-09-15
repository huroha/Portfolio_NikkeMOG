#include "pch.h"
#include "CMap.h"
#include "CCollider.h"
#include "CEngine.h"
#include "CLogMgr.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CCam.h"
#include "CTexture.h"


CMap::CMap()
	: m_Texture(nullptr)
	, m_Collider(nullptr)
{

	m_Collider = AddComponent(new CCollider);
}

CMap::CMap(const CMap& _Other)
	: CObj(_Other)
	, m_Texture(_Other.m_Texture)
	, m_Collider(_Other.m_Collider)
{
	m_Collider = GetComponent<CCollider>();
}

CMap::~CMap()
{
}

void CMap::SetColliderScale()
{
	m_Collider->SetScale(GetScale());
}

void CMap::Tick()
{

}

void CMap::Render()
{
	//Vec2 vRenderPos = GetRenderPos();

	//SELECT_PEN(BackDC, PEN_TYPE::BLUE);
	//SELECT_BRUSH(BackDC, BRUSH_TYPE::BLUE);


	//Rectangle(BackDC, vRenderPos.x - (GetScale().x/ 2.f), vRenderPos.y - (GetScale().y / 2.f)
	//	, vRenderPos.x + (GetScale().x / 2.f), vRenderPos.y + (GetScale().y / 2.f));
	HDC dc = CEngine::Get()->GetBackDC();

	Vec2 vPos = GetRenderPos();
	UINT width = m_Texture->GetWidth();
	UINT height = m_Texture->GetHeight();


	// AlphaBlending

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
		, width, height, m_Texture->GetDC(), 0, 0, width, height, blend);
	
}

void CMap::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	
	LOG(LOG_LEVEL::WARNING, GetName().c_str());

	CCam* pCam = dynamic_cast<CCam*>(_OtherObj);

	CPlayer* pPlayer = pCam->GetPlayer();

	                                                                
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMapPos = GetPos();

	float diffx = abs(vPlayerPos.x - vMapPos.x);
	float diffy = abs(vPlayerPos.y - vMapPos.y);

	Vec2 vPlayeDir = pPlayer->GetRigidBody()->GetVelocity();
	float dirx = vPlayeDir.x < 0 ? -1 : 1;
	float diry = vPlayeDir.y < 0 ? -1 : 1;

	if (diffx > diffy)
		SetPos(GetPos().x + (1.0f * dirx * GetScale().x ), GetPos().y);
	else if (diffx < diffy)
	{
		SetPos(GetPos().x,GetPos().y + (1.0f * diry * GetScale().y ));
	}

}




