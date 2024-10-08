#include "pch.h"
#include "VTimeManager.h"
#include "VCore.h"
#include "stdio.h"


VTimeManager::VTimeManager()
	:m_CurCount{}, m_Frequency{}, m_PrevCount{}, m_DeltaTime(), m_iCallCount(0),
	m_dAcc(0), m_FPS(0)
{

}

VTimeManager::~VTimeManager()
{

}

void VTimeManager::Init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_PrevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_Frequency);				// Frequency : �����, ����

}

void VTimeManager::Update()
{
	QueryPerformanceCounter(&m_CurCount);

	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_DeltaTime = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;
	
	// ����ī��Ʈ ���� ���簪���� ����(������ ����� ���ؼ�)
	m_PrevCount = m_CurCount;

#ifdef _DEBUG
	if (m_DeltaTime > (1.f / 60.f))
	{
		m_DeltaTime = (1.f / 60.f);
	}
#endif
	
}

void VTimeManager::Render()
{
	++m_iCallCount;
	m_dAcc += m_DeltaTime;

	if (m_dAcc >= 1.f)
	{
		m_FPS = m_iCallCount;
		m_dAcc = 0;
		m_iCallCount = 0;

	}

	// ���� ���� ������ ���
	wchar_t sBuffer[255] = {};
	swprintf_s(sBuffer, L"FPS : %d, DeltaTime : %f", m_FPS, m_DeltaTime);
	SetWindowText(VCore::GetInst()->GetMainHwnd(), sBuffer);


}
