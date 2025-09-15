#include "pch.h"
#include "CLogMgr.h"

#include "CEngine.h"
#include "CTimeMgr.h"

CLogMgr::CLogMgr()
	: m_LogMaxLife(3.f)
	, m_LogStep(18)
{
}

CLogMgr::~CLogMgr()
{

}

void CLogMgr::Tick()
{
	list<tLog>::iterator iter = m_LogList.begin();

	int i = 0;
	for (iter; iter != m_LogList.end(); ++i)
	{
		// �α׸� ȭ�鿡 ��½�Ų��.
		Vec2 vLogPos = Vec2(10.f, 10.f + (float)(i * m_LogStep));

		// �α� ���ؿ����� ������ �ٸ��� �Ѵ�.
		switch ((*iter).Level)
		{
		case LOG_LEVEL::LOG:
			SetTextColor(BackDC, RGB(220, 220, 220));
			break;
		case LOG_LEVEL::WARNING:
			SetTextColor(BackDC, RGB(220, 220, 30));
			break;
		case LOG_LEVEL::BUG:
			SetTextColor(BackDC, RGB(240, 30, 30));
			break;	
		}

		SetBkMode(BackDC, TRANSPARENT);
		TextOut(BackDC, (int)vLogPos.x, (int)vLogPos.y, (*iter).strLog.c_str(), (*iter).strLog.length());

		// �α��� ������ �� �������� ����Ʈ���� �����Ѵ�.
		(*iter).Time += DT;
		if (m_LogMaxLife < (*iter).Time)
		{
			iter = m_LogList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
