#pragma once
#include "CCount_UI.h"
class CCount_Skill :
    public CCount_UI
{
private:
    UINT    m_StartWidth;

public:
    void SetStartWidth(UINT _start) { m_StartWidth = _start; }

    virtual void Tick_UI() override; 
    virtual void Render_UI() override;

public:
    CLONE(CCount_Skill);
    CCount_Skill();
    ~CCount_Skill();
};

