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

void VCoroutine::Execute() { /* ���� �����Լ� */ }

void VCoroutine::Init()
{	// ��ü�� �ʼ� ��� �ʱ�ȭ �ϴ� �Լ�

	if (VCoroutineManager::GetInst()->GetVoidFunction() != nullptr
		&& VCoroutineManager::GetInst()->GetFloatFunction() != nullptr)
	{	// ��𼱰� ������ �߻��� ��
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

	funcOwner = VCoroutineManager::GetInst()->GetOwnerCache();	// ���⼭ �����߸� ���� �߸��Ȱ�

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



