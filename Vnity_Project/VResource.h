#pragma once
#include "VGlobal.h"

class VResource
{

private:
	wstring		m_strKey;				// 리소스만의 고유의 ID(문자열)
	wstring		m_strRelativePath;		// 리소스의 상대경로

public:
	void SetKey(const wstring& _stKey) {  m_strKey = _stKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	VResource();
	virtual ~VResource();
};

