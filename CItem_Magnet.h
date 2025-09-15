#pragma once
#include "CState.h"
class CItem_Magnet :
    public CState
{
private:
    bool        m_TurnDead;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    CLONE(CItem_Magnet);
    CItem_Magnet();
    ~CItem_Magnet();

};

