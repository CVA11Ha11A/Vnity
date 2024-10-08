#pragma once

// Singleton ��ũ��
#define SINGLETON(type) public: static type* GetInst() \
{\
	 static type mgr;\
	 return &mgr; \
}\
private:\
type();\
~type();
// Singleton ��ũ��

#define DeltaTime VTimeManager::GetInst()->GetDeltaTime()	// ��ŸŸ�� �������� ��ũ��
#define DT DeltaTime

#define CLONE(type) type* Clone() { return new type(*this); }

#define KEY_CHECK(E_Key,State) VKeyManager::GetInst()->GetKeyState(E_Key) == State
#define KEY_ENTER(E_Key) KEY_CHECK(E_Key,E_KEY_STATE::ENTER)
#define KEY_HOLD(E_Key) KEY_CHECK(E_Key,E_KEY_STATE::HOLD)
#define KEY_UP(E_Key) KEY_CHECK(E_Key,E_KEY_STATE::UP)
#define KEY_NONE(E_Key) KEY_CHECK(E_Key,E_KEY_STATE::NONE)
#define MOUSE_POS VKeyManager::GetInst()->GetMousePos()

#define WINDOW_X_SIZE 1600
#define WINDOW_Y_SIZE 900


#define PI 3.1415926535f


#define TILE_SIZE 64		// Ÿ���� ������ (�̹����� ���� ��������)

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	GROUND,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,







	UI = 31,		// ���� ���� �׸��� ���� UI�� �Ʒ����ٰ� �д�.
	END = 32,
};

enum class E_SCENE_TYPE
{
	TOOL,

	START,

	STAGE_01,
	STAGE_02,



	END,
};

enum class BRUSH_TYPE
{

	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,	
	END,
};

enum class E_EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,

	END,
};


enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATTACK,
	RUN,
	DEAD,
	END,
};