#include "VPanelUI.h"

#include "VKeyManager.h"

VPanelUI::VPanelUI()
	:VUI(false)
{

}

VPanelUI::~VPanelUI()
{
}





void VPanelUI::Update()
{

}

void VPanelUI::Render(HDC _dc)
{
	VUI::Render(_dc);
}

void VPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		Vector2 vDiff = MOUSE_POS - m_vDragStart;

		Vector2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void VPanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void VPanelUI::MouseLbtnUp()
{
}

void VPanelUI::MouseLbtnClicked()
{
}

