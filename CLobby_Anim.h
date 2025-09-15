#pragma once
#include "CObj.h"

class CAnimator;

class CLobby_Anim :
    public CObj
{
private:
    CAnimator* m_Animator;



public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CLONE(CLobby_Anim);
    CLobby_Anim();
    ~CLobby_Anim();
};

