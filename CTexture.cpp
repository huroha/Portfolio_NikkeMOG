#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"
#include "CEngine.h"

CTexture::CTexture()
	: m_hBitmap(nullptr)
	, m_hDC(nullptr)
	, m_BitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBitmap);
}

int CTexture::Load(const wstring& _FilePath)
{
	wchar_t szExt[50] = {};
	_wsplitpath_s(_FilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);

	if ( !wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		// ������ ��ηκ��� ��Ʈ�� �̹����� �޸𸮿� �ε��ϰ� �ڵ鰪�� �޾Ƶ�
		m_hBitmap = (HBITMAP)LoadImage(nullptr, _FilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// �ε��� ���������� �Ǿ����� ��Ʈ�� �ڵ鰪�� Ȯ��
		if (nullptr == m_hBitmap)
		{
			DWORD err = GetLastError();
			wchar_t buffer[256] = {};
			swprintf_s(buffer, 256, L"�ؽ��� �ε� ����\n���� ��ȣ : %d", err);
			MessageBox(nullptr, buffer, L"���� �߻�", MB_OK);

			return E_FAIL;
		}		
	}

	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplustoken = 0;
		GdiplusStartupInput input = {};
		GdiplusStartup(&gdiplustoken, &input, nullptr);		

		Image* pImage = Image::FromFile(_FilePath.c_str());
		Bitmap* pBitmap = (Bitmap*)pImage->Clone();
		delete pImage;

		pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBitmap);
	}

	// ��Ʈ���� �����ؼ� �������� DC �� ����
	m_hDC = CreateCompatibleDC(CEngine::Get()->GetMainDC());

	// ��Ʈ�ʰ� ������ DC �� ����
	DeleteObject(SelectObject(m_hDC, m_hBitmap));

	// �޸𸮿� �ε��� ��Ʈ���� ������ �޾ƿ´�.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitInfo);

	return S_OK;
}

int CTexture::Create(UINT _Width, UINT _Height)
{
	HDC DC = CEngine::Get()->GetMainDC();

	// BackBuffer ����
	m_hBitmap = CreateCompatibleBitmap(DC, _Width, _Height);

	// BackBuffer �� DC ����
	m_hDC = CreateCompatibleDC(DC);

	// BackBufferDC �� BackBuffer ��Ʈ���� ������ Ÿ������ �����ϰ�, 
	// DC �� ���� ����ִ� 1�ȼ�¥�� ��Ʈ���� ����Ѵ�.
	DeleteObject(SelectObject(m_hDC, m_hBitmap));

	// �޸𸮿� �ε��� ��Ʈ���� ������ �޾ƿ´�.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitInfo);

	return S_OK;
}
