#include "pch.h"
#include "CGuidedMissile.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CEnemy.h"

#include "CTimeMgr.h"
#include "CPlayer.h"

CGuidedMissile::CGuidedMissile()
	: m_TargetObj(nullptr)
	, m_DetectRange(500.f)
	, m_RotateSpeed(180.f)
{
}

CGuidedMissile::CGuidedMissile(const CGuidedMissile& _Other)
	: CMissile(_Other)
	, m_TargetObj(nullptr)
	, m_DetectRange(_Other.m_DetectRange)
	, m_RotateSpeed(_Other.m_RotateSpeed)
{
}

CGuidedMissile::~CGuidedMissile()
{
}

void CGuidedMissile::Tick()
{
	/*DrawDebugShape(DEBUG_SHAPE::CIRCLE, PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW
		         , GetPos(), Vec2(m_DetectRange * 2.f, m_DetectRange * 2.f));*/



	// 1. ������ ����� ã�´�.
	//  - �̻���(����)�κ��� ���� ����� ����� ã�´�.
	FindTarget();
	
	// 2. Ÿ���� �����Ѵ�.
	if (IsValid(m_TargetObj))
	{
		Trace();
	}
	
	// 3. ������ ����(����) �� ����(�̻���)�� �̵���Ų��.
	CMissile::Tick();
}

void CGuidedMissile::FindTarget()
{
	if (nullptr != m_TargetObj)
		return;

	// Ž������
	float MinDist = m_DetectRange;

	// �̻����� ��ġ
	Vec2 vMissilePos = GetPos();

	// �̻���(����)�� ���� ����� ���͸� ã�´�.
	CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetLayer(LAYER_TYPE::ENEMY);
		
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		//Vec2 vDiff = vecMon[i]->GetPos() - vMissilePos;
		//float Dist = vDiff.Length();
	
		float Dist = vMissilePos.Distance(vecMon[i]->GetPos());

		if (Dist < MinDist)
		{
			MinDist = Dist;
			m_TargetObj = vecMon[i];
		}
	}
}

void CGuidedMissile::Trace()
{
	/*{
		Vec2 vDir = m_TargetObj->GetPos() - GetPos();
		vDir.Normalize();
		SetVelocity(vDir, 500.f);
	}*/

	//// ��, ���ӵ�
	//{
	//	Vec2 vDir = m_TargetObj->GetPos() - GetPos();
	//	vDir.Normalize();
	//	Vec2 vForce = vDir * 2000.f;
	//	Vec2 Accel = vForce / GetMass();
	//	AddVelocity(Accel * DT);
	//}

	// ���� ȸ�� 
	{
		// ���� �̵����� ����
		Vec2 vCurDir = GetVelocity();
		float speed = vCurDir.Length();
		vCurDir.Normalize();

		Vec2 vTargetDir = m_TargetObj->GetPos() - GetPos();

		//vCurDir.x;    vCurDir.y;      0.f;   vCurDir.x;      vCurDir.y;
		//vTargetDir.x; vTargetDir.y;   0.f;   vTargetDir.x;   vTargetDir.y;
		// 0.f, 0.f, vCurDir.x* vTargetDir.y - vCurDir.y * vTargetDir.x;
		if (0.f < vCurDir.x * vTargetDir.y - vCurDir.y * vTargetDir.x)
		{
			vCurDir = RotateDir(vCurDir, m_RotateSpeed * DT);
		}
		else
		{
			vCurDir = RotateDir(vCurDir, -m_RotateSpeed * DT);
		}

		SetVelocity(vCurDir, speed);
	}
}