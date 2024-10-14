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
{	// ��ü�� �ʼ� ��� �ʱ�ȭ �ϴ� �Լ�
	tCouroutineDatas& cacheData = VCoroutineManager::GetInst()->GetCouroutineCache();
	bool fSwitch = VCoroutineManager::GetInst()->GetFSwitch();
	bool vSwitch = VCoroutineManager::GetInst()->GetVSwitch();

#pragma region LEGACY(ĳ�� ������ üũ)
	//if (cacheData.vFuncCache != nullptr)
	//{
	//	vfunc = cacheData.vFuncCache;
	//}
	//else if (cacheData.fFuncCache != nullptr)
	//{
	//	ffunc = cacheData.fFuncCache;
	//	m_fParam = cacheData.fCacheParam;
	//}
#pragma endregion LEGACY(ĳ�� ������ üũ)
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



