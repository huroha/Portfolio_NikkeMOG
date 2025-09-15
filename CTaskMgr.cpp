#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"

CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}


void CTaskMgr::Tick()
{
	// GC Clear
	for (size_t i = 0; i < m_GC.size(); ++i)
	{
		delete m_GC[i];
	}
	m_GC.clear();


	// Task ó��
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		ExcuteTask(m_vecTask[i]);
	}

	m_vecTask.clear();
}


void CTaskMgr::ExcuteTask(const tTask& _Task)
{
	switch (_Task.TaskType)
	{
	case TASK_TYPE::CREATE_OBJECT:
	{
		CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();

		CObj* pNewObject = (CObj*)_Task.Param_0;
		LAYER_TYPE LayerType = (LAYER_TYPE)_Task.Param_1;

		pCurLevel->AddObject(pNewObject, LayerType);
	}
		break;
	case TASK_TYPE::DELETE_OBJECT:
	{
		CObj* pObj = (CObj*)_Task.Param_0;

		// �̹� Dead ó���� ��ü�� �� ������û �� ��� ����ó��
		if (false == pObj->IsDead())
		{
			pObj->m_bDead = true;
			m_GC.push_back(pObj);
		}		
	}
		break;
	case TASK_TYPE::CHANGE_LEVEL:
	{
		LEVEL_TYPE type = (LEVEL_TYPE)_Task.Param_0;
		CLevelMgr::Get()->ChangeLevel(type);
	}
		break;	
	}	
}