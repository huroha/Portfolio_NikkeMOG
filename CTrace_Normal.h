#pragma once
#include "CState.h"
class CTrace_Normal :
    public CState
{
private:
    float   m_AttackRange;
    float   m_DetectRange;

    
    float   m_Cooltime;        // ���� ��Ÿ��

    UINT    m_RandomPattern;
    UINT    m_Seed;

    UINT    m_SpAttackCount;      // �̻��Ϲ߻縦 �������� �ΰ� ����Ƚ�� �߻��ϸ� ���� Ÿ������

    float   m_CutHP;


public:

    UINT RandomPatternChoose();


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CTrace_Normal);
    CTrace_Normal();
    ~CTrace_Normal();
};

