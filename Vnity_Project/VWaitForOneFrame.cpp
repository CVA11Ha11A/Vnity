#include "pch.h"
#include "VWaitForOneFrame.h"

#include "VCoroutineManager.h"



VWaitForOneFrame::VWaitForOneFrame()
{
	m_eType = CoroutineType::WaitForOneFrame;
	VCoroutineManager::GetInst()->AddCoroutine(this);		// �ش� �Լ����� Manager���� �߰�
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