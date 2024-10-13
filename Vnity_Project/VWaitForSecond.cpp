#include "pch.h"
#include "VWaitForSecond.h"

#include "VTimeManager.h"
#include "VCoroutineManager.h"

VWaitForSecond::VWaitForSecond(float _duration)
	:m_fDurationTime(0.f)
	,VCoroutine(_duration)
{
	m_fWaitTime = _duration;
	m_eType = CoroutineType::WaitForSecond;
	VCoroutineManager::GetInst()->AddCoroutine(this);		// 해당 함수에서 Manager에게 추가
}


VWaitForSecond::~VWaitForSecond()
{

}


void VWaitForSecond::Execute()
{	
	m_fDurationTime += DeltaTime;

	if (m_fWaitTime <= m_fDurationTime)
	{
		CallFunction();
	}
}		// Execute()