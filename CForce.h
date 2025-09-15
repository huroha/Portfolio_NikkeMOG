#pragma once
#include "CObj.h"


class CForce :
    public CObj
{
private:
    float   m_Force;        // ���� ũ��
    float   m_Range;        // ���� ����Ǵ� ����
    float   m_Duration;     // ���� ������
    float   m_AccTime;      // ������ üũ��

public:
    void SetForce(float _ForceScale, float _Range)
    {
        m_Force = _ForceScale;
        m_Range = _Range;
    }

    void SetLifeTime(float _time) { m_Duration = _time; }


public:
    virtual void Tick() override;
    virtual void Render() override {}

public:
    CLONE(CForce);
    CForce();
    CForce(const CForce& _Other);
    ~CForce();
};

