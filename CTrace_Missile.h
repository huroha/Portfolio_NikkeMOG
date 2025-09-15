#pragma once
#include "CBasic_Missile.h"
class CTrace_Missile :
    public CBasic_Missile
{
private:
    CPlayer*    m_TargetPlayer;

    float       m_DetectRange;
    float       m_RotateSpeed;
    float       m_Speed2;

    float       m_HP;

public:
    virtual void Tick() override;


    void SetSpeed2(float _speed) { m_Speed2 = _speed; }

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
  

private:
    void Trace();



public:
    CLONE(CTrace_Missile);
    CTrace_Missile();
    CTrace_Missile(const CTrace_Missile& _Other);
    ~CTrace_Missile();
};

