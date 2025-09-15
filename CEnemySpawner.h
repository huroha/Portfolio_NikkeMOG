#pragma once
#include "CObj.h"

class CPlayer;
class CEnemy1;

class CEnemySpawner :
    public CObj
{

private:
    CPlayer*    m_Player;
    vector<CObj*>   m_EnemyLayer;

    float       m_CoolTime;

    UINT        m_SpawnLevel;
public:

    virtual void Tick() override;
public:
    CLONE(CEnemySpawner);
    CEnemySpawner();
    ~CEnemySpawner();
};

