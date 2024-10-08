#include "pch.h"
#include "VPathManager.h"

#include "VCore.h"


VPathManager::VPathManager()
	:m_szContentPath{}
	, m_szRelativePath{}
{

}
VPathManager::~VPathManager()
{
}


void VPathManager::Init()
{
	// ���α׷������ ��� �˾ƿ��� (.exe��ġ)
	GetCurrentDirectory(255, m_szContentPath);

	// ���������� // ����Path + bin\\content\\ 
	int iLen = (int)wcslen(m_szContentPath);
	for (int i = iLen; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\Content\\");

	SetWindowText(VCore::GetInst()->GetMainHwnd(), m_szContentPath);

}

wstring VPathManager::GetRelativePath(const wchar_t* _filePath)
{
	_filePath;

	wstring strFilePath = _filePath;
	
	
	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);


	return strRelativePath;
}
