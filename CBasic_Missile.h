#pragma once
#include "CObj.h"

class CAnimator;


class CBasic_Missile :
    public CObj
{
private:
    CAnimator* m_Animator;

    float      m_LifeTime;
    Vec2       m_Velocity;
    float      m_Speed;

public:
    void    CheckVelocity();
    void    SetSpeed(float _speed) { m_Speed = _speed; }
    void    SetVelocity(Vec2 _velocity) { m_Velocity = _velocity; }
    void    SetVelocitySpeed(Vec2 _velocity, float _speed) 
    {
        m_Velocity = _velocity;
        m_Velocity.Normalize();
        m_Velocity *= _speed;
    }

    float   GetSpeed() { return m_Speed; }
    Vec2    GetVelocity() { return m_Velocity; }

    CAnimator* GetAnimator() { return m_Animator; }


public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CLONE(CBasic_Missile);
    CBasic_Missile();
    ~CBasic_Missile();
};

