#pragma once
#include "CState.h"

class CItem;

class CItem_Dead :
    public CState
{

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    CLONE(CItem_Dead);
    CItem_Dead();
    ~CItem_Dead();
};

