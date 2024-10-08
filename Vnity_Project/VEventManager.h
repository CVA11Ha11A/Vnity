#pragma once

struct tEvent
{
	E_EVENT_TYPE		eEven;
	DWORD_PTR			lParam;		// �ּ� ���� �ü�� ��Ʈ���� ���� ũ�Ⱑ �ٸ��⿡ PTR�� ���
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
	void Execute(const tEvent& _event);	// �̺�Ʈ ó�� �Լ�


public:
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

};

