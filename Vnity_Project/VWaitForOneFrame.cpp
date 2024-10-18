#include "pch.h"
#include "VWaitForOneFrame.h"

#include "VCoroutineManager.h"



VWaitForOneFrame::VWaitForOneFrame()
{
	m_eType = CoroutineType::WaitForOneFrame;
	VCoroutineManager::GetInst()->AddCoroutine(this);		// 해당 함수에서 Manager에게 추가
}

VWaitForOneFrame::~VWaitForOneFrame()
{

}

bool VWaitForOneFrame::Execute()
{
	CallFunction();
	VCoroutineManager::GetInst()->AddGarbageRoutine(this);
	return true;
}