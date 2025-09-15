#pragma once
#include "CBtnUI.h"
class CBtnBust_UI :
    public CBtnUI
{

private:
    CTexture*       m_Texture;
    UINT            m_StartWidth;
    UINT            m_StartHeight;
    float           m_Time;
    UINT            m_CutSize;


    bool            m_IsCool;

    UINT            m_Count;

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    void SetCutSize(UINT _size) { m_CutSize = _size; }


public:
    void SetStartWidth(UINT _start) { m_StartWidth = _start; }
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

public:
    CLONE(CBtnBust_UI);
    CBtnBust_UI();
    ~CBtnBust_UI();
};

