#include "pch.h"
#include "VEventManager.h"
#include "VSceneManager.h"
#include "VUIManager.h"

#include "VObject.h"
#include "VScene.h"

#include "VAI.h"
#include "VState.h"

VEventManager::VEventManager()
	:m_vecEvent()
{

}
VEventManager::~VEventManager()
{
}


void VEventManager::Update()
{

	for (size_t i = 0; i < m_vecDeadObj.size(); ++i)
	{	// for : Deadó���� ������Ʈ ����
		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	// ==========
	// Event ó��
	// ==========
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void VEventManager::Execute(const tEvent& _event)
{	// lParam : Object Adress, // wParam : Group Type

	switch (_event.eEven)
	{
	case E_EVENT_TYPE::CREATE_OBJECT:
	{	// ������Ʈ�� ���� ������ �߰��϶�� �����Ѵ�.
		VObject* pNewObj = (VObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;
		VSceneManager::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case E_EVENT_TYPE::DELETE_OBJECT:
	{	// Object�� Dead ���·� ���� �� ���� ���� ������Ʈ�� ��Ƶд�.
		VObject* pDeadObj = (VObject*)_event.lParam;
		pDeadObj->SetDead();
		m_vecDeadObj.push_back(pDeadObj);
	}
	break;
	case E_EVENT_TYPE::SCENE_CHANGE:
	{	// lParam : Next Scene Type
		// Scene����
		VSceneManager::GetInst()->ChangeScene((E_SCENE_TYPE)_event.lParam);

		// ��Ŀ�� UI ���� (���� Scene�� ��Ŀ���� UI�� �����͸� ������ �ֱ� ����)
		VUIManager::GetInst()->SetFocusedUI(nullptr);
	}
	break;
	case E_EVENT_TYPE::CHANGE_AI_STATE:
	{	// lParam : AI Pointer
		// wParam : Next Type(State)
		VAI* pAI = (VAI*)_event.lParam;
		MON_STATE eNextState = (MON_STATE)_event.wParam;
		pAI->ChangeState(eNextState);
	}
	break;

	default:
		assert(nullptr);	// ���ǵ������� �̺�Ʈ�� ����
		break;
	}

}		// Execute()
