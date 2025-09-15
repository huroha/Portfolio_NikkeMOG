#pragma once
#include "CEnemy.h"

class CAnimator;
class CRigidBody;
class CTexture;

class CEnemy1 :
    public CEnemy
{
private:
    CAnimator*      m_Animator;

    UINT            m_Rand;
    UINT            m_Seed;


    bool            m_CheckHit;
    UINT            m_DmgDelayCount;
    float           m_Time;
    float           m_Alpha;

public:
    virtual void Render() override;
    virtual void Tick() override;
    
    void Dead();


    void ChangeEnemy();
    void SetEnemy2Collider();

    float GetAlpha() { return m_Alpha; }

    void InitHit()
    {
        m_CheckHit = false;
        m_Alpha = 255.f;
    }

public:

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
public:
    CLONE(CEnemy1);
    CEnemy1();
    CEnemy1(const CEnemy1& _Other);
    ~CEnemy1();

};

