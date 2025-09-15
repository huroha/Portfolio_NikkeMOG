#pragma once
#include "CObj.h"

class CAnimator;

class CGren :
    public CObj
{
private:
    CAnimator*      m_Animator;
    CCollider*      m_Collider;

    float           m_LifeTime;     // 물체 살아있는 시간
    float           m_LimitTime;    // 무기군 활성화 최대 시간 제어용

    float           m_Radius;          // 회전에 필요한 변수들
    float           m_Angle;
    float           m_Speed;


    float           m_AddRadian;


public:


    void SetAddRadian(float _Radian) { m_AddRadian = _Radian; }     // 기본 150.f
    void SetSpeed(float _Speed) { m_Speed = _Speed; }               // 기본 300.f
    void SetAngle(float _Angle) { m_Angle = _Angle; }               // 기본 0.f

    void SetColliderSize(Vec2 _Size);
    void SetLvMaxAnimation();

public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);




public:
    CLONE(CGren);
    CGren();
    ~CGren();
};

