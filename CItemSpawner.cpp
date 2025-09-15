#include "pch.h"
#include "CItemSpawner.h"
#include "CEnemy.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLogMgr.h"


CItemSpawner::CItemSpawner()
	: m_Enemy(nullptr)
	, m_ItemLayer{}
{
	m_ItemLayer = CLevelMgr::Get()->GetCurrentLevel()->GetLayer(LAYER_TYPE::ITEM);

}

CItemSpawner::~CItemSpawner()
{
}




void CItemSpawner::Tick()
{
}

void CItemSpawner::DropItem(UINT _ItemChoose, CObj* _Owner)
{

	switch (_ItemChoose)
	{
	// ȸ��
	case 0:
	{
		for (int i = 0; i < 2; ++i)
		{
			if (m_ItemLayer[i]->IsDead() == true)
			{
				m_ItemLayer[i]->ChangeLifeState();
				m_ItemLayer[i]->SetPos(Vec2(_Owner->GetPos()));
				break;
			}
		}


	}
		break;
	// ����
	case 1:
	{
		for (int i = 5; i < 305; ++i)
		{
			if (m_ItemLayer[i]->IsDead() == true)
			{
				m_ItemLayer[i]->ChangeLifeState();
				m_ItemLayer[i]->SetPos(Vec2(_Owner->GetPos()));
				break;
			}
		}


	}
		break;
	// Exp ��
	case 2:
	{
		for (int i = 305; i < 605; ++i)
		{
			if (m_ItemLayer[i]->IsDead() == true)
			{
				m_ItemLayer[i]->ChangeLifeState();
				m_ItemLayer[i]->SetPos(Vec2(_Owner->GetPos()));
				break;
			}
		}

	}
		break;

	// Exp ��
	case 3:
	{
		for (int i = 605; i < 705; ++i)
		{
			if (m_ItemLayer[i]->IsDead() == true)
			{
				m_ItemLayer[i]->ChangeLifeState();
				m_ItemLayer[i]->SetPos(Vec2(_Owner->GetPos()));
				break;
			}
		}

	}
		break;

	// Exp ��
	case 4:
	{
		for (int i = 705; i < 750; ++i)
		{
			if (m_ItemLayer[i]->IsDead() == true)
			{
				m_ItemLayer[i]->ChangeLifeState();
				m_ItemLayer[i]->SetPos(Vec2(_Owner->GetPos()));
				break;
			}
		}

	}
		break;

	// �ñر� Up
	case 5:
		break;

	// �ڼ� ȿ��
	case 6:
		break;


	}



}

