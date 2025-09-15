#pragma once
#include "CCount_UI.h"
class CCount_Spd :
    public CCount_UI
{
private:

    UINT    m_Spd;
    UINT    m_StartWidth;

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    CLONE(CCount_Spd);
    CCount_Spd();
    ~CCount_Spd();
};

