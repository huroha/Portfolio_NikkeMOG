#include "pch.h"
#include "CEffectSpawner.h"
#include "CLevel.h"
#include "CLevelMgr.h"


CEffectSpawner::CEffectSpawner()
	: m_Enemy(nullptr)
	, m_EffectLayer{}
{
	m_EffectLayer = CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::EFFECT_DEAD);
}

CEffectSpawner::~CEffectSpawner()
{
}


void CEffectSpawner::Tick()
{
}

void CEffectSpawner::EffectOn(CObj* _Owner)
{

	for (int i = 0; i < 40; ++i)
	{
		if (m_EffectLayer[i]->IsDead() == true)
		{
			m_EffectLayer[i]->ChangeLifeState();
			m_EffectLayer[i]->SetPos(Vec2(_Owner->GetPos()));
			break;
		}
	}
}

void CEffectSpawner::EffectOn(CObj* _Owner, int _tail)
{
	
	if (m_EffectLayer[_tail]->IsDead() == true)
	{
		m_EffectLayer[_tail]->ChangeLifeState();
		m_EffectLayer[_tail]->SetPos(Vec2(_Owner->GetPos()));
	}
	


}
