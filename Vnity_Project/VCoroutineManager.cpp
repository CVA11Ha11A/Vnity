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
		// 여기서 캐시 설정 한번 더 해줘야 할거 같은데?
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
{		// 씬 이동시 오브젝트들의 DonDestory여부에 따라서 코루틴또한 파괴되지않도록 설정하는 함수

	vector<VCoroutine*> vAliveRoutine;	// DonDestory오브젝트가 실행시킨 코루틴들을 모아둘 vector
	vector<VObject*> vDonDesObjs;		// DonDestroy인 오브젝트들

	// 1.이동전 씬에서 DonDestory인 오브젝트를 찾아서 임시 vector에 넣어두기
	for (int i = 0; i < (int)GROUP_TYPE::END; i++)
	{
		const vector<VObject*>& sceneObjs = VSceneManager::GetInst()->GetCurScene()->GetGroupObject((GROUP_TYPE)i);

		for (int j = 0; j < sceneObjs.size(); j++)
		{	// for : 각 그룹의 DonDestory오브젝트들을 모아두는 작업
			if (sceneObjs[j]->GetIsDonDestroy())
			{
				vDonDesObjs.push_back(sceneObjs[j]);
			}
		}
	}


	// 2.DonDestory인 오브젝트들의 목록을가지고 생존한 루틴을 추가함
	vector<VObject*>::iterator iter = vDonDesObjs.begin();	

	for (; iter != vDonDesObjs.end(); iter++)
	{
		if (*iter == nullptr) { assert(nullptr); }
		// DonDestory가 실행한 코루틴이 존재하는지 체크(없을경우 nullptr반환)
		VCoroutine* routine = VCoroutineManager::GetInst()->FindCoroutine(*iter);

		if (routine != nullptr)
		{
			vAliveRoutine.push_back(routine);
		}
	}

	// 3.현재씬에서 루틴으로 저장된 코루틴들을 모두 제거후 생존한 코루틴을 추가
	m_lWaitForOneFrame.clear();
	m_lWaitForSecond.clear();

	for (int i = 0; i < vAliveRoutine.size(); i++)
	{
		BranchCoroutine(vAliveRoutine[i]);
	}



}		// CoroutineReSetting()


