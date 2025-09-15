#pragma once
#include "CObj.h"


class CUI :
    public CObj
{
private:
    CUI*            m_Parent;
    vector<CUI*>    m_vecChild;

    Vec2            m_FinalPos;

    bool            m_MouseOn;      // ���� ���콺�� UI ���� �ִ���
    bool            m_MouseOn_Prev; // ���� �����ӿ� ���콺�� UI ���� �־�����
    bool            m_LbtnDown;     // UI �� ���콺 ���ʹ�ư�� ���� ��������

public:
    CUI* GetParentUI() { return m_Parent; }
    const vector<CUI*>& GetChildUI() { return m_vecChild; }
    void AddChildUI(CUI* _ChildUI) 
    {
        m_vecChild.push_back(_ChildUI);
        _ChildUI->m_Parent = this;
    }



    Vec2 GetFinalPos() { return m_FinalPos; }

    bool IsLBtnDown() { return m_LbtnDown; }
    bool IsMouseOn() { return m_MouseOn; }

public:
    virtual void Tick() override final;
    virtual void Render() override final;


    virtual void Tick_UI() = 0;
    virtual void Render_UI();

    virtual void BeginHovered() {} // ���콺�� UI ���� �� �ö�Ϳ��� ��
    virtual void OnHovered() {}   // ���콺 UI ���� ���� ��
    virtual void EndHovered() {}  // ���콺�� UI �� ���� ������ ����

    virtual void LBtnDown() {}
    virtual void LBtnUp() {}
    virtual void LBtnClicked() {}

private:
    virtual void MouseOnCheck();

public:
    virtual CUI* Clone() override = 0;
    CUI();
    CUI(const CUI& _Other);
    ~CUI();

    friend class CUIMgr;
};

