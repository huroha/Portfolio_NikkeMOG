#pragma once
#include "CObj.h"

class CTexture;


class CMissile :
    public CObj
{
private:
    CTexture* m_Texture;
    CCollider* m_Collider;
    Vec2    m_Velocity;
    float   m_Mass;

    float   m_LifeTime;
    float   m_LimitTime;

    UINT    m_StartWidth;


    CObj* m_TargetObj;
    float       m_DetectRange;

    bool        m_OneTime;

private:
    void FindTarget();
    void Trace();

public:
    void SetVelocity(Vec2 _vDir, float _Speed)
    {
        m_Velocity = _vDir;
        m_Velocity.Normalize();
        m_Velocity *= _Speed;
    }

    void AddVelocity(Vec2 _Accel)
    {
        m_Velocity += _Accel;

        if (m_Velocity.Length() > 1000.f)
        {
            m_Velocity.Normalize();
            m_Velocity *= 1000.f;
        }
    }

    void SetLifeTime(float _Limit) { m_LifeTime = _Limit; }

    Vec2 GetVelocity() { return m_Velocity; }

    float GetMass() { return m_Mass; }

    void SetMissileTexture(PREV_MOVE _PlayerPrevMove);
    void SetTexture(CTexture* _Tex) { m_Texture = _Tex; }

public:
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);


public:
    CLONE(CMissile);
    CMissile();
    CMissile(const CMissile& _Other);
    ~CMissile();
};

