#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"


CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_CurrentCount{}
	, m_PrevCount{}
	, m_DT(0.)
	, m_fDT(0.f)
	, m_Time(0.)
	, m_FPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::Tick()
{
	QueryPerformanceCounter(&m_CurrentCount);

	m_DT = (double)(m_CurrentCount.QuadPart - m_PrevCount.QuadPart) / (double)m_Frequency.QuadPart;

	// DT ����, 60 ���� 1 ���� ũ�� ���ϰ� ����
	if ((1.f / 60.f) < m_DT)
		m_DT = (1.f / 60.f);

	m_fDT = (float)m_DT;
	
	// �ð� ����
	m_Time += m_DT;

	// �ð� ����
	m_Second += m_DT;

	// �Լ� ȣ��Ƚ��
	++m_FPS;

	if (1. < m_Second)
	{
		m_Second -= 1.;

		//// ������ Ÿ��Ʋ�� FPS �� DeltaTime ǥ��
		//wchar_t buff[256] = {};
		//swprintf_s(buff, 256, L"FPS : %d, DeltaTime : %f", m_FPS, m_fDT);
		//SetWindowText(CEngine::Get()->GetMainHwnd(), buff);

		m_FPS = 0;
	}

	m_PrevCount = m_CurrentCount;
}