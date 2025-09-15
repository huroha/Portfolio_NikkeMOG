#include "pch.h"
#include "CTrace_Normal.h"
#include "CTimeMgr.h"

#include "CBoss.h"
#include "time.h"
#include "CRigidBody.h"
#include "CAnimator.h"

CTrace_Normal::CTrace_Normal()
	: m_AttackRange(0.f)
	, m_DetectRange(1200.f)
	, m_Cooltime(0.f)
	, m_RandomPattern(0)
	, m_SpAttackCount(0)
	, m_Seed(0)
	, m_CutHP(0.f)
{
	
	m_AttackRange = 600.f;

	

	/// �����Ұ�!
	m_CutHP = 6000.f;
}

CTrace_Normal::~CTrace_Normal()
{
}




void CTrace_Normal::Enter()
{
	m_Cooltime = 0;
	LOG(LOG_LEVEL::LOG, L"Normal����");

	
}

void CTrace_Normal::FinalTick()
{
	CBoss* pBoss = GetOwner<CBoss>();
	CPlayer* pPlayer = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
	Vec2 vDir = pPlayer->GetPos() - pBoss->GetPos();

	float distance = vDir.Length();

	m_Cooltime += DT;



	// Detect Range������ ��� ����
	if (distance < m_DetectRange)
	{
		vDir.Normalize();
		CRigidBody* Rigid = pBoss->GetRigidBody();
		Rigid->AddVelocity(vDir * 150.f);


		DrawDebugShape(DEBUG_SHAPE::CIRCLE, PEN_TYPE::BLUE, BRUSH_TYPE::HOLLOW
			, pBoss->GetRenderPos(), Vec2(m_AttackRange * 2.f, m_AttackRange * 2.f));


		// AttackRange ���ο� ������ ���� ��ȭ
		if (distance < m_AttackRange)
		{
			if (m_Cooltime > 3.5f)
			{

				m_RandomPattern = RandomPatternChoose();

				if (m_CutHP > pBoss->GetMonsterInfo().HP)
				{
					m_SpAttackCount = 0;
				}


				if (m_SpAttackCount == 4)
				{
					m_SpAttackCount = 0;
					GetStateMachine()->ChangeState(L"AttackState_Thunder");
				}

				else
				{

					switch (m_RandomPattern)
					{
						// ���� �߻� �⺻
					case 0:
					{
						if(m_CutHP < pBoss->GetMonsterInfo().HP)
							m_SpAttackCount += 1;
						GetStateMachine()->ChangeState(L"AttackState_1");
					}
					break;
					// ���� ��Ѹ��� �⺻
					case 1:
					{
						if (m_CutHP < pBoss->GetMonsterInfo().HP)
							m_SpAttackCount += 1;
						GetStateMachine()->ChangeState(L"AttackState_2");
					}
					break;
				
					case 2:
					{
						if (m_CutHP < pBoss->GetMonsterInfo().HP)
							m_SpAttackCount += 1;
						GetStateMachine()->ChangeState(L"AttackState_Trace");
					}
					break;
					}

				}


			}
			

		}

	}


	// ��ȭ �������� ���� ��ȭ
	else
	{
		GetStateMachine()->ChangeState(L"TraceState_Fast");
	}

}

void CTrace_Normal::Exit()
{
	//LOG(LOG_LEVEL::LOG, L"�߰� ����");
}



UINT CTrace_Normal::RandomPatternChoose()
{
	m_Seed += 3;
	srand(time(nullptr) + m_Seed);
	UINT random = rand() % 3;

	return random;
}
