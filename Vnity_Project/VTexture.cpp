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
	// ���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP,
								0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// ! �׽�Ʈ ��� ���� ���� // ! LoadImage�δ� �⺻������ bmpȮ���ڸ� ������
	// ! ���� Png�� bmp�� �¶������� �����ߴµ� �׷� ������ ���ҷ��� �׸������� �׸��� bmp�� �����ϴ� �Ǿ���
	 			
	assert(m_hBit);

	// ��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(VCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void VTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = VCore::GetInst()->GetMainDC();

	// �ؽ��� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
	m_dc = CreateCompatibleDC(maindc);
	
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}		// Create()



