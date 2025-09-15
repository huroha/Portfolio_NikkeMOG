#pragma once
#include "CObj.h"

class CAnimator;
class CTexture;
class CCollider;
class CSound;

class CModernia :
    public CObj
{

private:
    CAnimator*  m_Animator;
    CCollider*   m_Collider;

    float       m_LifeTime;
    float       m_LimitTime;

    bool        m_Infinite;

    float       m_DelayDMG;
    float       m_DelayCool;
    bool        m_bDelay;

    Vec2        m_CurDir;

    UINT        m_Seed;
    UINT        m_Skill_Lv;

    CSound*     m_Sound;

public:
    virtual void Tick() override;
    virtual void Render() override;



    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    

    void ChangeLockOn();
    void SetColliderSize(Vec2 _Size);
    void OnOffCollider(bool _trigger);

    void SetLifeTime(float _time); 

    void LevelMax() { m_Infinite = true; }


    void SetDelayCool(float _Cool) { m_DelayCool = _Cool; }

    void PlaySoundModer();
    void StopSound();
    void ChangeAnimation(UINT _Level);

public:
    CLONE(CModernia);
    CModernia();
    ~CModernia();

};

