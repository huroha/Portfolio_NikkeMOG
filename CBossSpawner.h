#pragma once
#include "CObj.h"
class CBossSpawner :
    public CObj
{

private:
    vector<CObj*>   m_EnemyLayer;

    tPlayerInfo     m_CheckPlayerInfo;

    bool            m_Once;

public:
    virtual void Tick() override;

public:
    CLONE(CBossSpawner);
    CBossSpawner();
    ~CBossSpawner();
};

