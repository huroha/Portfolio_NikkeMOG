#pragma once
#include "CObj.h"
class CCR :
    public CObj
{

public:

    virtual void Tick() override;
    virtual void Render() override;

public:
    CLONE(CCR);
    CCR();
    ~CCR();
};

