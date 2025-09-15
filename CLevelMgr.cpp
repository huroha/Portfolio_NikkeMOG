#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"

#include "CLevel.h"
#include "CLevel_Start.h"
#include "CLevel_Editor.h"

#include "CPlayer.h"
#include "CEnemy.h"

#include "CCollisionMgr.h"
#include "CPauseMgr.h"


CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_CurLevel(nullptr)
{}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		if(nullptr != m_arrLevel[i])
			delete m_arrLevel[i];
	}	
}

void CLevelMgr::Init()
{
	// Level ����
	m_arrLevel[(int)LEVEL_TYPE::START] = new CLevel_Start;
	m_arrLevel[(int)LEVEL_TYPE::START]->SetName(L"Level_Start");
	m_arrLevel[(int)LEVEL_TYPE::EIDTOR] = new CLevel_Editor;
	m_arrLevel[(int)LEVEL_TYPE::EIDTOR]->SetName(L"Level_Edit");

	m_CurLevel = m_arrLevel[(int)LEVEL_TYPE::EIDTOR];
	m_CurLevel->Init();
}

void CLevelMgr::Tick()
{
	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}

void CLevelMgr::Render()
{
	m_CurLevel->Render();
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	// ���� ���� ������ Exit
	if (nullptr != m_CurLevel)
	{
		m_CurLevel->Exit();
	}

	// ���ο� ������ ����Ű��, �ʱ�ȭ(Init) �� �صд�.
	m_CurLevel = m_arrLevel[(int)_Type];
	m_CurLevel->Init();
	CPauseMgr::Get()->CheckLevel();

}
