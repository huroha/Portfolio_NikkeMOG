#pragma once
#include "CObj.h"

class CAnimator;
class CTexture;
class CCollider;

class CThunder_Missile :
    public CObj
{
private:
    CAnimator*  m_Animator;
    CTexture*   m_Texture;
    CCollider* m_Collider;


    float       m_LifeTime;
    float       m_DelayTime;
    bool        m_StartAnim;

public:
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }



    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CLONE(CThunder_Missile);
    CThunder_Missile();
    ~CThunder_Missile();

};

