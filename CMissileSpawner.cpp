#include "pch.h"
#include "CMissileSpawner.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"

#include "CPlayer.h"
#include "CMissile.h"
#include "CLogMgr.h"

CMissileSpawner::CMissileSpawner()
	: m_Player(nullptr)
	, m_MissileLayer{}
{
	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	m_MissileLayer = CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::PLAYER_PROJECTILE);


}

CMissileSpawner::~CMissileSpawner()
{
}



void CMissileSpawner::Tick()
{

}

Vec2 CMissileSpawner::GetPrevMove()
{
	m_Move = m_Player->GetPlayerInfo().PrevMove;

	Vec2 playerPos = m_Player->GetPos();
	Vec2 playerScale = Vec2(50.f, 60.f);


	if (m_Move == PREV_MOVE::LEFT_UP)
		return Vec2(playerPos.x - playerScale.x / 2, playerPos.y - playerScale.y / 2);
	else if (m_Move == PREV_MOVE::UP)
		return Vec2(playerPos.x, playerPos.y - playerScale.y / 2);
	else if (m_Move == PREV_MOVE::RIGHT_UP)
		return Vec2(playerPos.x + playerScale.x / 2, playerPos.y - playerScale.y / 2);
	else if (m_Move == PREV_MOVE::LEFT)
		return Vec2(playerPos.x - playerScale.x / 2, playerPos.y);
	else if (m_Move == PREV_MOVE::RIGHT)
		return Vec2(playerPos.x + playerScale.x / 2, playerPos.y);
	else if (m_Move == PREV_MOVE::LEFT_DOWN)
		return Vec2(playerPos.x - playerScale.x / 2, playerPos.y + playerScale.y / 2);
	else if (m_Move == PREV_MOVE::DOWN)
		return Vec2(playerPos.x, playerPos.y + playerScale.y / 2);
	else if (m_Move == PREV_MOVE::RIGHT_DOWN)
		return Vec2(playerPos.x + playerScale.x / 2, playerPos.y + playerScale.y / 2);
	else
		return Vec2(playerPos.x + playerScale.x / 2, playerPos.y);
}

Vec2 CMissileSpawner::GetMissleVelocity()
{
	m_Move = m_Player->GetPlayerInfo().PrevMove;


	if (m_Move == PREV_MOVE::LEFT_UP)
		return Vec2(-1.f,-1.f);
	else if (m_Move == PREV_MOVE::UP)
		return Vec2(0.f,-1.f);
	else if (m_Move == PREV_MOVE::RIGHT_UP)
		return Vec2(1.f,-1.f);
	else if (m_Move == PREV_MOVE::LEFT)
		return Vec2(-1.f,0.f);
	else if (m_Move == PREV_MOVE::RIGHT)
		return Vec2(1.f,0.f);
	else if (m_Move == PREV_MOVE::LEFT_DOWN)
		return Vec2(-1.f,1.f);
	else if (m_Move == PREV_MOVE::DOWN)
		return Vec2(0.f,1.f);
	else if (m_Move == PREV_MOVE::RIGHT_DOWN)
		return Vec2(1.f,1.f);
	else
		return Vec2(1.f,0.f);
}

PREV_MOVE CMissileSpawner::GetPlayerPrev()
{

	m_Move = m_Player->GetPlayerInfo().PrevMove;
	return m_Move;
}

Vec2 CMissileSpawner::GetPlayerPos()
{
	return m_Player->GetPos();
}




