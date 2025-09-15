#pragma once
#include "CState.h"
#include "CObj.h"
class CPlayer_IDLE :
    public CState
{
private:
    CAnimator*      m_Animator;
    bool            m_Once;
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    

public:
    CLONE(CPlayer_IDLE);
    CPlayer_IDLE();
    ~CPlayer_IDLE();
};

