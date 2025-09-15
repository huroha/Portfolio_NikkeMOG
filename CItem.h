#pragma once
#include "CObj.h"

class CPlayer;

class CItem :
    public CObj
{

private:
    CTexture*       m_Texture;
    CPlayer*        m_Player;
    UINT            m_StartWidth;
    float           m_DetectRange;
    float           m_DeleteRange;
    float           m_Speed;


public:

    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    CTexture* GetTexture() { return m_Texture; }

    void DeleteAndGainExp();
    void DeleteAndGainExp_2();
    void DeleteAndGainExp_3();
    void DeleteAndGainCoin();
    void DeleteAndGainHP();

    float   GetDetectRange() { return m_DetectRange; }
    float   GetDeleteRange() { return m_DeleteRange; }

    float   GetSpeed() { return m_Speed; }

    CPlayer* GetPlayer() { return m_Player; }

    void ChooseItem(UINT _StartWidth) { m_StartWidth = _StartWidth; }
    void MagnetLevelUp() 
    { 
        m_DetectRange += 30.f;
        m_Speed += 80.f;
    }
    



public:
    virtual void Tick() override;
    virtual void Render() override;
public:
    CLONE(CItem);
    CItem();
    CItem(const CItem& _Other);
    ~CItem();
};

