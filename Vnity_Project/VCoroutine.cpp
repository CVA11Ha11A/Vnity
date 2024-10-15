#include "pch.h"
#include "VCoroutine.h"

#include "VCoroutineManager.h"


VCoroutine::VCoroutine()
	:m_fWaitTime(0.f)
	, m_fParam(0.f)
	, m_eType(CoroutineType::Default)
	, routineOwner(nullptr)
	, ffunc(nullptr)
	, vfunc(nullptr)
{
	Init();
}
VCoroutine::VCoroutine(float _waitTime)
	:m_fWaitTime(_waitTime)
	, m_fParam(0.f)
	, m_eType(CoroutineType::Default)
	, routineOwner(nullptr)
	, ffunc(nullptr)
	, vfunc(nullptr)
{
	Init();
}

VCoroutine::~VCoroutine()
{

}


void VCoroutine::Init()
{	// 객체의 필수 요소 초기화 하는 함수
	tCouroutineDatas& cacheData = VCoroutineManager::GetInst()->GetCouroutineCache();
	bool fSwitch = VCoroutineManager::GetInst()->GetFSwitch();
	bool vSwitch = VCoroutineManager::GetInst()->GetVSwitch();

#pragma region LEGACY(캐시 포인터 체크)
	//if (cacheData.vFuncCache != nullptr)
	//{
	//	vfunc = cacheData.vFuncCache;
	//}
	//else if (cacheData.fFuncCache != nullptr)
	//{
	//	ffunc = cacheData.fFuncCache;
	//	m_fParam = cacheData.fCacheParam;
	//}
#pragma endregion LEGACY(캐시 포인터 체크)
	if (vSwitch == true)
	{
		vfunc = cacheData.vFuncCache;
	}
	else if (fSwitch == true)
	{
		ffunc = cacheData.fFuncCache;
		m_fParam = cacheData.fCacheParam;
	}

	routineOwner = cacheData.ownerCache;

	VCoroutineManager::GetInst()->ClearCacheData();

}		// Init()


void VCoroutine::CallFunction()
{
	if (ffunc != nullptr)
	{
		ffunc(m_fParam);
	}
	else if (vfunc != nullptr)
	{
		vfunc();
	}

}		// CallFunction()



