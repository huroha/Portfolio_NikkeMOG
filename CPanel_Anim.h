#pragma once
#include "CUI.h"


class CAnimator;

class CPanel_Anim :
    public CUI
{
private:
    CAnimator*  m_Animator;
    bool        m_Visible;

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    CLONE(CPanel_Anim);
    CPanel_Anim();
    ~CPanel_Anim();

    
};

