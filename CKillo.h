#pragma once
#include "CObj.h"


class CAnimator;
class CCollider;



class CKillo :
    public CObj
{
private:
    CAnimator*  m_Animator;
    CCollider*  m_Collider;


    float       m_DelayDMG;     // ���������� DT�� ���ϱ� ���� ��
    float       m_DelayCool;    
    bool        m_bDelay;


    float       m_WeaponAtk;

public:


    void OnOffCollider(bool _trigger);

    void SetColliderSize(Vec2 _Size);
    void ChangeDmgDelay(float _Delay) { m_DelayCool = _Delay; }         // �⺻ 0.1f
    void SetWeaponDMG(float _DMG) { m_WeaponAtk = _DMG; }               // �⺻ 0

    void SetLvMaxAnimation();

public:
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);



public:
    CLONE(CKillo);
    CKillo();
    ~CKillo();

};

