#pragma once
#include "VResource.h"

class VTexture : public VResource
{

private:
	HDC			m_dc;
	HBITMAP		m_hBit;
	BITMAP		m_bitInfo;	// ∫Ò∆Æ∏  ¡§∫∏


public:
	void Load(const wstring _strFilePath);
	void Create(UINT _iWidth, UINT _iHeight);

	UINT GetWidth() { return m_bitInfo.bmWidth; }
	UINT GetHeight() { return m_bitInfo.bmHeight; }

	HDC	 GetDC() { return m_dc; }


private:
	VTexture();
	virtual ~VTexture();

	friend class VResourceManager;
};

