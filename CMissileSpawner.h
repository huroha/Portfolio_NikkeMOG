#pragma once
#include "CObj.h"
#include "CSound.h"
#include "CAssetMgr.h"


class CPlayer;

class CMissileSpawner :
    public CObj
{
private:
    CPlayer*        m_Player;
    vector<CObj*>   m_MissileLayer;
    Vec2            m_PrevMove;

    PREV_MOVE       m_Move;

public:
    virtual void Tick() override;

    Vec2 GetPrevMove();
    Vec2 GetMissleVelocity();

    vector<CObj*> GetMissileLayer() { return m_MissileLayer; }

    PREV_MOVE GetPlayerPrev();

    Vec2 GetPlayerPos();

public:
    CLONE(CMissileSpawner);
    CMissileSpawner();
    ~CMissileSpawner();
};

