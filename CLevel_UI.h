#pragma once
#include "CUI.h"
class CLevel_UI :
    public CUI
{
private:

    CTexture*       m_Texture;
    UINT            m_StartWidth;
    UINT            m_StartHeight;

public:

    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    void SetLevelTex();
public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;
public:
    CLONE(CLevel_UI);
    CLevel_UI();
    ~CLevel_UI();

};

