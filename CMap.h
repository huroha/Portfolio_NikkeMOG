#pragma once
#include "CObj.h"
class CMap :
    public CObj
{
private:
    CTexture*       m_Texture;
    CCollider*      m_Collider;


public:
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    void SetColliderScale();
public:
    virtual void Tick() override;
    virtual void Render() override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) override;
public:
    CLONE(CMap);
    CMap();
    CMap(const CMap& _Other);
    ~CMap();
};

