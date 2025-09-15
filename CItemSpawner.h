#pragma once
#include "CObj.h"


class CEnemy;

class CItemSpawner :
    public CObj
{
private:
    CEnemy*          m_Enemy;
    vector<CObj*>    m_ItemLayer;

public:
    virtual void Tick() override;

    void DropItem(UINT _ItemChoose, CObj* _Owner);
public:
    CLONE(CItemSpawner);
    CItemSpawner();
    ~CItemSpawner();

};





