#pragma once
#include "CCount_UI.h"
class CCount_Atk :
    public CCount_UI
{
private:

    UINT    m_Atk;
    UINT    m_StartWidth;

public:
    virtual void Render_UI() override;
    virtual void Tick_UI() override;

public:
    CLONE(CCount_Atk);
    CCount_Atk();
    ~CCount_Atk();
};

