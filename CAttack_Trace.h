#pragma once
#include "CState.h"
class CAttack_Trace :
    public CState
{

private:
    CBoss* m_Boss;

    float       m_CoolTime;
    UINT        m_ShootCount;

    bool        m_Wait;
public:


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CAttack_Trace);
    CAttack_Trace();
    ~CAttack_Trace();
};

