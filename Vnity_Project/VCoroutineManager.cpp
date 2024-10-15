#include "pch.h"
#include "VCoroutineManager.h"

#include "VCoroutine.h"

VCoroutineManager::VCoroutineManager()
	:isFSwitch(false)
	, isVSwitch(false)
	, m_tCache{}
{
}
VCoroutineManager::~VCoroutineManager()
{
}

void VCoroutineManager::Init()
{
}


void VCoroutineManager::SetCouroutineCache(VCoroutine* _routine)
{
	if (_routine->ffunc != nullptr)
	{
		m_tCache.fFuncCache = _routine->ffunc;
		m_tCache.fCacheParam = _routine->m_fParam;
		OnFSwitch();
	}
	else if (_routine->vfunc != nullptr)
	{
		m_tCache.vFuncCache = _routine->vfunc;
		OnVSwitch();
	}

	m_tCache.ownerCache = _routine->funcOwner;

}

void VCoroutineManager::ClearGarbage()
{
	if (100 < m_vGarbageRoutines.size())
	{
		Safe_Delete_Vec<VCoroutine*>(m_vGarbageRoutines);
	}
}

void VCoroutineManager::UpdateWaitForOneFrame()
{
	for (size_t i = 0; i < m_lWaitForOneFrame.size(); ++i)
	{
		// m_vWaitForOneFrame.
	}
}		// UpdateWaitForOneFrame()

void VCoroutineManager::UpdateWaitForSecond()
{
	VCoroutine* routine = nullptr;

	for (; 0 < m_lWaitForSecond.size(); )
	{
		// 여기서 캐시 설정 한번 더 해줘야 할거 같은데?
		routine = *(m_lWaitForSecond.begin());
		SetCouroutineCache(routine);
		m_lWaitForSecond.pop_front();
		if (routine->Execute() == false)
		{
			m_vAddRouitnes.push_back(routine);
		}
	}

}		// UpdateWaitForSecond()

void VCoroutineManager::UpdateRoutineSetting()
{
	for (size_t i = 0; i < m_vAddRouitnes.size(); i++)
	{
		AddCoroutine(m_vAddRouitnes[i]);
	}
	m_vAddRouitnes.clear();

	ClearGarbage();
}



void VCoroutineManager::AddCoroutine(VCoroutine* _routine)
{
	switch (_routine->m_eType)
	{
	case CoroutineType::Default:
		assert(nullptr);
		break;
	case CoroutineType::WaitForSecond:
		m_lWaitForSecond.push_back(_routine);
		break;
	case CoroutineType::WaitForOneFrame:
		m_lWaitForOneFrame.push_back(_routine);
		break;
	}

}		// AddCoroutine()


