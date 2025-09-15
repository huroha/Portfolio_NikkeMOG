#pragma once
#include "CObj.h"


class CAnimator;

class CDig_Missile :
    public CObj
{

private:
    CAnimator* m_Animator;

    float      m_LifeTime;


public:



    
public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);


public:
    CLONE(CDig_Missile);
    CDig_Missile();
    ~CDig_Missile();
};

