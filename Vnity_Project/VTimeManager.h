#pragma once


class VTimeManager
{
	SINGLETON(VTimeManager);
private:
	// FPS를 알면 1프레임당 걸리는 시간을 알 수 있음 // Delta Time = 1프레임에 걸리는 시간
	LARGE_INTEGER	m_CurCount;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_Frequency;

	float			m_DeltaTime;	// 프레임 간의 시간값
	float			m_dAcc;			// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// 초당 호출 횟수
	UINT			m_FPS;			// 초당 프레임


public:
	void Init();
	void Update();
	void Render();

public:
	 float GetDeltaTime() { return m_DeltaTime; }	 
	 //float GetDeltaTime() { return (float)m_DeltaTime; }

};

