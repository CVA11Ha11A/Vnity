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
	// 1. FocusedUI Ȯ�� 
	m_pFocusedUI = GetFocusedUI();

	if (m_pFocusedUI == nullptr)
	{
		return;
	}



	// 2. FocousedUI ������, �θ� UI����, �ڽ� UI�� �� ���� Ÿ�����̵� UI�� �����´�.
	VUI* pTargetUI = GetTargetedUI(m_pFocusedUI);		// Ÿ���� ã��

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

			// ���� ��ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
			pTargetUI->m_bLbtnDown = false;
		}
	}



	VScene* pCurScene = VSceneManager::GetInst()->GetCurScene();
	const vector<VObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);



}		// Update()

void VUIManager::SetFocusedUI(VUI* _pUI)
{
	// �̹� ��Ŀ�� ���� or ��Ŀ�� ���� ��û�� ���
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

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���ϴ�.
	VUI* pForcusedUI = m_pFocusedUI;

	if (!bLbtnEnter)
	{
		return pForcusedUI;
	}

	vector<VObject*>::iterator targetIter = vecUI.end();		// Ÿ�� ���ͷ�����
	vector<VObject*>::iterator iter = vecUI.begin();			// �ݺ��� ���ͷ�����

	// ��Ŭ���� �߻��ߴٰ� �����Ͽ� �˻�����
	for (; iter != vecUI.end() && *iter != nullptr; ++iter)
	{
		if (((VUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// �̹��� Forcus�� ����.
	if (targetIter == vecUI.end())
	{
		return nullptr;
	}

	pForcusedUI = (VUI*)*targetIter;

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetIter);
	vecUI.push_back(pForcusedUI);


	return pForcusedUI;
}


VUI* VUIManager::GetTargetedUI(VUI* _pParentUI)
{
	bool bLbtnUp = KEY_UP(KEY::LBTN);

	// 1. �θ� UI ����, ��� �ڽĵ��� �����Ѵ�.
	VUI* pTargetUI = nullptr;
	static list<VUI*> queue;
	static vector<VUI*> vecNoneTargetUI;

	queue.clear();
	vecNoneTargetUI.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{	// while(Queue�� �� ��������� ���� ��ȸ)

		// ť���� ������ �ϳ� ������
		VUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI ���� Ȯ��
		// 2. Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI(����� ���ļ� ���� ��������?)
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

		// �ش� UI�� �ڽ� UI ��������
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


