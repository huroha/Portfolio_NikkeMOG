#include "pch.h"
#include "CHP_bar.h"
#include "CEngine.h"
#include "CPlayer.h"
CHP_bar::CHP_bar()
{
	SetGauge(58.f);
}



CHP_bar::~CHP_bar()
{
}



void CHP_bar::Tick_UI()
{

	SetGauge(GetPlayer()->GetPlayerInfo().HP / GetPlayer()->GetPlayerInfo().MaxHP * 58.f);
}


void CHP_bar::Render_UI()
{

	SELECT_PEN(BackDC, PEN_TYPE::WHITE);
	SELECT_BRUSH(BackDC, BRUSH_TYPE::WHITE);


	Vec2 vPos = GetFinalPos();

	Rectangle(BackDC, vPos.x, vPos.y - 1.f
		, vPos.x + GetGauge(), vPos.y + 2.f);
}
