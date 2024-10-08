#include "pch.h"
#include "VTexture.h"
#include "VCore.h"
#include <iostream>

VTexture::VTexture()
	:m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

VTexture::~VTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}


void VTexture::Load(const wstring _strFilePath)
{
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP,
								0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// ! 테스트 결과 사진 문제 // ! LoadImage로는 기본적으로 bmp확장자만 가져옴
	// ! 기존 Png를 bmp로 온라인으로 변경했는데 그런 사진도 못불러옴 그림판으로 그린걸 bmp로 저장하니 되었음
	 			
	assert(m_hBit);

	// 비트맵과 연결할 DC
	m_dc = CreateCompatibleDC(VCore::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void VTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = VCore::GetInst()->GetMainDC();

	// 텍스쳐 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
	m_dc = CreateCompatibleDC(maindc);
	
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	// 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}		// Create()



