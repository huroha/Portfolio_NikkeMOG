#include "pch.h"
#include "CLobby_Anim.h"
#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include "CKeyMgr.h"
#include "CLogMgr.h"



CLobby_Anim::CLobby_Anim()
	: m_Animator(nullptr)
{

	m_Animator = AddComponent(new CAnimator);
	tAnimDesc desc = {};
	desc.AnimName = L"Main";
	desc.FPS = 20;
	desc.FrmCount = 32;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"Lobby", L"texture\\Lobby.png");
	desc.SliceSize = Vec2(1280.f, 768.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);
	//m_Animator->SaveAnimation(L"animation\\Lobby\\");
	//m_Animator->LoadAnimation(L"animation\\Player\\IDLE_LEFT.anim");

	m_Animator->Play(L"Main",true);

}

CLobby_Anim::~CLobby_Anim()
{
}
void CLobby_Anim::Tick()
{

}

void CLobby_Anim::Render()
{
	m_Animator->Render();
}
