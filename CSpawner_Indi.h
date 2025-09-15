#pragma once
#include "CObj.h"

class CBoss;

class CSpawner_Indi :
    public CObj
{
private:
    vector<CObj*>   m_BossProjectileLayer;
    CBoss*          m_Boss;

    float           m_CoolTime;
    UINT            m_ShootCount;


    float           m_Angle;
    Vec2            m_Round;

public:

    vector<CObj*> GetMissileLayer() { return m_BossProjectileLayer; }
    

    void DigAttack();
    void BasicAttack_1();
    void BasicAttack_2();


    void TraceAttack();

    void ThunderAttack();

public:
    virtual void Tick() override;


public:
    CLONE(CSpawner_Indi);
    CSpawner_Indi();
    ~CSpawner_Indi();

};

