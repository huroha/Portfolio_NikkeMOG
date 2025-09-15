#pragma once
#include "CState.h"
class CPlayer_MOVE :
    public CState
{

private:
    CAnimator* m_Animator;
    bool            m_Once;
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:


public:
    CLONE(CPlayer_MOVE);
    CPlayer_MOVE();
    ~CPlayer_MOVE();
};

