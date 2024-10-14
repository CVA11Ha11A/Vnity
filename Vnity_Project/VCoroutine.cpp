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



