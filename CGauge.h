#pragma once
#include "CUI.h"


class CPlayer;

class CGauge :
    public CUI
{
private:
    CPlayer*    m_Player;

    float       m_Gauge;

public:

    void SetPercent();
    CPlayer* GetPlayer() { return m_Player; }
    float   GetGauge() { return m_Gauge; }
    void SetGauge(float _Gauge);
public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    CLONE(CGauge);
    CGauge();
    ~CGauge();
};

