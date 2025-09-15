#pragma once
#include "CState.h"

class CBoss;

class CTrace_Fast :
    public CState
{
private:
    CBoss*      m_Boss;
    float       m_DigAttackRange;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CTrace_Fast);
    CTrace_Fast();
    ~CTrace_Fast();
};

