#include "pch.h"
#include "VCoroutineManager.h"

#include "VCoroutine.h"

VCoroutineManager::VCoroutineManager()
	:ownerCache(nullptr)
	,vCFunc(nullptr)
	,fCFunc(nullptr)
	,m_fCacheParam(0.f)
{
	m_vWaitForSecond.resize(20);
	m_vWaitForOneFrame.resize(20);
}
VCoroutineManager::~VCoroutineManager()
{
}

void VCoroutineManager::Init()
{
}

void VCoroutineManager::ClearCache()
{
	ownerCache = nullptr;
	vCFunc = nullptr;
	fCFunc = nullptr;
	m_fCacheParam = 0.f;
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
	for (size_t i = 0; i < m_vWaitForSecond.size(); ++i)
	{
		m_vWaitForSecond[i]->Execute();
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


