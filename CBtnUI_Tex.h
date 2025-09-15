#pragma once

#include "CBtnUI.h"

class CTexture;

class CBtnUI_Tex :
    public CBtnUI
{
private:
    CTexture*       m_NormalImg;

    UINT            m_StartWidth;
    UINT            m_StartHeight;
    UINT            m_SizeW;
    UINT            m_SizeH;
    bool            m_Visible;
    bool            m_ChangeWidth;
public:

    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    void SetTexture(CTexture* _tex) { m_NormalImg = _tex; }

    void SetCutSizeW(UINT _size) { m_SizeW = _size; }
    void SetCutSizeH(UINT _size) { m_SizeH = _size; }


    void SetChangeWidth(bool _change) { m_ChangeWidth = _change; }
    void SetStartHeight(UINT _start) { m_StartHeight = _start; }
    void SetStartWidth(UINT _start) { m_StartWidth = _start; }

public:
    CLONE(CBtnUI_Tex);
    CBtnUI_Tex();
    ~CBtnUI_Tex();
};

