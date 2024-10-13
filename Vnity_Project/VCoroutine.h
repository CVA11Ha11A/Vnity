#pragma once

enum class CoroutineType
{
	Default,
	WaitForSecond,
	WaitForOneFrame,

};

class VObject;

class VCoroutine
{	// ! �θ�ü ��ӹ��� ��ü���� Waitforsecond, WaitforOneframe(null) ������ü�� ����� ����


public:	

	
protected:
	CoroutineType m_eType;			// � Ÿ�������� ���� Manager�� �� ������ �޶���
	float m_fWaitTime;				// waitforsecond�� ����� �ð�
	float m_fParam;					// float���ڸ� �޴� �Լ��� ���� �����صѰ�

	
private:	
	VObject* funcOwner;		// �ڷ�ƾ�� �����û�� ��ü(��ü ���Ž� StopCoroutine��û�� �����ٰ���)
	void (VObject::*vfunc)(void);			// ���ڸ� �����ʴ� �Լ� ������
	void (VObject::*ffunc)(float);			// int���ڸ� �޴� �Լ� ������
	

public:
	virtual void Execute() = 0;		// ���⼭ ���� �ڽ� ��ü���� �ڽ��� �ҷ��� �Ǵ��� ����Ұ���


protected:
	void CallFunction();			// �����ϰ� �ִ� �Լ� �����ͷ� �����ϴ� �Լ�
	
private:
	void Init();



public:
	VCoroutine();
	VCoroutine(float _param);
	~VCoroutine();

	friend class VCoroutineManager;
};

