#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_Frequency;	// 1�ʴ� ī���� ���� ��
	LARGE_INTEGER	m_CurrentCount;	// ���� ī����
	LARGE_INTEGER	m_PrevCount;	// ���� ������ ī����

	double			m_DT;		// DeltaTime : 1�����ӿ� �ɸ� �ð�
	float			m_fDT;		// DeltaTime : 1�����ӿ� �ɸ� �ð�
	double			m_Time;		// ���� �ð�

	double			m_Second;	// 1�� üũ �뵵 �����ð�

	UINT			m_FPS;


public:
	void Init();
	void Tick();

public:
	double GetDeltaTime_D() { return m_DT; }
	float GetDeltaTime() { return m_fDT; }
};

