#include "pch.h"
#include "CPauseMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CAssetMgr.h"
#include "CSound.h"

CPauseMgr::CPauseMgr()
	: m_CurLevel(nullptr)
{

}

CPauseMgr::~CPauseMgr()
{

}

void CPauseMgr::Init()
{
	m_CurLevel = CLevelMgr::Get()->GetCurrentLevel();

}

void CPauseMgr::CheckLevel()
{
	m_CurLevel = CLevelMgr::Get()->GetCurrentLevel();
}

void CPauseMgr::ChangePauseState()
{
	m_CurLevel->ChangePauseState();
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Pause", L"sound\\Pause.wav");
	pBGM->Play();
	pBGM->SetVolume(10.f);
}


