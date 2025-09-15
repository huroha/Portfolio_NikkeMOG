#pragma once

#include "CComponent.h"

enum class RIGIDBODY_MODE
{
    TOPVIEW,
    PLATFOMER,
};

class CRigidBody :
    public CComponent
{
private:
    RIGIDBODY_MODE      m_Mode;
    Vec2                m_Force;            // ���� �� (ũ�� + ����)
    Vec2                m_Velocity;         // �ӵ�    (ũ�� + ����)
    Vec2                m_GravidyVelocity;

    float               m_Mass;             // ����
    float               m_Friction;         // �������
    float               m_MaxSpeed;         // �ִ� �ӷ� ����
    float               m_GravityAccel;     // �߷°��ӵ� ũ��
    float               m_GravityMaxSpeed;  // �߷����� ���ؼ� �߻��ϴ� �ӵ��� �ִ� ����ġ
    float               m_JumpSpeed;
    bool                m_IsMove;           // ���� ������Ʈ�� �����̴� ������ �ƴ��� üũ
    bool                m_IsGound;          // �������� ���ִ��� ����
    bool                m_UseGravity;

public:
    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetMaxSpeed(float _Max) { m_MaxSpeed = _Max; }
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }
    void SetFriction(float _Friction) { m_Friction = _Friction; }
    void SetMode(RIGIDBODY_MODE _Mode) { m_Mode = _Mode; }
    void SetGravityAccelScale(float _Accel) { m_GravityAccel = _Accel; }
    void SetMaxGravitySpeed(float _Max) { m_GravityMaxSpeed = _Max; }
    void UseGravity(bool _Use) { m_UseGravity = _Use; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }

    void SetGround(bool _Ground);

    void Jump();

    Vec2 GetVelocity() { return m_Velocity; }
    Vec2 GetForce() { return m_Force; }
    float GetMass() { return m_Mass; }
    float GetMaxSpeed() { return m_MaxSpeed; }


    RIGIDBODY_MODE GetMode() { return m_Mode; } 
    bool IsMove() { return m_IsMove; }

public:
    virtual void FinalTick() override;

public:
    CLONE(CRigidBody);
    CRigidBody();
    CRigidBody(const CRigidBody& _Other);
    ~CRigidBody();
};

 