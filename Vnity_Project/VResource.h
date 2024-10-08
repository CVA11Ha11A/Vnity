#pragma once
#include "VGlobal.h"

class VResource
{

private:
	wstring		m_strKey;				// ���ҽ����� ������ ID(���ڿ�)
	wstring		m_strRelativePath;		// ���ҽ��� �����

public:
	void SetKey(const wstring& _stKey) {  m_strKey = _stKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	VResource();
	virtual ~VResource();
};

