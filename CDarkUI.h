#pragma once
#include "CUI.h"
class CDarkUI :
    public CUI
{
private:
    CTexture*   m_Texture;
       
    bool        m_Visible;


public:
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

    void ChangeVisibleState() { m_Visible = !m_Visible; }
    
public:
    virtual void Render_UI() override;
    virtual void Tick_UI() override;


public:
    CLONE(CDarkUI);
    CDarkUI();
    ~CDarkUI();


};

