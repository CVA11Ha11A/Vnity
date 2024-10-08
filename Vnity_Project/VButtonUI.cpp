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
		// ��� �Լ� ������ ���� �ν��Ͻ��� �������� .���� �Լ� �����͵� �������ؼ� ����Ѵ�.
		// ex) ((*m_pSceneInst).*m_pSceneFunc)(/*����*/);
		((*m_pSceneInst).*m_pSceneFunc)(/*����X*/);
	}

}

