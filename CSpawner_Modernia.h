#pragma once
#include "CMissileSpawner.h"
class CSpawner_Modernia :
    public CMissileSpawner
{
private:
    float           m_CoolTime;

    bool            m_Have;
    UINT            m_CheckInven;

public:
    virtual void Tick() override;


public:

    CLONE(CSpawner_Modernia);
    CSpawner_Modernia();
    ~CSpawner_Modernia();

};

