#pragma once
#include "CLevel.h"

class CPanel_Tex;
class CDarkUI;

class CLevel_Start :
    public CLevel
{
private:
    CPanel_Tex* m_PauseMenu;

    CPanel_Tex* m_SkillMenu;
    CPanel_Tex* m_ResultMenu;
    CDarkUI*    m_DarkFilter;



    bool        m_IsWeapon[3];
    UINT        m_ChoosePassive[3];
    UINT        m_ChooseWeapon[3];
    UINT        m_Seed;



public:
    virtual void Init() override;   // 레벨 초기화
    virtual void Exit() override;   // 레벨을 종료할때 수행

    virtual void Tick() override;


    void PasueMenu();
    void QuitGame();
    CPanel_Tex* GetPauseMenu() { return m_PauseMenu; }

    CPanel_Tex* GetResultMenu() { return m_ResultMenu; }
    CDarkUI* GetDarkFilter() { return m_DarkFilter; }

public:

    void VisibleSkill_BG(const tPlayerInfo& _Info, bool _Reroll);

    void ReStartLobby();

    void LevelUP_1();
    void LevelUP_2();
    void LevelUP_3();
    void ReRoll();


public:    
    CLevel_Start(const CLevel_Start& _Other) = delete;
    CLevel_Start();
    ~CLevel_Start();
};

