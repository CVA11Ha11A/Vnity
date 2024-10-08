#include "VButtonUI.h"

#include "VScene.h"
#include "VObject.h"

VButtonUI::VButtonUI()
	:VUI(false)
	,m_pFunc(nullptr)
	,m_pSceneFunc(nullptr)
	,m_pSceneInst(nullptr)
{
}

VButtonUI::~VButtonUI()
{
}


void VButtonUI::MouseOn()
{
}

void VButtonUI::MouseLbtnDown()
{
}

void VButtonUI::MouseLbtnUp()
{

}

void VButtonUI::MouseLbtnClicked()
{
	if (m_pFunc != nullptr)
	{
		m_pFunc(m_param1, m_param2);
	}
	if (m_pSceneFunc != nullptr && m_pSceneInst != nullptr)
	{
		// 멤버 함수 포인터 사용시 인스턴스를 역참조후 .으로 함수 포인터도 역참조해서 사용한다.
		// ex) ((*m_pSceneInst).*m_pSceneFunc)(/*인자*/);
		((*m_pSceneInst).*m_pSceneFunc)(/*인자X*/);
	}

}

