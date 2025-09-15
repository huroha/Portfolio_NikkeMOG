#pragma once
#include "CMissileSpawner.h"
class CSpawner_Killo :
    public CMissileSpawner
{

private:
    bool            m_Have;
    UINT            m_CheckInven;

    UINT            m_Once;
public:



public:
    virtual void Tick() override;


public:
    CLONE(CSpawner_Killo);
    CSpawner_Killo();
    ~CSpawner_Killo();
};

