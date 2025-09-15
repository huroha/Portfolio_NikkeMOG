#include "pch.h"
#include "CTileMap.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CCamera.h"

CTileMap::CTileMap()
	: CComponent(COMPONENT_TYPE::TILEMAP)
	, m_Row(1)
	, m_Col(1)
	, m_TileSize(Vec2(32.f, 32.f))
{
}

CTileMap::~CTileMap()
{
}

void CTileMap::FinalTick()
{
}

void CTileMap::Render()
{
	Vec2 vPos = GetOwner()->GetRenderPos();

	SELECT_PEN(BackDC, PEN_TYPE::MAGENTA);

	for (int iRow = 0; iRow < m_Row + 1; ++iRow)
	{
		MoveToEx(BackDC, (int)vPos.x, (int)vPos.y + iRow * (int)m_TileSize.y, nullptr);
		LineTo(BackDC, (int)vPos.x + m_Col * (int)m_TileSize.x, (int)vPos.y + iRow * (int)m_TileSize.y);		
	}
	
	for (int iCol = 0; iCol < m_Col + 1; ++iCol)
	{
		MoveToEx(BackDC, (int)vPos.x + iCol * (int)m_TileSize.x, (int)vPos.y, nullptr);
		LineTo(BackDC, (int)vPos.x + iCol * (int)m_TileSize.x, (int)vPos.y + m_Row * (int)m_TileSize.y);
	}

	if (nullptr != m_Atlas)
	{
		Render_Tile();
	}
}

void CTileMap::Render_Tile()
{
	// ȭ�� �ػ�
	Vec2 vResolution = CEngine::Get()->GetResolution();

	// Ÿ�� ������Ʈ ���� �»�� ��ġ
	Vec2 vRenderPos = GetOwner()->GetRenderPos();

	// ī�޶� �ٶ󺸴� ���� ��ǥ
	Vec2 vLookAt = CCamera::Get()->GetLookAt();
	Vec2 vCamLookLeftTop = vLookAt - (vResolution / 2.f);

	// ī�޶� �þ� �»�ܰ� Ÿ�Ͽ�����Ʈ ������ġ�� ���̰�
	Vec2 vOffset = vCamLookLeftTop - GetOwner()->GetPos();

	// ī�޶� �þ� �»���� Ÿ�� ������Ʈ�� ����, � �������� Ȯ��
	int LeftTopCol = vOffset.x / m_TileSize.x;
	int LeftTopRow = vOffset.y / m_TileSize.y;

	if (vOffset.x < 0.f)
		LeftTopCol = 0;
	if (vOffset.y < 0.f)
		LeftTopRow = 0;
	
	// ȭ��ȿ� ������ Ÿ���� ���� ����, ���� ������ ���
	int TileMaxCol = (vResolution.x / m_TileSize.x) + 1;
	int TileMaxRow = (vResolution.y / m_TileSize.y) + 1;
	
	int RightBotCol = LeftTopCol + TileMaxCol;
	int RightBotRow = LeftTopRow + TileMaxRow;

	if (m_Col <= RightBotCol)	
		RightBotCol = m_Col;

	if (m_Row <= RightBotRow)
		RightBotRow = m_Row;
	
	for (int iRow = LeftTopRow; iRow < RightBotRow; ++iRow)
	{
		for (int iCol = LeftTopCol; iCol < RightBotCol; ++iCol)
		{
			// ȭ��󿡼� Ÿ���� �������� �»�� ��ġ
			Vec2 Pos = vRenderPos + Vec2(iCol * m_TileSize.x, iRow * m_TileSize.y);

			// ������ �������� ȭ��ۿ� ����� Ÿ���̸�, ȭ�鿡 ������ �ʴ� Ÿ���̶�� ��
			// �̷� Ÿ�ϵ��� ȭ�鿡 �׸��� �ʴ´�.
			if (Pos.x < -m_TileSize.x || vResolution.x < Pos.x ||
				Pos.y < -m_TileSize.y || vResolution.y < Pos.y)
			{
				continue;
			}

			// ���Ϳ� ����ִ� Ÿ���� ������ �������� ���ؼ� ���� Ÿ���� ��ķ� 1���� �ε����� ����
			int idx = iRow * m_Col + iCol;			

			if (-1 == m_vecTileInfo[idx].ImgIdx)
				continue;

			// Ÿ�������� ����ִ� �̹��� �ε����� �̿��ؼ�, ��Ʋ���� ��������� �������� �»�� ��ǥ�� �����
			Vec2 vLeftTop = Vec2(m_AtlasTileSize.x * (m_vecTileInfo[idx].ImgIdx % m_AtlasMaxCol)
								, m_AtlasTileSize.y * (m_vecTileInfo[idx].ImgIdx / m_AtlasMaxCol));
			
			// Ÿ�� ��ġ��, ��Ʋ�󽺿��� ������ �̹����� �߶� �ٿ�����
			BitBlt(BackDC, (int)Pos.x, (int)Pos.y, (int)m_TileSize.x, (int)m_TileSize.y
				  , m_Atlas->GetDC(), (int)vLeftTop.x, (int)vLeftTop.y, SRCCOPY);
		}
	}

}

void CTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	m_Row = _Row; 
	m_Col = _Col;

	if (m_vecTileInfo.size() < m_Row * m_Col)
	{
		m_vecTileInfo.resize(m_Row * m_Col);
	}
	else if (m_Row * m_Col < m_vecTileInfo.size())
	{
		vector<tTileInfo> temp;
		temp.resize(m_Row * m_Col);
		m_vecTileInfo.swap(temp);
	}

	for (int i = 0; i < m_vecTileInfo.size(); ++i)
	{
		m_vecTileInfo[i].ImgIdx = 0;
		//int MaxTileImgCount = m_AtlasMaxCol * m_AtlasMaxRow;
		//m_vecTileInfo[i].ImgIdx = i % MaxTileImgCount;
	}
}



void CTileMap::SetAtlas(CTexture* _Atlas)
{
	m_Atlas = _Atlas;

	if (m_Atlas)
	{
		m_AtlasResolution = Vec2(m_Atlas->GetWidth(), m_Atlas->GetHeight());
	}
}

void CTileMap::SetAtlasTileSize(Vec2 _Size)
{
	m_AtlasTileSize = _Size;

	if (m_Atlas)
	{
		m_AtlasMaxCol = m_AtlasResolution.x / m_AtlasTileSize.x;
		m_AtlasMaxRow = m_AtlasResolution.y / m_AtlasTileSize.y;
	}
}

tTileInfo* CTileMap::GetTileInfo(UINT _Col, UINT _Row)
{
	if (m_Col <= _Col || m_Row <= _Row)
	{
		return nullptr;
	}

	return &m_vecTileInfo[_Row * m_Col + _Col];
}

void CTileMap::Save(const wstring& _strPath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _strPath.c_str(), L"wb");

	// Ÿ�� ��,�� ����
	fwrite(&m_Row, sizeof(UINT), 1, File);
	fwrite(&m_Col, sizeof(UINT), 1, File);

	// Ÿ�� 1���� ũ��
	fwrite(&m_TileSize, sizeof(Vec2), 1, File);
	
	// Ÿ���� �����ϴ� ��Ʋ�� �ؽ��� ����
	SaveAssetRef(m_Atlas, File);
	fwrite(&m_AtlasTileSize, sizeof(Vec2), 1, File);

	// �� Ÿ���� � �̹����� ����ߴ���
	fwrite(m_vecTileInfo.data(), sizeof(tTileInfo), m_Row * m_Col, File);

	fclose(File);
}

void CTileMap::Load(const wstring& _strPath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _strPath.c_str(), L"rb");

	// Ÿ�� ��,�� ����
	fread(&m_Row, sizeof(UINT), 1, File);
	fread(&m_Col, sizeof(UINT), 1, File);
	SetRowCol(m_Row, m_Col);


	// Ÿ�� 1���� ũ��
	fread(&m_TileSize, sizeof(Vec2), 1, File);

	// Ÿ���� �����ϴ� ��Ʋ�� �ؽ��� ����
	m_Atlas = LoadTextureRef(File);
	if (nullptr != m_Atlas)
		SetAtlas(m_Atlas);

	fread(&m_AtlasTileSize, sizeof(Vec2), 1, File);
	SetAtlasTileSize(m_AtlasTileSize);

	// �� Ÿ���� � �̹����� ����ߴ���
	fread(m_vecTileInfo.data(), sizeof(tTileInfo), m_Row * m_Col, File);

	fclose(File);
}