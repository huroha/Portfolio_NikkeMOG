#include "pch.h"
#include "CPanel_Anim.h"
#include "CAnimator.h"
#include "CPanel_Tex.h"
#include "CAssetMgr.h"


CPanel_Anim::CPanel_Anim()
	: m_Animator(nullptr)
	, m_Visible(true)
{
	m_Animator = AddComponent(new CAnimator);

	m_Animator->LoadAnimation(L"animation\\Player\\IDLE_LEFT.anim");

	m_Animator->Play(L"IDLE_LEFT", true);
}

CPanel_Anim::~CPanel_Anim()
{
}


void CPanel_Anim::Tick_UI()
{
	CPanel_Tex* pParent = dynamic_cast<CPanel_Tex*>(GetParentUI());
	if(pParent!= nullptr)
		m_Visible = pParent->GetVisible();
	FinalTick();
}

void CPanel_Anim::Render_UI()
{
	if (m_Visible)
	{
		m_Animator->Render();
	}
	if (GetName() == L"ResultPlayer")
	{
		int a = 0;
		m_Visible;

	}
}
