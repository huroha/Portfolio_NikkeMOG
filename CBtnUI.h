#pragma once
#include "CUI.h"
#include "CPanel_Tex.h"

typedef void(*BTN_CALLBACK)(void);
typedef void(CBase::* BaseFunc)(void);
typedef void(CBase::* BaseFunc_Param1)(DWORD_PTR);
typedef void(CBase::* BaseFunc_Param2)(DWORD_PTR, DWORD_PTR);


class CBtnUI :
    public CUI
{
private:
    BTN_CALLBACK            m_CallBack;

    CBase*                  m_Inst;
    BaseFunc                m_MemFunc;
    BaseFunc_Param1         m_MemFunc_1;
    BaseFunc_Param2         m_MemFunc_2;

    DWORD_PTR               m_Param1;

    bool                    m_IsVisible;


public:
    void SetCallBack(BTN_CALLBACK _CallBack) { m_CallBack = _CallBack; }
    void SetDelegate(CBase* _Inst, BaseFunc _MemFunc)
    {
        m_Inst = _Inst;
        m_MemFunc = _MemFunc;
    }

    void SetDelegate(CBase* _Inst, BaseFunc_Param1 _MemFunc1 , DWORD_PTR _Param1)
    {
        m_Inst = _Inst;
        m_MemFunc_1 = _MemFunc1;
        m_Param1 = _Param1;

    }

    virtual void Tick_UI() override {};
    virtual void Render_UI() override;



public:
    virtual void LBtnDown() override;
    virtual void LBtnClicked() override;

public:
    CLONE(CBtnUI);
    CBtnUI();
    ~CBtnUI();
};

