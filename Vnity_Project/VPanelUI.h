#pragma once

#include "VUI.h"


class VPanelUI : public VUI
{

private:
	Vector2		m_vDragStart;	

public:	
	virtual void Update();
	virtual void Render(HDC _dc);

public:

	virtual void MouseOn();             // UI���� ���콺�� �ö�ð��ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();       // UI���� ���콺 ��Ŭ���� ȣ��� �Լ�
	virtual void MouseLbtnUp();         // UI���� ���콺 ��Ŭ���� ��� ȣ��� �Լ�
	virtual void MouseLbtnClicked();    // UI���� ���콺 Ŭ���� ���� �ɰ��(���ο��� Donw, UP�� �Ǿ����)


	CLONE(VPanelUI);

public:
	VPanelUI();
	virtual ~VPanelUI();

};

