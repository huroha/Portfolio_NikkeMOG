#pragma once
#include "CState.h"

class CIdleState :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CIdleState);
    CIdleState();
    ~CIdleState();
};

