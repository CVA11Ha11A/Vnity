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
	{	// for : Dead처리된 오브젝트 제거
		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	// ==========
	// Event 처리
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
	{	// 오브젝트를 현재 씬에게 추가하라고 전달한다.
		VObject* pNewObj = (VObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;
		VSceneManager::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case E_EVENT_TYPE::DELETE_OBJECT:
	{	// Object를 Dead 상태로 변경 후 삭제 예정 오브젝트를 모아둔다.
		VObject* pDeadObj = (VObject*)_event.lParam;
		pDeadObj->SetDead();
		m_vecDeadObj.push_back(pDeadObj);
	}
	break;
	case E_EVENT_TYPE::SCENE_CHANGE:
	{	// lParam : Next Scene Type
		// Scene변경
		VSceneManager::GetInst()->ChangeScene((E_SCENE_TYPE)_event.lParam);

		// 포커스 UI 해제 (이전 Scene의 포커스된 UI의 포인터를 가지고 있기 때문)
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
		assert(nullptr);	// 정의되지않은 이벤트가 들어옴
		break;
	}

}		// Execute()
