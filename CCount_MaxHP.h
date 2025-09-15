#pragma once
#include "CCount_UI.h"
class CCount_MaxHP :
    public CCount_UI
{
private:
    UINT    m_MaxHP;
    UINT    m_StartWidth;

public:
    virtual void Render_UI() override;
    virtual void Tick_UI() override;

public:
    CLONE(CCount_MaxHP);
    CCount_MaxHP();
    ~CCount_MaxHP();
};

