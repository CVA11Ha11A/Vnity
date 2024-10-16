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
	VObject* routineOwner;			// �ڷ�ƾ�� �����Ų ��ü(����Լ� ������ ����)
	float m_fWaitTime;				// waitforsecond�� ����� �ð�
	float m_fParam;					// float���ڸ� �޴� �Լ��� ���� �����صѰ�

	
private:		
	//void (VObject::*vfunc)(void);				// ���ڸ� �����ʴ� �Լ� ������
	//void (VObject::*ffunc)(float);			// int���ڸ� �޴� �Լ� ������

	function<void(void)> vfunc;
	function<void(float)> ffunc;

public:
	virtual bool Execute() = 0;		// ���⼭ ���� �ڽ� ��ü���� �ڽ��� �ҷ��� �Ǵ��� ����Ұ���

	const VObject* GetOwner() { return routineOwner; }

protected:
	void CallFunction();			// �����ϰ� �ִ� �Լ� �����ͷ� �����ϴ� �Լ�
	
private:
	void Init();



public:
	VCoroutine();
	VCoroutine(float _waitTime);		// WaitForSecond�� ���� ���ð�
	~VCoroutine();

private:
	VCoroutine(VCoroutine* _origin);		// ��������� �Ұ����ϵ���


	friend class VCoroutineManager;
};

