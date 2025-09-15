#include "pch.h"
#include "CLevel_Editor.h"

#include "CLogMgr.h"
#include "CPathMgr.h"

#include "CKeyMgr.h"
#include "CTile.h"
#include "resource.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAssetMgr.h"

#include "CEngine.h"
#include "CTileMap.h"

#include "CBtnUI.h"
#include "CPanel.h"
#include "CUIMgr.h"

#include "CSound.h"

#include "resource.h"

#include "CBtnUI_Tex.h"
#include "CLogMgr.h"
#include "CLobby_Anim.h"

#include "CCR.h"


void TestFunc2()
{
	ChangeLevel(LEVEL_TYPE::START);
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"StartBtn", L"sound\\StartBtn.wav");
	pBGM->Play();
	pBGM->SetVolume(10.f);
	CCamera::Get()->SetFilterEffect(FADE_IN, 0.3f);
}



CLevel_Editor::CLevel_Editor()
	: m_hMenu(nullptr)
	, m_TileMap(nullptr)
{
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_PORTFOLIOMOG));
}

CLevel_Editor::~CLevel_Editor()
{
	DestroyMenu(m_hMenu);
}


void CLevel_Editor::Init()
{
	// BGM 지정
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"Lobby", L"sound\\Last_Kingdom.wav");
	pBGM->PlayToBGM(true);
	pBGM->SetVolume(10.f);

	// 메뉴 따위 없음
	SetMenu(CEngine::Get()->GetMainHwnd(), nullptr);

	// 다시 윈도우 크기 재계산
	UINT width = CEngine::Get()->GetResolution().x;
	UINT height = CEngine::Get()->GetResolution().y;
	CEngine::Get()->ChangeWindowResolution(width, height);


	CCamera::Get()->Init();

	// 뒷배경

	


	// Title
	CPanel_Tex* pTitle = new CPanel_Tex;
	pTitle->SetTexture(CAssetMgr::Get()->LoadTexture(L"Title", L"texture\\Title_t.png"));
	pTitle->SetPos(Vec2(width/2 + 8.f,height/2 -190.f));
	AddObject(pTitle, LAYER_TYPE::UI);


	// side
	CPanel_Tex* pSide = new CPanel_Tex;
	pSide->SetTexture(CAssetMgr::Get()->LoadTexture(L"Side", L"texture\\lobbyside.png"));
	pSide->SetPos(Vec2(width / 2, height / 2 + 200.f));
	AddObject(pSide, LAYER_TYPE::UI);

	// Start Btn
	CBtnUI_Tex* pStartBtn = new CBtnUI_Tex;
	pStartBtn->SetTexture(CAssetMgr::Get()->LoadTexture(L"StartBtn", L"texture\\start_540.png"));
	pStartBtn->SetPos(Vec2(-130.f, -20.f));
	pStartBtn->SetScale(Vec2(270.f, 78.f));
	pStartBtn->SetCutSizeW(2);
	pStartBtn->SetChangeWidth(true);
	pStartBtn->SetCallBack(&TestFunc2);
	pSide->AddChildUI(pStartBtn);




	CLobby_Anim* pMain = new CLobby_Anim;
	pMain->SetPos(Vec2(width/2, height/2));
	AddObject(pMain, LAYER_TYPE::BACKGROUND);


	CCR* pCCR = new CCR;
	AddObject(pCCR, LAYER_TYPE::BACKGROUND);


}

void CLevel_Editor::Exit()
{

	// 오브젝트 삭제
	DeleteAllObjects();
}

void CLevel_Editor::Tick()
{
	CLevel::Tick();



}

void CLevel_Editor::TileMode()
{
	Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();
	vMousePos = CCamera::Get()->GetRealPos(vMousePos);

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 TileSize = m_TileMap->GetTileSize();

		UINT Col = vMousePos.x / TileSize.x;
		UINT Row = vMousePos.y / TileSize.y;

		tTileInfo* pTileInfo = m_TileMap->GetTileInfo(Col, Row);

		if (nullptr != pTileInfo)
		{
			++pTileInfo->ImgIdx;
		}

		//wchar_t szMousePos[255] = {};
		//swprintf_s(szMousePos, 255, L"MouseX : %d, MousY : %d", (int)vMousePos.x, (int)vMousePos.y);
		//LOG(LOG_LEVEL::WARNING, szMousePos);
	}
}

void CLevel_Editor::SaveTile()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();
	
	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*"; 
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		if (wcslen(szFilePath) != 0)
		{
			m_TileMap->Save(szFilePath);
		}		
	}

	CUIMgr::Get()->SetPreventFrame(1);
}

void CLevel_Editor::LoadTile()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetOpenFileName(&Desc))
	{
		if (wcslen(szFilePath) != 0)
		{
			m_TileMap->Load(szFilePath);
		}		
	}

	CUIMgr::Get()->SetPreventFrame(1);
}






// ===============================
// 타일관련 다이얼로그 프로시저 함수
// ===============================
LRESULT CALLBACK TileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int Col = GetDlgItemInt(hWnd, IDC_COL, nullptr, true);
			int Row = GetDlgItemInt(hWnd, IDC_ROW, nullptr, true);
						
			if (Col == 0 || Row == 0)
			{
				MessageBox(nullptr, L"타일의 행 or 열은 0 이 될 수 없습니다.", L"타일 행, 렬 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}

			// 1. 현재 레벨에 접근
			CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);

			// 에디터 레벨에서만 사용해야하는 다이얼로그 윈도우가 다른레벨에서 띄워진 경우
			assert(pEditorLevel);

			CTileMap* pTileMap = pEditorLevel->GetTileMap();
			pTileMap->SetRowCol(Col, Row);


			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}