#pragma once

// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ������

// 2. Ű �Է� �̺�Ʈ ó��
// Enter, Stay, Up

enum class E_KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	ENTER,	// �� ���� ���� (Ȧ�� �ƴ�)
	HOLD,	// ������ �ִ� ����
	UP,		// �� �� ����
	
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
	E_KEY_STATE		eState;	// Ű�� ���°�
	bool			isPrevEnter;	// ���� �����ӿ� ���ȴ��� ����

};

class VKeyManager
{
	SINGLETON(VKeyManager);

private:
	vector<KeyInfo> m_vecKey;
	Vector2			m_vCurMousePos;	// ���� ���콺 ��ġ


public:
	void Init();
	void Update();

public:
	E_KEY_STATE GetKeyState(KEY _eKey);		// TODO : �̺κ��� 3���ҷγ���� �ѹ��� �����ϸ� ȣ��� ª�� ȣ�� �����غ��� (������ ����)
	Vector2 GetMousePos() { return m_vCurMousePos; }	// �� Update���� ���Ǵ���


};

