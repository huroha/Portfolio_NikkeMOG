#pragma once


class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr);
private:
	CLevel*		m_arrLevel[(int)LEVEL_TYPE::END];	// ��� ����
	CLevel*		m_CurLevel; // ���� ������ ����

public:
	CLevel* GetCurrentLevel() { return m_CurLevel ; }

public:
	void Init();
	void Tick();
	void Render();

private:
	void ChangeLevel(LEVEL_TYPE _Type);
	friend class CTaskMgr;
};

