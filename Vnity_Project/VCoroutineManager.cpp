#include "pch.h"
#include "VCoroutineManager.h"

#include "VSceneManager.h"

#include "VObject.h"
#include "VScene.h"
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

	m_tCache.ownerCache = _routine->routineOwner;

}

void VCoroutineManager::ClearGarbage()
{
	if (100 < m_vGarbageRoutines.size())
	{
		Safe_Delete_Vec<VCoroutine*>(m_vGarbageRoutines);
	}
}		// ClearGarbage()

void VCoroutineManager::ClearRouitnes()
{

}		// ClearRouitnes()

void VCoroutineManager::UpdateWaitForOneFrame()
{
	VCoroutine* routine = nullptr;

	for (; 0 < m_lWaitForOneFrame.size(); )
	{
		// ���⼭ ĳ�� ���� �ѹ� �� ����� �Ұ� ������?
		routine = *(m_lWaitForOneFrame.begin());
		SetCouroutineCache(routine);
		m_lWaitForOneFrame.pop_front();
		routine->Execute();

	}
}		// UpdateWaitForOneFrame()

void VCoroutineManager::UpdateWaitForSecond()
{
	VCoroutine* routine = nullptr;

	for (; 0 < m_lWaitForSecond.size(); )
	{
		// ���⼭ ĳ�� ���� �ѹ� �� ����� �Ұ� ������?
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
		BranchCoroutine(m_vAddRouitnes[i]);
	}
	m_vAddRouitnes.clear();

	ClearGarbage();
}



void VCoroutineManager::BranchCoroutine(VCoroutine* _routine)
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

void VCoroutineManager::AddCoroutine(VCoroutine* _routine)
{
	m_vAddRouitnes.push_back(_routine);
}

VCoroutine* VCoroutineManager::FindCoroutine(const VObject* _owner)
{
	list<VCoroutine*>::iterator oneframeIter = m_lWaitForOneFrame.begin();
	VCoroutine* routine;
	for (; oneframeIter != m_lWaitForOneFrame.end(); oneframeIter++)
	{
		routine = *oneframeIter;
		if (routine->GetOwner() == _owner)
		{
			return routine;
		}
	}

	list<VCoroutine*>::iterator secondIter = m_lWaitForSecond.begin();
	for (; secondIter != m_lWaitForSecond.end(); secondIter++)
	{
		routine = *secondIter;
		if (routine->GetOwner() == _owner)
		{
			return routine;
		}
	}

	return nullptr;
}		// FindCoroutine()

void VCoroutineManager::CoroutineReSetting()
{		// �� �̵��� ������Ʈ���� DonDestory���ο� ���� �ڷ�ƾ���� �ı������ʵ��� �����ϴ� �Լ�

	vector<VCoroutine*> vAliveRoutine;	// DonDestory������Ʈ�� �����Ų �ڷ�ƾ���� ��Ƶ� vector
	vector<VObject*> vDonDesObjs;		// DonDestroy�� ������Ʈ��

	// 1.�̵��� ������ DonDestory�� ������Ʈ�� ã�Ƽ� �ӽ� vector�� �־�α�
	for (int i = 0; i < (int)GROUP_TYPE::END; i++)
	{
		const vector<VObject*>& sceneObjs = VSceneManager::GetInst()->GetCurScene()->GetGroupObject((GROUP_TYPE)i);

		for (int j = 0; j < sceneObjs.size(); j++)
		{	// for : �� �׷��� DonDestory������Ʈ���� ��Ƶδ� �۾�
			if (sceneObjs[j]->GetIsDonDestroy())
			{
				vDonDesObjs.push_back(sceneObjs[j]);
			}
		}
	}


	// 2.DonDestory�� ������Ʈ���� ����������� ������ ��ƾ�� �߰���
	vector<VObject*>::iterator iter = vDonDesObjs.begin();	

	for (; iter != vDonDesObjs.end(); iter++)
	{
		if (*iter == nullptr) { assert(nullptr); }
		// DonDestory�� ������ �ڷ�ƾ�� �����ϴ��� üũ(������� nullptr��ȯ)
		VCoroutine* routine = VCoroutineManager::GetInst()->FindCoroutine(*iter);

		if (routine != nullptr)
		{
			vAliveRoutine.push_back(routine);
		}
	}

	// 3.��������� ��ƾ���� ����� �ڷ�ƾ���� ��� ������ ������ �ڷ�ƾ�� �߰�
	m_lWaitForOneFrame.clear();
	m_lWaitForSecond.clear();

	for (int i = 0; i < vAliveRoutine.size(); i++)
	{
		BranchCoroutine(vAliveRoutine[i]);
	}



}		// CoroutineReSetting()


