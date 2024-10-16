#pragma once

enum class CoroutineType
{
	Default,
	WaitForSecond,
	WaitForOneFrame,

};

class VObject;

class VCoroutine
{	// ! 부모객체 상속받을 객체들은 Waitforsecond, WaitforOneframe(null) 같은객체가 상속할 예정


public:	

	
protected:
	CoroutineType m_eType;			// 어떤 타입인지에 따라서 Manager에 들어갈 공간이 달라짐
	VObject* routineOwner;			// 코루틴을 실행시킨 객체(멤버함수 포인터 주인)
	float m_fWaitTime;				// waitforsecond의 대기할 시간
	float m_fParam;					// float인자를 받는 함수를 위해 저장해둘곳

	
private:		
	//void (VObject::*vfunc)(void);				// 인자를 받지않는 함수 포인터
	//void (VObject::*ffunc)(float);			// int인자를 받는 함수 포인터

	function<void(void)> vfunc;
	function<void(float)> ffunc;

public:
	virtual bool Execute() = 0;		// 여기서 각각 자식 객체에서 자신이 불려도 되는지 계산할것임

	const VObject* GetOwner() { return routineOwner; }

protected:
	void CallFunction();			// 저장하고 있던 함수 포인터로 실행하는 함수
	
private:
	void Init();



public:
	VCoroutine();
	VCoroutine(float _waitTime);		// WaitForSecond를 위한 대기시간
	~VCoroutine();

private:
	VCoroutine(VCoroutine* _origin);		// 복사생성자 불가능하도록


	friend class VCoroutineManager;
};

