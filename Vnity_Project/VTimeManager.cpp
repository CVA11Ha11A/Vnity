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
	// 현재 카운트
	QueryPerformanceCounter(&m_PrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_Frequency);				// Frequency : 빈번도, 정도

}

void VTimeManager::Update()
{
	QueryPerformanceCounter(&m_CurCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_DeltaTime = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;
	
	// 이전카운트 값을 현재값으로 갱신(다음번 계산을 위해서)
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

	// 매초 제목에 프레임 출력
	wchar_t sBuffer[255] = {};
	swprintf_s(sBuffer, L"FPS : %d, DeltaTime : %f", m_FPS, m_DeltaTime);
	SetWindowText(VCore::GetInst()->GetMainHwnd(), sBuffer);


}
