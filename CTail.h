#pragma once
#include "CObj.h"

class CBoss;
class CAnimator;

class CTail :
    public CObj
{

private:
    CBoss* m_Boss;
    CAnimator* m_Animator;


    float   m_Alpha;
    float   m_HpCheck;
public:
    virtual void Tick() override;
    virtual void Render() override;


    float GetAlpha() { return m_Alpha; }
public:
    CLONE(CTail);
    CTail();
    ~CTail();

};

