#pragma once
#include "VUI.h"

class VScene;
class VObject;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);	// 함수포인터를 하나의 타임으로 정의

// !함수포인터 : 멤버함수를 받을 수 있는 포인터(반환형 void) 어떤 개체에서 받을지 명시해야함
// (단 상위 개체(부모)를 상속받는얘도 가능 캐스팅은 해야함)
typedef void(VScene::*SCENE_MEMFUNC)(void);
typedef void(VObject::*OBJECT_MEMFUNC)(void);

class VButtonUI :  public VUI
{
private:
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;


	SCENE_MEMFUNC	m_pSceneFunc;
	VScene*			m_pSceneInst;


public:
	virtual void MouseOn();             // UI위에 마우스가 올라올경우호출되는 함수
	virtual void MouseLbtnDown();       // UI에서 마우스 좌클릭시 호출될 함수
	virtual void MouseLbtnUp();         // UI에서 마우스 좌클릭땔 경우 호출될 함수
	virtual void MouseLbtnClicked();    // UI에서 마우스 클릭이 감지 될경우(내부에서 Donw, UP이 되어야함)
	
	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}

	void SetClickedCallBack(VScene* _pScene, SCENE_MEMFUNC _pSceneFunc)	
	{
		m_pSceneInst = _pScene;
		m_pSceneFunc = _pSceneFunc;
	}

	CLONE(VButtonUI);


public:
	VButtonUI();
	virtual ~VButtonUI();
};

