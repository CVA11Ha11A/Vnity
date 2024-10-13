#include "pch.h"
#include "VCoroutine.h"

#include "VCoroutineManager.h"


VCoroutine::VCoroutine()
	:m_fWaitTime(0.f)
	,m_fParam(0.f)
	,m_eType(CoroutineType::Default)
	,ffunc(nullptr)
	,vfunc(nullptr)
{	
	Init();
}
VCoroutine::VCoroutine(float _param)
	:m_fWaitTime(_param)
	,m_fParam(0.f)
	,m_eType(CoroutineType::Default)
	, ffunc(nullptr)
	, vfunc(nullptr)
{
	Init();
}

VCoroutine::~VCoroutine()
{
	
}

void VCoroutine::Execute() { /* 순수 가상함수 */ }

void VCoroutine::Init()
{	// 객체의 필수 요소 초기화 하는 함수

	if (VCoroutineManager::GetInst()->GetVoidFunction() != nullptr
		&& VCoroutineManager::GetInst()->GetFloatFunction() != nullptr)
	{	// 어디선가 문제가 발생한 것
		assert(nullptr);
	}
	else if (VCoroutineManager::GetInst()->GetVoidFunction() != nullptr)
	{
		vfunc = VCoroutineManager::GetInst()->GetVoidFunction();
	}
	else if (VCoroutineManager::GetInst()->GetFloatFunction() != nullptr)
	{
		ffunc = VCoroutineManager::GetInst()->GetFloatFunction();
		m_fParam = VCoroutineManager::GetInst()->GetCacheParam();
	}

	funcOwner = VCoroutineManager::GetInst()->GetOwnerCache();	// 여기서 오류뜨면 무언가 잘못된거

	VCoroutineManager::GetInst()->ClearCache();
}		// Init()


void VCoroutine::CallFunction()
{
	if (ffunc != nullptr)
	{
		
		(funcOwner->*ffunc)(m_fParam);
	}
	else if (vfunc != nullptr)
	{
		(funcOwner->*vfunc)();
	}

}		// CallFunction()



