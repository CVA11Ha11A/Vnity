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

};

