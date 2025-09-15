#pragma once
#include "CObj.h"

class CAnimator;
class CCollider;
class CRigidBody;
class CSpawner_Indi;

class CBoss :
    public CObj
{
private:
    CAnimator*      m_Animator;
    CCollider*      m_Collider;
    CRigidBody*     m_RigidBody;

    tEnemyInfo      m_Info;
    CSpawner_Indi*  m_MissileSpawner;

    bool            m_IsTrace;

    bool            m_CheckHit;
    UINT            m_DmgDelayCount;
    float           m_Time;
    float           m_Alpha;

public:
    const tEnemyInfo& GetMonsterInfo() { return m_Info; }

    CRigidBody* GetRigidBody() { return m_RigidBody; }
    CAnimator* GetAnimator() { return m_Animator; }
    CSpawner_Indi* GetMissileSpawner() { return m_MissileSpawner; }

    bool IsTrace() { return m_IsTrace; }
    void SetTrace(bool _IsTrace) { m_IsTrace = _IsTrace; }

    float GetAlpha() { return m_Alpha; }
    void Boss_Dead();
    void HPReduce(float _Dmg)
    {
        if(_Dmg > 0.f)
            m_Info.HP -= _Dmg; 
    }

public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);



public:
    CLONE(CBoss);
    CBoss();
    ~CBoss();

};

