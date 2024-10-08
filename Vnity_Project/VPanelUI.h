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

	virtual void MouseOn();             // UI위에 마우스가 올라올경우호출되는 함수
	virtual void MouseLbtnDown();       // UI에서 마우스 좌클릭시 호출될 함수
	virtual void MouseLbtnUp();         // UI에서 마우스 좌클릭땔 경우 호출될 함수
	virtual void MouseLbtnClicked();    // UI에서 마우스 클릭이 감지 될경우(내부에서 Donw, UP이 되어야함)


	CLONE(VPanelUI);

public:
	VPanelUI();
	virtual ~VPanelUI();

};

