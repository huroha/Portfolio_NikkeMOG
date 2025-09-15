#pragma once
#include "CObj.h"

class CAnimator;

class CGren :
    public CObj
{
private:
    CAnimator*      m_Animator;
    CCollider*      m_Collider;

    float           m_LifeTime;     // ��ü ����ִ� �ð�
    float           m_LimitTime;    // ���ⱺ Ȱ��ȭ �ִ� �ð� �����

    float           m_Radius;          // ȸ���� �ʿ��� ������
    float           m_Angle;
    float           m_Speed;


    float           m_AddRadian;


public:


    void SetAddRadian(float _Radian) { m_AddRadian = _Radian; }     // �⺻ 150.f
    void SetSpeed(float _Speed) { m_Speed = _Speed; }               // �⺻ 300.f
    void SetAngle(float _Angle) { m_Angle = _Angle; }               // �⺻ 0.f

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

