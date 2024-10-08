#pragma once
#include "VUI.h"

class VScene;
class VObject;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);	// �Լ������͸� �ϳ��� Ÿ������ ����

// !�Լ������� : ����Լ��� ���� �� �ִ� ������(��ȯ�� void) � ��ü���� ������ ����ؾ���
// (�� ���� ��ü(�θ�)�� ��ӹ޴¾굵 ���� ĳ������ �ؾ���)
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
	virtual void MouseOn();             // UI���� ���콺�� �ö�ð��ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();       // UI���� ���콺 ��Ŭ���� ȣ��� �Լ�
	virtual void MouseLbtnUp();         // UI���� ���콺 ��Ŭ���� ��� ȣ��� �Լ�
	virtual void MouseLbtnClicked();    // UI���� ���콺 Ŭ���� ���� �ɰ��(���ο��� Donw, UP�� �Ǿ����)
	
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

