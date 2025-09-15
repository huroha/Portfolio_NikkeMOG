#pragma once
#include "CMissileSpawner.h"
class CSpawner_Lapun :
    public CMissileSpawner
{
private:
    float           m_CoolTime;

    bool            m_Have;
    UINT            m_CheckInven;

    UINT            m_MissileCount;

public:



public:
    virtual void Tick() override;



public:
    CLONE(CSpawner_Lapun);
    CSpawner_Lapun();
    ~CSpawner_Lapun();
};

