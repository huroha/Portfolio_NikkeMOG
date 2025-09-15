#pragma once
#include "CUI.h"

class CPlayer;

class CPassive_UI :
    public CUI
{

private:
    CTexture*   m_Texture;
    CPlayer*    m_Player;

    UINT        m_StartWidth;

public:
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    void CheckPassive(UINT _order);

public:
    CLONE(CPassive_UI);
    CPassive_UI();
    ~CPassive_UI();
};

