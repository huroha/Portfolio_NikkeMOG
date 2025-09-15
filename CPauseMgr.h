#pragma once

class CLevel;

class CPauseMgr
{

	SINGLE(CPauseMgr);
private:
	CLevel*		m_CurLevel;


public:
	void Init();


	void CheckLevel();
	void ChangePauseState();
};

