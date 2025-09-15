#pragma once
#include "CUI.h"

class CTexture;
class CPlayer;

class CCount_UI :
    public CUI
{
    CTexture*       m_Texture;
    CPlayer*        m_Player;

    UINT            m_StartHeight;
    UINT            m_StartWidth;

    float            vStartPosx;
    float            vStartPosy;


    bool            m_Visible;

public:

    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    void SetTextColor(UINT _num);
    void SetStartPos(float _x, float _y) { vStartPosx = _x; vStartPosy = _y; }
    CTexture* GetTexture() { return m_Texture; }

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;
public:
    CLONE(CCount_UI);
    CCount_UI();
    ~CCount_UI();
};
