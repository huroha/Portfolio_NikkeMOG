#pragma once
#include "CGauge.h"
class CHP_bar :
    public CGauge
{


public:
    virtual void Render_UI() override;
    virtual void Tick_UI() override;

public:
    CLONE(CHP_bar);
    CHP_bar();
    ~CHP_bar();
};

