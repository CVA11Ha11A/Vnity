#include "pch.h"
#include "VKeyManager.h"
#include "VCore.h"

// 내가 정한 가상 key값과 VK key값 매핑
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
	// vector(List)속에 모든 키를 KeyInfo를 넣어놓음
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(KeyInfo{ E_KEY_STATE::NONE, false });
	}

}

void VKeyManager::Update()
{
	// 윈도우 포커싱 알아내기
	HWND hMainWnd = VCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();		// 현재 포커싱을 알아오기

	if (hMainWnd != hWnd)
	{	// 현재 프로그램이 포커싱 중이 아닐경우 STATE를 점점 NONE값으로 바꿈
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
		{	// if : 키가 눌려있다면.
			if (m_vecKey[i].isPrevEnter)
			{
				m_vecKey[i].eState = E_KEY_STATE::HOLD;
			}
			else
			{	// else : 이전에 눌려있지 않다
				m_vecKey[i].eState = E_KEY_STATE::ENTER;
			}

			m_vecKey[i].isPrevEnter = true;
		}
		else 
		{	// else : 키가 눌리지않았다.
			if (m_vecKey[i].isPrevEnter == true)
			{	// if : 이전에 눌려있던 경우
				m_vecKey[i].eState = E_KEY_STATE::UP;
			}
			else
			{	// else : 이전에도 눌리지 않은 상태라면
				m_vecKey[i].eState = E_KEY_STATE::NONE;
			}

			m_vecKey[i].isPrevEnter = false;
		}		
	}

	// Mouse 위치 계산
	POINT ptPos = {};
	GetCursorPos(&ptPos);		// 윈도우 제공 커서 위치가져옴 (현재 프로그램 내의 위치가아닌 모든 화면 기준)
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
