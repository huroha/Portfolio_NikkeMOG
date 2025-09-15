#include "pch.h"
#include "CCR.h"
#include "CEngine.h"


CCR::CCR()
{
}

CCR::~CCR()
{
}



void CCR::Tick()
{
}

void CCR::Render()
{
	SetBkMode(BackDC, TRANSPARENT);
	SetTextColor(BackDC, RGB(255, 255, 255)); // 글자색 변경

	wchar_t print_string[256] = {};
	swprintf_s(print_string, 256, L"제작자 Email : kmsms0306@naver.com");
	TextOut(BackDC, 10, 710, print_string, wcslen(print_string));
	
	wchar_t print_string2[256] = {};
	swprintf_s(print_string2, 256, L"produce by huroha");
	TextOut(BackDC, 10, 690, print_string2, wcslen(print_string2));


	wchar_t print_string3[256] = {};
	swprintf_s(print_string3, 256, L"**본 게임은 Nikke MOG의 팬 게임으로 상업적 용도로 사용할 수 없습니다**");
	TextOut(BackDC, 10, 730, print_string3, wcslen(print_string3));


}
