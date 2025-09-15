#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"
#include "CPathMgr.h"
#include "CDebugMgr.h"
#include "CTaskMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CAssetMgr.h"
#include "CLogMgr.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"
#include "CPauseMgr.h"


#include "CTexture.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_DC(nullptr)
	, m_BackBuffer(nullptr)
	, m_Pen{}
	, m_Brush{}	
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_DC);
	
	for (int i = 0; i < (int)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	for (int i = 0; i < (int)BRUSH_TYPE::HOLLOW; ++i)
	{
		DeleteObject(m_Brush[i]);
	}
}

void CEngine::Init(HWND _MainHwnd, UINT _Width, UINT _Height)
{
	m_hMainWnd = _MainHwnd;

	// DC(Device Context)
	// ȭ�鿡 �׸���(Rendering) �۾��� ����ϴ� ��ġ
	// �������� �ʿ��� ������ ����
	// Pen(Black), Brush(White), Bitmap
	m_DC = GetDC(m_hMainWnd);

	// ������ �ػ� ����
	ChangeWindowResolution(_Width, _Height);

	// ����� �� �ؽ��� ����
	m_BackBuffer = CAssetMgr::Get()->CreateTexture(L"BackBufferTex", _Width, _Height);

	// ���� ����� �� �� �귯�� ����
	CreateGDIObject();
	
	// Manager �ʱ�ȭ
	CPathMgr::Get()->Init();
	CTimeMgr::Get()->Init();
	CKeyMgr::Get()->Init();
	CSoundMgr::Get()->Init();
	CLevelMgr::Get()->Init();
	CPauseMgr::Get()->Init();


	CCamera::Get()->Init();
}


void CEngine::Progress()
{	
	CTimeMgr::Get()->Tick();
	CKeyMgr::Get()->Tick();
	CLevelMgr::Get()->Tick();
	CCollisionMgr::Get()->Tick();
	CCamera::Get()->Tick();
	CUIMgr::Get()->Tick();

	// Level ��ü�� ������
	Render();

	// ���� �����ӿ� ����Ǿ� �� �۾����� ó��
	CTaskMgr::Get()->Tick();
}

void CEngine::Render()
{
	// Rendering
	// ������ ȭ��(��Ʈ��) �� Ư�� �������� Clear ���ش�.
	SELECT_BRUSH(m_BackBuffer->GetDC(), BRUSH_TYPE::GRAY);
	Rectangle(m_BackBuffer->GetDC(), -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);	
	
	// ������ ��ü���� ȭ�鿡 ������
	CLevelMgr::Get()->Render();

	// Camera ������
	CCamera::Get()->Render();



	// Debug ������
	CDebugMgr::Get()->Tick();

#ifdef _DEBUG
	// Log ������
	CLogMgr::Get()->Tick();
#endif

	// BackBuffer �׸��� MainDC ���۷� ����
	BitBlt(m_DC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y
		 , m_BackBuffer->GetDC(), 0, 0, SRCCOPY);
}

void CEngine::CreateGDIObject()
{
	m_Pen[(int)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen[(int)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pen[(int)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_Pen[(int)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_Pen[(int)PEN_TYPE::MAGENTA] = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	m_Pen[(int)PEN_TYPE::TURQUOISE] = CreatePen(PS_SOLID, 1, RGB(57, 215, 237));
	m_Pen[(int)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));


	m_Brush[(int)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(int)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(int)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_Brush[(int)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_Brush[(int)BRUSH_TYPE::TURQUOISE] = CreateSolidBrush(RGB(57, 215, 237));	
	m_Brush[(int)BRUSH_TYPE::WHITE] = CreateSolidBrush(RGB(255, 255, 255));	
	m_Brush[(int)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}

HDC CEngine::GetBackDC()
{
	return m_BackBuffer->GetDC();
}

void CEngine::ChangeWindowResolution(UINT _Width, UINT _Height)
{
	// �����ϰ��� �ϴ� �ػ� ������ Engine ��ü�� ����
	m_Resolution.x = (float)_Width;
	m_Resolution.y = (float)_Height;

	// ũ�⸦ �����Ϸ��� �������� �޴� ���翩�θ� Ȯ��
	HMENU hMenu = GetMenu(m_hMainWnd);

	// �������� �׸��⿵��(��Ʈ��) �� �ػ󵵸� ���ϴ� ��ġ�� ����� ���ؼ�
	// ���� �����찡 ������ �ϴ� ũ�⸦ ���
	RECT rt = {0, 0, _Width, _Height};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, (bool)hMenu);

	// �������� ���� ������ ũ�Ⱚ���� ������ ũ�⸦ ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);	
}