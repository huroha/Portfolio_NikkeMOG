#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	Release_Map(m_mapTex);
	Release_Map(m_mapSound);
}

void CAssetMgr::Init()
{
}

CTexture* CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _RelativePath)
{
	// ������ Ű������ �̹� �ؽ��İ� �ִ��� Ȯ��
	CTexture* pTexture = FindTexture(_strKey);

	// �̹� ������ �װ� ��ȯ
	if (pTexture)
		return pTexture;

	// ��������, �Է����� ���� ����ο� Content ���������� ��θ� ���ļ� ������ ���� ��θ� ����
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _RelativePath;

	// �ؽ��� ��ü�ϳ� ����, �ϼ��� ��η� ��Ʈ�� �ε� ����
	pTexture = new CTexture;
	if (FAILED(pTexture->Load(strFilePath)))
	{
		delete pTexture;
		return nullptr;
	}
	
	// �ε��� �ؽ��ĸ� AssetMgr �� ���
	m_mapTex.insert(make_pair(_strKey, pTexture));

	// �ε��� �ؽ��İ� �ڽ��� Key, RelativePath �� �˰� �Ѵ�.
	pTexture->m_Key = _strKey;
	pTexture->m_RelativePath = _RelativePath;

	// �ε��� �ؽ��ĸ� ��ȯ
	return pTexture;
}

CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	// ������ Ű������ �ؽ��İ� �ִ��� Ȯ��
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	// �ؽ��İ� �̹� �־����� �װ� ��ȯ
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}

CTexture* CAssetMgr::CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height)
{
	// ������ Ű������ �̹� �ؽ��İ� �ִ��� Ȯ��
	CTexture* pTexture = FindTexture(_strKey);
	assert(!pTexture);

	pTexture = new CTexture;
	pTexture->Create(_Width, _Height);

	m_mapTex.insert(make_pair(_strKey, pTexture));
	pTexture->m_Key = _strKey;

	return pTexture;
}

CSound* CAssetMgr::LoadSound(const wstring& _strKey, const wstring& _RelativePath)
{
	// ������ Ű������ �̹� ���尡 �ִ��� Ȯ��
	CSound* pSound = FindSound(_strKey);

	// �̹� ������ �װ� ��ȯ
	if (pSound)
		return pSound;

	// ��������, �Է����� ���� ����ο� Content ���������� ��θ� ���ļ� ������ ���� ��θ� ����
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _RelativePath;

	// ���� ��ü�ϳ� ����, �ϼ��� ��η� ���� �ε� ����
	pSound = new CSound;
	if (FAILED(pSound->Load(strFilePath)))
	{
		delete pSound;
		return nullptr;
	}

	// �ε��� ���带 AssetMgr �� ���
	m_mapSound.insert(make_pair(_strKey, pSound));

	// �ε��� ���尡 �ڽ��� Key, RelativePath �� �˰� �Ѵ�.
	pSound->m_Key = _strKey;
	pSound->m_RelativePath = _RelativePath;

	// �ε��� ���带 ��ȯ
	return pSound;
}

CSound* CAssetMgr::FindSound(const wstring& _strKey)
{
	// ������ Ű������ ���尡 �ִ��� Ȯ��
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);
	
	// Ű���� �ش��ϴ� ���尡 ������ nullptr ��ȯ
	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	// ã������, ã�� ���� ��ȯ
	return iter->second;
}
