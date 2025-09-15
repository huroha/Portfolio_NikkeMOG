#pragma once
#include "CState.h"
class CTrace_Normal :
    public CState
{
private:
    float   m_AttackRange;
    float   m_DetectRange;

    
    float   m_Cooltime;        // 패턴 쿨타임

    UINT    m_RandomPattern;
    UINT    m_Seed;

    UINT    m_SpAttackCount;      // 미사일발사를 조건으로 두고 일정횟수 발사하면 범위 타격으로

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

