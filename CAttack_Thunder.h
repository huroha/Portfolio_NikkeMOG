#pragma once
#include "CState.h"
class CAttack_Thunder :
    public CState
{
private:
    CBoss* m_Boss;

    float       m_CoolTime;
    UINT        m_ShootCount;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;


public:
    CLONE(CAttack_Thunder);
    CAttack_Thunder();
    ~CAttack_Thunder();

};

