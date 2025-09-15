#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CPauseMgr.h"

CLevel::CLevel()
	: m_CurPlayer(nullptr)
{
}

CLevel::~CLevel()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		Release_Vector(m_arrLayer[i]);
	}	
}

void CLevel::Tick()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsPause() != true && m_arrLayer[i][j]->IsDead() != true)
				m_arrLayer[i][j]->Tick();
		}
	}
}


void CLevel::FinalTick()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if(m_arrLayer[i][j]->IsPause() != true && m_arrLayer[i][j]->IsDead() != true)
				m_arrLayer[i][j]->FinalTick();
		}
	}
}

void CLevel::Render()
{
	//
	//for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	//{
	//	vector<CObj*>& vecObj = m_arrLayer[i];

	//	vector<CObj*>::iterator iter = vecObj.begin();
	//	for (; iter != vecObj.end(); )
	//	{
	//		if ((*iter)->IsDead())
	//		{
	//			//(*iter)->ChangeLifeState();
	//			//iter = vecObj.erase(iter);
	//			++iter;
	//		}
	//		else
	//		{
	//			if ((*iter)->IsLife())
	//			{
	//				(*iter)->Render();
	//				++iter;
	//			}
	//		}		
	//	}
	//}


	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if ( m_arrLayer[i][j]->IsDead() != true)
				m_arrLayer[i][j]->Render();
		}
	}
}

void CLevel::AddObject(CObj* _Obj, LAYER_TYPE _Type)
{
	m_arrLayer[(int)_Type].push_back(_Obj);
	_Obj->m_LayerType = (int)_Type;
}

void CLevel::DeleteObjects(LAYER_TYPE _Type)
{
	vector<CObj*>& vecObj = m_arrLayer[(int)_Type];
	Release_Vector(vecObj);
}

void CLevel::DeleteAllObjects()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		DeleteObjects((LAYER_TYPE)i);
	}
}

void CLevel::ChangePauseState()
{
	for (int i = 0; i < (int)LAYER_TYPE::UI; ++i)
	{
		for (int j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->ChangePauseState();
		}
	}

}

