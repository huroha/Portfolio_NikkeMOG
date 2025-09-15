#include "pch.h"
#include "CGauge.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CEngine.h"

CGauge::CGauge()
	: m_Player(nullptr)
	, m_Gauge(0.f)
{
	m_Player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();
}

CGauge::~CGauge()
{

}



void CGauge::SetPercent()
{

	m_Gauge = m_Player->GetPlayerInfo().Exp;
	

}

void CGauge::SetGauge(float _Gauge)
{
	if (_Gauge <= 0)
	{
		m_Gauge = 0;
	}
	else {
		m_Gauge = _Gauge;
	}

}

void CGauge::Tick_UI()
{
	SetPercent();

}

void CGauge::Render_UI()
{
	SELECT_PEN(BackDC, PEN_TYPE::TURQUOISE);
	SELECT_BRUSH(BackDC, BRUSH_TYPE::TURQUOISE);


	Vec2 vPos = GetFinalPos();

	Rectangle(BackDC, vPos.x , vPos.y -3.f
		, vPos.x + m_Gauge, vPos.y  +3.f);


}
