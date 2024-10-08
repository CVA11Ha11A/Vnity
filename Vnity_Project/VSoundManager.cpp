#include "pch.h"
#include "VSoundManager.h"
#include "VResourceManager.h"
#include "VSound.h"

#include "VCore.h"

VSoundManager::VSoundManager()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

VSoundManager::~VSoundManager()
{
}

int VSoundManager::Init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� ����̽� �������� ����.
	HWND hWnd = VCore::GetInst()->GetMainHwnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void VSoundManager::RegisterToBGM(VSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}