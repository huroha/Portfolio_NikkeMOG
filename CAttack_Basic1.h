#pragma once
#include "CState.h"
class CAttack_Basic1 :
    public CState
{

private:
    CBoss*      m_Boss;

    float       m_CoolTime;
    float       m_RepeatTime;
    UINT        m_ShootCount;
    
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;


public:
    CLONE(CAttack_Basic1);
    CAttack_Basic1();
    ~CAttack_Basic1();
};

