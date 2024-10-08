#pragma once

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가진다

// 2. 키 입력 이벤트 처리
// Enter, Stay, Up

enum class E_KEY_STATE
{
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상태
	ENTER,	// 막 누른 시점 (홀드 아님)
	HOLD,	// 누르고 있는 시점
	UP,		// 막 땐 시점
	
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,Z,X,C,V,B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,



	LAST,
};

struct KeyInfo
{	
	E_KEY_STATE		eState;	// 키의 상태값
	bool			isPrevEnter;	// 이전 프레임에 눌렸는지 여부

};

class VKeyManager
{
	SINGLETON(VKeyManager);

private:
	vector<KeyInfo> m_vecKey;
	Vector2			m_vCurMousePos;	// 현재 마우스 위치


public:
	void Init();
	void Update();

public:
	E_KEY_STATE GetKeyState(KEY _eKey);		// TODO : 이부분을 3분할로나누어서 한번더 매핑하면 호출시 짧게 호출 가능해보임 (성능은 저하)
	Vector2 GetMousePos() { return m_vCurMousePos; }	// 매 Update에서 계산되는중


};

