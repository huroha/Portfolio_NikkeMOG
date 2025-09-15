#pragma once
#include "CState.h"
class CItem_Idle :
    public CState
{
private:
    float      m_LifeTime;
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    CLONE(CItem_Idle);
    CItem_Idle();
    ~CItem_Idle();
};

