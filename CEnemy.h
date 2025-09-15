#pragma once
#include "CObj.h"

class CCollider;
class CRigidBody;

class CEnemy :
    public CObj
{
private:
    tEnemyInfo    m_Info;

    CTexture*       m_Texture;
    CCollider*      m_Collider;

    CRigidBody*     m_RigidBody;


    bool            m_bStop;

    float           m_Time;

public:
    void SetTexture(CTexture* _tex) {  m_Texture = _tex; }
    const tEnemyInfo& GetMonsterInfo() { return m_Info; }

    void SetMonsterInfo(float _HP, float _MaxHP, float _Atk, float _Def, float _Speed, float _DetectRange);

    void HPReduce(float _Dmg)
    { 
        if(_Dmg > 0.f)
            m_Info.HP -= _Dmg;
    }
    void HPRestore(float _HP) { m_Info.HP = _HP; }
    void AtkUP(float _Atk) { m_Info.Atk = _Atk; }

    CCollider* GetCollider() { return m_Collider; }
    
    CRigidBody* GetRigidBody() { return m_RigidBody; }
    void  ChangeStop()
    {
        m_bStop = !m_bStop;
        m_Time = 0;
    }

    float  GetLifeTime() { return m_Time; }
    void   InitLifeTime() { m_Time = 0; }

public:
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

public:
    CLONE(CEnemy);
    CEnemy();
    CEnemy(const CEnemy& _Other);
    ~CEnemy();
};

