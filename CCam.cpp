#include "pch.h"
#include "CCam.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"



CCam::CCam()
	: m_Collider(nullptr)
	, m_Player(nullptr)
{
	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(1280.f, 1280.f));
}

CCam::~CCam()
{

}


void CCam::Tick()
{
	SetPos(m_Player->GetPos());
}
