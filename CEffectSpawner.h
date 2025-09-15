#pragma once
#include "CObj.h"

class CEnemy;

class CEffectSpawner :
    public CObj
{
private:
    CEnemy*          m_Enemy;
    vector<CObj*>    m_EffectLayer;

public:
    virtual void Tick() override;

    void EffectOn(CObj* _Owner);
    void EffectOn(CObj* _Owner, int _tail);
public:
    CLONE(CEffectSpawner);
    CEffectSpawner();
    ~CEffectSpawner();

};

