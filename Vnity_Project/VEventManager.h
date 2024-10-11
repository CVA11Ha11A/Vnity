#pragma once

struct tEvent
{
	E_EVENT_TYPE		eEven;
	DWORD_PTR			lParam;		// 주소 값이 운영체제 비트수의 따라 크기가 다르기에 PTR로 사용
	DWORD_PTR			wParam;
};


class VEventManager
{
	SINGLETON(VEventManager);


private:
	vector<tEvent>	m_vecEvent;

	vector<VObject*> m_vecDeadObj;

public:

	void Update();

private:
	void Execute(const tEvent& _event);	// 이벤트 처리 함수


public:
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

	// 다음에 실행될 이벤트의 정보를 가져오는 함수(ex : 씬이동 바로 2번호출된다면 먼저실행될 이벤트를 넘겨줌)
	tEvent FindNextEvent(E_EVENT_TYPE _findEvent);		
};

