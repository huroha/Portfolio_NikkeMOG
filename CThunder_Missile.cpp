#include "pch.h"
#include "CThunder_Missile.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CSound.h"

CThunder_Missile::CThunder_Missile()
	: m_Animator(nullptr)
	, m_Texture(nullptr)
	, m_LifeTime(0.f)
	, m_DelayTime(0.f)
	, m_StartAnim(false)
{
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(64.f, 37.f));
	m_Collider->SetOffset(Vec2(0.f, 114.f));
	m_Collider->Deactivate();
	

	m_Animator = AddComponent(new CAnimator);

	tAnimDesc desc = {};
	desc.AnimName = L"Thunder";
	desc.FPS = 30;
	desc.FrmCount = 8;
	desc.pAtlas = CAssetMgr::Get()->LoadTexture(L"ThunderAttack", L"texture\\thunder3.png");
	desc.SliceSize = Vec2(64.f, 256.f);
	desc.StartLeftTop = Vec2(0.f, 0.f);
	m_Animator->CreateAnimation(desc);

	
	m_Animator->Play(L"Thunder", true);
}

CThunder_Missile::~CThunder_Missile()
{
}






void CThunder_Missile::Tick()
{
	


	if (!IsDead())
	{
		m_LifeTime += DT;
		m_DelayTime += DT;
	}


	if (m_DelayTime > 2.f)
	{
		
		m_StartAnim = true;
		m_Collider->Activate();
		CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Lightning", L"sound\\Lightning.wav");
		pBGM->Play();
		pBGM->SetVolume(75.f);
		m_DelayTime = 0;

	}

	
	if (m_LifeTime > 2.5f)
	{
		ChangeLifeState();
		m_LifeTime = 0;
		m_DelayTime = 0;
		m_Animator->ResetAnim();
		m_Collider->Deactivate();
		m_StartAnim = false;
	}

}


void CThunder_Missile::Render()
{
	if(m_StartAnim)
		m_Animator->Render();

	else
	{
		Vec2 vPos = GetRenderPos();
		UINT width = m_Texture->GetWidth();
		UINT height = m_Texture->GetHeight();


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC, (int)vPos.x - width / 2, (int)vPos.y - height / 2
			, width, height, m_Texture->GetDC(), 0, 0, width, height, blend);

	}
}

void CThunder_Missile::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (UINT)LAYER_TYPE::PLAYER)
	{

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
		pPlayer->HPReduce_Dig();
	}


}
