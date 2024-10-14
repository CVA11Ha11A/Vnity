#include "pch.h"
#include "VCoroutineManager.h"

#include "VCoroutine.h"

VCoroutineManager::VCoroutineManager()	
	:isFSwitch(false)
	,isVSwitch(false)
	,m_tCache{}
{	
}
VCoroutineManager::~VCoroutineManager()
{
}

void VCoroutineManager::Init()
{
}


void VCoroutineManager::ClearGarbage()
{
	Safe_Delete_Vec<VCoroutine*>(m_vGarbageRoutines);
}

void VCoroutineManager::UpdateWaitForOneFrame()
{
	for (size_t i = 0; i < m_vWaitForOneFrame.size(); ++i)
	{
		// m_vWaitForOneFrame.
	}
}		// UpdateWaitForOneFrame()

void VCoroutineManager::UpdateWaitForSecond()
{	

	for (size_t i = 0; i < m_vWaitForSecond.size(); i++)
	{
		if (m_vWaitForSecond[i] != nullptr)
		{
			if (m_vWaitForSecond[i]->Execute() == true)
			{
				int deleteIndex = i--;
				m_vWaitForSecond.erase(m_vWaitForSecond.begin() + deleteIndex);
				
			}
		}
												
	}

}		// UpdateWaitForSecond()



void VCoroutineManager::AddCoroutine(VCoroutine* _routine)
{	
	switch (_routine->m_eType)
	{
	case CoroutineType::Default:
		assert(nullptr);
		break;
	case CoroutineType::WaitForSecond:
		m_vWaitForSecond.push_back(_routine);
		break;
	case CoroutineType::WaitForOneFrame:
		m_vWaitForOneFrame.push_back(_routine);
		break;
	}
	
}		// AddCoroutine()


