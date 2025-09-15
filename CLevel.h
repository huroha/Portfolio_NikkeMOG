#pragma once
#include "CBase.h"

class CObj;
class CPlayer;
class CBoss;

class CLevel :
    public CBase
{
private:    
    vector<CObj*>   m_arrLayer[(int)LAYER_TYPE::END];
    CPlayer*        m_CurPlayer;
    CBoss*          m_CurBoss;

public:
    void AddObject(CObj* _Obj, LAYER_TYPE _Type);
    vector<CObj*>& GetLayer(LAYER_TYPE _Type) { return m_arrLayer[(int)_Type]; }



    void RegisterPlayer(CPlayer* _Player) { m_CurPlayer = _Player; }
    CPlayer* GetPlayer() { return m_CurPlayer; }
    void RegisterBoss(CBoss* _Boss) { m_CurBoss = _Boss; }
    CBoss* GetBoss() { return m_CurBoss; }

    void DeleteObjects(LAYER_TYPE _Type);
    void DeleteAllObjects();

    void ChangePauseState();

public:
    virtual void Init() = 0;
    virtual void Exit() = 0;

    virtual void Tick();
    virtual void FinalTick();
    virtual void Render();

public:
    CLONE_DISABLE(CLevel);
    CLevel();
    virtual ~CLevel();
};

