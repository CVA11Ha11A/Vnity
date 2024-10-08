#include "pch.h"
#include "VResourceManager.h"

#include "VPathManager.h"
#include "VTexture.h"
#include "VSound.h"


VResourceManager::VResourceManager()
{

}

VResourceManager::~VResourceManager()

{
	Safe_Delete_Map(m_mapTex);
	Safe_Delete_Map(m_mapSound);
}



/// <summary>
/// 텍스쳐 로딩 함수 ResourceManager
/// </summary>
/// <param name="_strKey">map의 Key값</param>
/// <param name="_strRelativePath">리소스의 상대적 경로</param>
/// <returns></returns>
VTexture* VResourceManager::LoadTexture(const wstring& _strKey, const wstring _strRelativePath)
{
	VTexture* pTex = FindTexture(_strKey);

	if (pTex != nullptr)
	{	// if : Map에 이미 로드된 텍스쳐가 존재한다면 해당 텍스쳐 리턴
		return pTex;
	}

	// 기본경로 Relese(.exe)\\Content;
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new VTexture;
	pTex->Load(strFilePath);

	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;

}

VTexture* VResourceManager::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	VTexture* pTex = FindTexture(_strKey);

	if (pTex != nullptr)
	{	// if : Map에 이미 로드된 텍스쳐가 존재한다면 해당 텍스쳐 리턴
		return pTex;
	}

	pTex = new VTexture;
	pTex->Create(_iWidth, _iHeight);
	pTex->SetKey(_strKey);
	
	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

VSound* VResourceManager::LoadSound(const wstring& _strKey, const wstring _strRelativePath)
{

	VSound* pSound = FindSound(_strKey);

	if (pSound != nullptr)
	{	// if : Map에 이미 로드된 텍스쳐가 존재한다면 해당 텍스쳐 리턴
		return pSound;
	}

	// 기본경로 Relese(.exe)\\Content;
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pSound = new VSound();
	pSound->Load(strFilePath);

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

VSound* VResourceManager::FindSound(const wstring& _strKey)
{
	map<wstring, VSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	return (VSound*)iter->second;
}



VTexture* VResourceManager::FindTexture(const wstring& _strKey)
{
	map<wstring, VResource*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (VTexture*)iter->second;
	
}
