#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CLevelMgr.h"
#include "CLevel.h"
CCamera::CCamera()
	: m_CamSpeed(500.f)
	, m_BlackFilterTex(nullptr)
	, m_Frequency(0.f)
	, m_Amplitude(0.f)
	, m_Duration(0.f)
	, m_AccTime(0.f)
	, m_CamShake(false)
	, m_Player(nullptr)
	, m_FilterInfo{}
{	
	// Black Filter Texture ����
	Vec2 vResolution = CEngine::Get()->GetResolution();
	m_BlackFilterTex = CAssetMgr::Get()->CreateTexture(L"BlackFliterTex", (UINT)vResolution.x, (UINT)vResolution.y);
}

CCamera::~CCamera()
{
}

void CCamera::Test()
{
	m_Player = nullptr;
}

void CCamera::Init()
{
	Vec2 vResolution = CEngine::Get()->GetResolution();
	m_LookAt = vResolution / 2.f;
	CLevel* pLevel = CLevelMgr::Get()->GetCurrentLevel();
	if(pLevel->GetName() != L"Level_Edit")
		m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	else
	{
		m_Player = nullptr;
	}
}

void CCamera::Tick()
{
	if (m_Player)
		m_LookAt = m_Player->GetPos();
	//else
	//{
	//	if (KEY_PRESSED(KEY::W))
	//		m_LookAt.y -= m_CamSpeed * DT;

	//	if (KEY_PRESSED(KEY::S))
	//		m_LookAt.y += m_CamSpeed * DT;

	//	if (KEY_PRESSED(KEY::A))
	//		m_LookAt.x -= m_CamSpeed * DT;

	//	if (KEY_PRESSED(KEY::D))
	//		m_LookAt.x += m_CamSpeed * DT;
	//}
	
	// ī�޶� ȿ�� ����
	CameraEffect();
	
	// ī�޶� �����ִ� ������, �ػ� �߽���ġ�� ���̰�  CEngine::Get()->GetResolution() / 2.f
	m_LookAtDiff = (m_LookAt + m_ShakeOffset) - (CEngine::Get()->GetResolution() / 2.f);
}

void CCamera::Render()
{		
	if (m_FilterInfo.empty())
		return;
		
	FILTER_INFO& info = m_FilterInfo.front();

	UINT Alpha = 0;
	if (FILTER_EFFECT::FADE_OUT == info.Effect)
	{
		float fRatio = info.AccTime / info.Duration;
		Alpha = (UINT)(255.f * fRatio);
	}

	else if (FILTER_EFFECT::FADE_IN == info.Effect)
	{
		float fRatio = 1.f - (info.AccTime / info.Duration);
		Alpha = (UINT)(255.f * fRatio);
	}

	info.AccTime += DT;
	if (info.Duration < info.AccTime)
	{
		m_FilterInfo.pop_front();
	}

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = Alpha; // 0(����) ~ 255(������)
	blend.AlphaFormat = 0;
	
	AlphaBlend(BackDC, 0, 0
		, m_BlackFilterTex->GetWidth()
		, m_BlackFilterTex->GetHeight()
		, m_BlackFilterTex->GetDC()
		, 0, 0
		, m_BlackFilterTex->GetWidth()
		, m_BlackFilterTex->GetHeight()
		, blend);
}

void CCamera::CameraEffect()
{
	if (false == m_CamShake)
		return;

	// ī�޶� �̵� ����(1.f == �Ʒ�, -1.f == ��)	
	m_ShakeOffset.y += m_Amplitude * 4.f * m_Frequency * DT * m_Dir;

	// ���� ��ġ�� �Ѿ�� ������ ��ȯ�����ش�.
	if (m_Amplitude < fabs(m_ShakeOffset.y))
	{
		// �ʰ����� �ٽ� �������� �����Ų��.
		m_ShakeOffset.y += (fabs(m_ShakeOffset.y) - m_Amplitude) * -m_Dir;

		// ���� ��ȯ
		m_Dir *= -1.f;
	}

	// ȿ�� �����ð��� �� �Ǿ����� üũ
	m_AccTime += DT;
	if (m_Duration < m_AccTime)
	{
		// ȿ���� ����Ǹ� ���� �� ����
		m_AccTime = 0.f;
		m_CamShake = false;
		m_ShakeOffset = Vec2(0.f, 0.f);
	}
}