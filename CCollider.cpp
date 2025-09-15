#include "pch.h"
#include "CCollider.h"

#include "CDebugMgr.h"
#include "CCollisionMgr.h"

#include "CCamera.h"

CCollider::CCollider()
	: CComponent(COMPONENT_TYPE::COLLIDER)
	, m_OverlapCount(0)
	, m_State(ACTIVE)
{
}

CCollider::CCollider(const CCollider& _Other)
	: CComponent(_Other)
	, m_OffsetPos(_Other.m_OffsetPos)
	, m_Scale(_Other.m_Scale)
	, m_OverlapCount(0)
	, m_State(_Other.m_State)
{
}

CCollider::~CCollider()
{
}

void CCollider::Activate()
{
	m_State = ACTIVE;
}

void CCollider::Deactivate()
{
	m_State = SEMIDEACTIVE;
}

void CCollider::FinalTick()
{
	if (DEACTIVE == m_State)
		return;
	else if (SEMIDEACTIVE == m_State)
		m_State = DEACTIVE;

	// �浹ü�� ���� ��ġ ���
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	// �浹ü�� ���̾� ��ȣ�� �°� �浹�Ŵ����� ���
	CCollisionMgr::Get()->RegisterCollider(this, (LAYER_TYPE)GetOwner()->GetLayerType());

	// �浹ü�� ����� ������ ��û
	Vec2 vRenderPos = CCamera::Get()->GetRenderPos(m_FinalPos);

	if(m_OverlapCount != 0)
		DrawDebugShape(DEBUG_SHAPE::RECT, PEN_TYPE::RED, BRUSH_TYPE::HOLLOW, vRenderPos, m_Scale);
	else
		DrawDebugShape(DEBUG_SHAPE::RECT, PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW, vRenderPos, m_Scale);
}

void CCollider::BeginOverlap(CCollider* _Other)
{
	++m_OverlapCount;

	GetOwner()->BeginOverlap(this, _Other->GetOwner(), _Other);	
}

void CCollider::Overlap(CCollider* _Other)
{
	GetOwner()->Overlap(this, _Other->GetOwner(), _Other);
}

void CCollider::EndOverlap(CCollider* _Other)
{
	--m_OverlapCount;

	GetOwner()->EndOverlap(this, _Other->GetOwner(), _Other);	
}
