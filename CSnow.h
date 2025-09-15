#pragma once
#include "CObj.h"


class CAnimator;


class CSnow :
    public CObj
{

private:
    CAnimator*  m_Animator;
    CTexture*   m_Texture;
    CCollider*  m_BoxLazer;

    Vec2        m_Velocity;
    float       m_LazerLifeTime;

    UINT        m_StartWidth;


public:

    void SetVelocity(Vec2 _vDir, float _Speed)
    {
        m_Velocity = _vDir;
        m_Velocity.Normalize();
        m_Velocity *= _Speed;
    }


    void SetMissileTexture(PREV_MOVE _PlayerPrevMove);


public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

    void SetColliderSize(Vec2 _size);

    void LevelMaxTexture();
public:
    CLONE(CSnow);
    CSnow();
    ~CSnow();
};

