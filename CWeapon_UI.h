#pragma once
#include "CUI.h"
class CWeapon_UI :
    public CUI
{
private:
    CTexture* m_Texture;
    CPlayer* m_Player;

    UINT        m_StartWidth;

public:
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    void CheckWeapon(UINT _order);

public:
    CLONE(CWeapon_UI);
    CWeapon_UI();
    ~CWeapon_UI();
};

