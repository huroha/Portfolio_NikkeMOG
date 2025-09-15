#pragma once
#include "CMissileSpawner.h"
class CSpawner_Snow :
    public CMissileSpawner
{
private:
    float           m_CoolTime;

    bool            m_Have;
    UINT            m_CheckInven;

    UINT            m_MissileCount;

public:
    virtual void Tick() override;

    PREV_MOVE ReversePrevMove(PREV_MOVE _Prev);
public:

    CLONE(CSpawner_Snow);
    CSpawner_Snow();
    ~CSpawner_Snow();
};

