#pragma once
#include "CObj.h"

class CTexture;
class CCollider;
class CAnimator;
class CRigidBody;
class CStateMachine;
class CPanel_Tex;
class CSound;

class CPlayer :
    public CObj
{
private:
    CTexture*       m_Texture;
    CCollider*      m_Body;
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CStateMachine*  m_SM;

    CPanel_Tex*     m_Skill;

    tPlayerInfo     m_Info;
    

    CSound*         m_Sound[(UINT)PlayerVoice::END];


    float           m_Time2;            // 피격 후 무적 임시
    int             m_DmgDelayCount;

    float           m_BustTime;
    bool            m_SkillCool;
    bool            m_AccessSkill;



    bool            m_InCountBoss;
    float           m_Alpha;
    bool            m_CheckHit;

    UINT            m_SoundCheck;

public:
    void GainExp(float _Exp);

    void CoinCountUp(UINT _Coin)
    { 
        m_Info.Coin += _Coin;
        if (m_Info.Coin > 9999)
        {
            m_Info.Coin = 9999;
        }
    }
    void SlayCountUp()
    { 
        m_Info.SlayCount += 1;
        if (m_Info.SlayCount > 9999)
        {
            m_Info.SlayCount = 9999;
        }
    }
    void HPRestore();
    void HPReduce_Dig();
    void HPReduce(float _Dmg);

    bool IsBossInCount() { return m_InCountBoss; }
    void SetBossInCount(bool _Incount) { m_InCountBoss = _Incount; }
    int Reroll_Buy()
    {
        if (m_Info.Coin > 9)
        {
            m_Info.Coin -= 10;
            return 1;
        }
        return 0;
    }

    UINT GetPassiveLevel(PlayerPassive _Passive);
    UINT GetWeaponLevel(PlayerWeapon _Weapon);
    
    void RegistBustUI(CPanel_Tex* _UI) { m_Skill = _UI; }


    float GetAlpha() { return m_Alpha; }
    void SetCheckHit(bool _check) { m_CheckHit = _check; }

public:
    void LevelUp_Passive(PlayerPassive _PassiveName, UINT _PassiveLevel);
    void LevelUp_Weapon(PlayerWeapon _WeaponName, UINT _WeaponLevel);



public:

    void Skill_On();
    void Skill_Off();


    bool IsSkillCool() { return m_SkillCool; }
    void AccessSkill(bool _check) { m_AccessSkill = _check; }
    bool IsAccess() { return m_AccessSkill; }


    void PlayVoice(PlayerVoice _choice);

 // 패시브와 무기 추가
public:
    void GainPassive(PlayerPassive _PassiveName);
    void GainWeapon(PlayerWeapon _WeaponName);


public:
    CAnimator* GetAnim() { return m_Animator; }
    CRigidBody* GetRigidBody() { return m_RigidBody; }
    const tPlayerInfo& GetPlayerInfo() { return m_Info; }

   


public:
    virtual void Tick() override;    
    virtual void Render() override;


public:
    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
public:
    CLONE(CPlayer);
    CPlayer();
    CPlayer(const CPlayer& _Other);
    ~CPlayer();
};

