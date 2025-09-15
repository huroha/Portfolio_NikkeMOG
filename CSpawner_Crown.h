#pragma once
#include "CMissileSpawner.h"

class CSound;

class CSpawner_Crown :
    public CMissileSpawner
{
private:
    tWeaponInfo     m_Crown;

    float           m_CoolTime;
    bool            m_sec;
    bool            m_third;

    CSound*         m_sound;

public:
    virtual void Tick() override;
    
public:
    CLONE(CSpawner_Crown);
    CSpawner_Crown();
    ~CSpawner_Crown();
};

