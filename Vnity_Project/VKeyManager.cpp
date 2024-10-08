#include "pch.h"
#include "VKeyManager.h"
#include "VCore.h"

// ���� ���� ���� key���� VK key�� ����
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU,	// ALT
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN, // ENTER
	VK_ESCAPE, // ESC

	VK_LBUTTON,
	VK_RBUTTON,

};



void VKeyManager::Init()
{
	// vector(List)�ӿ� ��� Ű�� KeyInfo�� �־����
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(KeyInfo{ E_KEY_STATE::NONE, false });
	}

}

void VKeyManager::Update()
{
	// ������ ��Ŀ�� �˾Ƴ���
	HWND hMainWnd = VCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();		// ���� ��Ŀ���� �˾ƿ���

	if (hMainWnd != hWnd)
	{	// ���� ���α׷��� ��Ŀ�� ���� �ƴҰ�� STATE�� ���� NONE������ �ٲ�
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].isPrevEnter = false;

			if (m_vecKey[i].eState == E_KEY_STATE::ENTER || m_vecKey[i].eState == E_KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = E_KEY_STATE::UP;
			}
			else
			{
				m_vecKey[i].eState = E_KEY_STATE::NONE;
			}
		}
		return;
	}

	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{	// if : Ű�� �����ִٸ�.
			if (m_vecKey[i].isPrevEnter)
			{
				m_vecKey[i].eState = E_KEY_STATE::HOLD;
			}
			else
			{	// else : ������ �������� �ʴ�
				m_vecKey[i].eState = E_KEY_STATE::ENTER;
			}

			m_vecKey[i].isPrevEnter = true;
		}
		else 
		{	// else : Ű�� �������ʾҴ�.
			if (m_vecKey[i].isPrevEnter == true)
			{	// if : ������ �����ִ� ���
				m_vecKey[i].eState = E_KEY_STATE::UP;
			}
			else
			{	// else : �������� ������ ���� ���¶��
				m_vecKey[i].eState = E_KEY_STATE::NONE;
			}

			m_vecKey[i].isPrevEnter = false;
		}		
	}

	// Mouse ��ġ ���
	POINT ptPos = {};
	GetCursorPos(&ptPos);		// ������ ���� Ŀ�� ��ġ������ (���� ���α׷� ���� ��ġ���ƴ� ��� ȭ�� ����)
	ScreenToClient(VCore::GetInst()->GetMainHwnd(), &ptPos);
	m_vCurMousePos = Vector2(ptPos);


}		// Update()

E_KEY_STATE VKeyManager::GetKeyState(KEY _eKey)
{
	return m_vecKey[(int)_eKey].eState;
}

VKeyManager::VKeyManager()
{

}
VKeyManager::~VKeyManager()
{

}
