#pragma once
#include "CUI.h"

class CTexture;

class CPanel_Tex :
    public CUI
{
private:
    CTexture*   m_Texture;

    bool        m_Visible;

    UINT        m_StartWidth;
    UINT        m_CutSize;
public:
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

    bool GetVisible() { return m_Visible; }
    void ChangeVisibleState() { m_Visible = !m_Visible; }
    void SetVisibleState(bool _check) { m_Visible = _check; }
    void SetCutSize(UINT _size) { m_CutSize = _size; }
    void SetStartWidth(UINT _start) { m_StartWidth = _start; }
public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;
    virtual void BeginHovered() override;


public:
    CLONE(CPanel_Tex);
    CPanel_Tex();
    ~CPanel_Tex();

};

