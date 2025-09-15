#pragma once
#include "CBase.h"

#include "CCamera.h"

class CComponent;
class CCollider;

class CObj :
    public CBase
{
private:
    Vec2                m_Pos;
    Vec2                m_Scale;
    vector<CComponent*> m_vecComponent;
    int                 m_LayerType;
    bool                m_bDead;

    bool                m_bPause;

public:
    Vec2 GetPos() { return m_Pos; }
    Vec2 GetRenderPos();
    
    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }

    Vec2 GetScale() { return m_Scale; }
    virtual void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    virtual void SetScale(float _Width, float _Height) { m_Scale.x = _Width; m_Scale.y = _Height; }
    
    bool IsDead() { return m_bDead; }
    void SetDead(bool _life) { m_bDead = _life; }

    CComponent* GetComponent(COMPONENT_TYPE _Type);
    CComponent* GetComponentByName(const wstring& _Name);

    int GetLayerType() { return m_LayerType; }

    void ChangePauseState() { m_bPause = !m_bPause; }
    bool   IsPause() { return m_bPause; }
    void SetPause(bool _pasue) { m_bPause = _pasue; }

    void ChangeLifeState() 
    {
        m_bDead = !m_bDead;
    }


    template<typename T>
    T* AddComponent(T* _Comonent);

    template<typename T>
    T* GetComponent();

public:
    // ���� �Լ�
    virtual void Tick() = 0;
    virtual void FinalTick() final;
    virtual void Render();

    virtual void BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {};
    virtual void Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {};
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider) {};

public:
    virtual CObj* Clone() = 0;
    CObj();
    CObj(const CObj& _Other);
    virtual ~CObj();

    friend class CLevel;
    friend class CTaskMgr;
};

template<typename T>
inline T* CObj::AddComponent(T* _Comonent)
{
    m_vecComponent.push_back(_Comonent);
    _Comonent->m_Owner = this;
    return _Comonent;
}

template<typename T>
inline T* CObj::GetComponent()
{
    for (size_t i = 0; i < m_vecComponent.size(); ++i)
    {
        T* pComponent = dynamic_cast<T*>(m_vecComponent[i]);
        if (pComponent)
            return pComponent;
    }

    return nullptr;
}
