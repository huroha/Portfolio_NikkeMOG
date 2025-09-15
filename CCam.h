#pragma once
#include "CObj.h"

class CCollier;
class CPlayer;
class CCam :
    public CObj
{
private:
    CCollider*  m_Collider;
    CPlayer*    m_Player;
public:
    CPlayer* GetPlayer() { return m_Player; }
    virtual void Tick() override;
public:
    CLONE(CCam);
    CCam();
    ~CCam();

};

