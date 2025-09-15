#pragma once
#include "CCount_UI.h"
class CCount_Def :
    public CCount_UI
{
private:

    UINT    m_Def;
    UINT    m_StartWidth;

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    CLONE(CCount_Def);
    CCount_Def();
    ~CCount_Def();
};
