#pragma once


class VResource;
class VTexture;
class VSound;

class VResourceManager
{
	SINGLETON(VResourceManager);

private:
	map<wstring, VResource*> m_mapTex;
	map<wstring, VSound*> m_mapSound;

public:
	VTexture* LoadTexture(const wstring& _strKey, const wstring _strRelativePath);
	VTexture* FindTexture(const wstring& _strKey);

	VTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);	


	VSound* LoadSound(const wstring& _strKey, const wstring _strRelativePath);
	VSound* FindSound(const wstring& _strKey);


};

