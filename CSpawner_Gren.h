#pragma once
#include "CMissileSpawner.h"
class CSpawner_Gren :
    public CMissileSpawner
{
private:
    float           m_CoolTime;

    bool            m_Have;
    UINT            m_CheckInven;

    UINT            m_MissileCount;

public:
    virtual void Tick() override;


public:
    CLONE(CSpawner_Gren);
    CSpawner_Gren();
    ~CSpawner_Gren();
};

