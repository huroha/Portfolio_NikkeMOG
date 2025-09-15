#pragma once

// ��� Ŭ�������� �ֻ��� �θ�Ŭ����
// �߻�Ŭ����

class CBase
{
private:
	static UINT g_ID;

private:
	wstring		m_Name; // wchar_t Ÿ�� ���� �迭
	const UINT	m_ID;	// Base ��ü���� ������ ���� ����

public:
	// Ŭ���� ����� ������ �Լ� ==> �ζ��� �Լ�
	// �Լ��� ȣ��Ǵ��� ���� ȣ���� ���� �ڵ尡 ����Ǿ ������
	// �Լ� �ڵ尡 ª�� ���, ���� ȣ��Ǵ� ���
	void SetName(const wstring& _Name)  { m_Name = _Name;  }
	const wstring& GetName()  { return m_Name;  }
	UINT GetID() { return m_ID; }

public:
	virtual CBase* Clone() = 0;

public:
	CBase();
	CBase(const CBase& _Other);
	virtual ~CBase();
};

