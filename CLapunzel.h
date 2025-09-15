#pragma once
#include "CObj.h"

class CTexture;
class CCollider;


class CLapunzel :
    public CObj
{

private:
    CTexture*    m_Texture;
    CCollider*   m_Collider;

    float        m_Radius;
    float        m_Angle;
    float        m_Speed;
    int          m_Dir;

    float        m_Delay;
    float        m_Time;


    float        m_LifeTime;
    float        m_LimitTime;

    UINT         m_TextureSizeUp;


public:

    void SetTexture(CTexture* _Tex) { m_Texture = _Tex; }
    
public:
    void SetRadius(float _radius) { m_Radius = _radius; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void ChangeDir(int _dir) { m_Dir = _dir; }      // +1 이면 시계방향 -1 시계 반대방향
    void SetTime(float _time) { m_Time = _time; }
    void SetDelay(float _delay) { m_Delay = _delay; }
    void SetAngle(float _Angle) { m_Angle = _Angle; }



    void SetTextureSizeUp() { m_TextureSizeUp = 1; }
    void SetColliderSize(Vec2 _Size); 

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:

    virtual void Tick() override;
    virtual void Render() override;




public:
    CLONE(CLapunzel);
    CLapunzel();
    ~CLapunzel();
};

