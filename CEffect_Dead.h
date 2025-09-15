#pragma once
#include "CObj.h"

class CAnimator;
class CTexture;

class CEffect_Dead :
    public CObj
{
private:
    CAnimator*      m_Animator;
    CTexture*       m_Texture;

    float           m_LifeTime;
    float           m_LimitTime;

public:
    virtual void Tick() override;
    virtual void Render() override;

    void ChangeAnim();

    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    void SetLimitTime(float _limit) { m_LimitTime = _limit; }
public:
    CLONE(CEffect_Dead);
    CEffect_Dead();
    ~CEffect_Dead();
};

