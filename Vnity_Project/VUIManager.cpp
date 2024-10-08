#include "pch.h"
#include "VUIManager.h"

#include "VSceneManager.h"
#include "VScene.h"
#include "VUI.h"

#include "VKeyManager.h"

VUIManager::VUIManager()
	:m_pFocusedUI(nullptr)
{

}

VUIManager::~VUIManager()
{

}

void VUIManager::Update()
{
	// 1. FocusedUI 확인 
	m_pFocusedUI = GetFocusedUI();

	if (m_pFocusedUI == nullptr)
	{
		return;
	}



	// 2. FocousedUI 내에서, 부모 UI포함, 자식 UI들 중 실제 타겟팅이된 UI를 가져온다.
	VUI* pTargetUI = GetTargetedUI(m_pFocusedUI);		// 타겟을 찾음

	bool bLbtnUp = KEY_UP(KEY::LBTN);
	bool bLbtnEnter = KEY_ENTER(KEY::LBTN);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();

		if (bLbtnEnter == true)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnUp == true)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown == true)
			{
				pTargetUI->MouseLbtnClicked();
			}

			// 왼쪽 버튼 떼면, 눌렸던 체크를 다시 해제한다.
			pTargetUI->m_bLbtnDown = false;
		}
	}



	VScene* pCurScene = VSceneManager::GetInst()->GetCurScene();
	const vector<VObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);



}		// Update()

void VUIManager::SetFocusedUI(VUI* _pUI)
{
	// 이미 포커싱 중인 or 포커싱 해제 요청인 경우
	if (m_pFocusedUI == _pUI || m_pFocusedUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;
	VScene* pCurScene = VSceneManager::GetInst()->GetCurScene();
	vector<VObject*>& vecUI = pCurScene->GetUIGroup();

	vector<VObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	if (iter != vecUI.end())
	{
		vecUI.erase(iter);
	}
	vecUI.push_back(m_pFocusedUI);

}		// SetFocusedUI()

VUI* VUIManager::GetFocusedUI()
{
	VScene* pCurScene = VSceneManager::GetInst()->GetCurScene();
	vector<VObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnEnter = KEY_ENTER(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인하다.
	VUI* pForcusedUI = m_pFocusedUI;

	if (!bLbtnEnter)
	{
		return pForcusedUI;
	}

	vector<VObject*>::iterator targetIter = vecUI.end();		// 타겟 이터레이터
	vector<VObject*>::iterator iter = vecUI.begin();			// 반복문 이터레이터

	// 좌클릭이 발생했다고 전재하에 검사진행
	for (; iter != vecUI.end() && *iter != nullptr; ++iter)
	{
		if (((VUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// 이번에 Forcus가 없다.
	if (targetIter == vecUI.end())
	{
		return nullptr;
	}

	pForcusedUI = (VUI*)*targetIter;

	// 백터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetIter);
	vecUI.push_back(pForcusedUI);


	return pForcusedUI;
}


VUI* VUIManager::GetTargetedUI(VUI* _pParentUI)
{
	bool bLbtnUp = KEY_UP(KEY::LBTN);

	// 1. 부모 UI 포함, 모든 자식들을 감지한다.
	VUI* pTargetUI = nullptr;
	static list<VUI*> queue;
	static vector<VUI*> vecNoneTargetUI;

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{	// while(Queue가 텅 비어있을때 까지 순회)

		// 큐에서 데이터 하나 꺼내기
		VUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI 인지 확인
		// 2. 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI(몇번을 거쳐서 가야 만나는지?)
		if (pUI->IsMouseOn())
		{
			if (pTargetUI != nullptr)
			{
				vecNoneTargetUI.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTargetUI.push_back(pUI);
		}

		// 해당 UI의 자식 UI 가져오기
		const vector<VUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}

	}

	for (size_t i = 0; i < vecNoneTargetUI.size(); ++i)
	{
		vecNoneTargetUI[i]->m_bLbtnDown = false;
	}



	return pTargetUI;
}		// GetTargetedUI()


