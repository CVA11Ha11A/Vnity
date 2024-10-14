#pragma once

class VObject;
class VCoroutine;



class VCoroutineManager
{
	SINGLETON(VCoroutineManager);
	
private:
	// 어떤것을 담아야할까 (코루틴의 호출 주기가 완료되었는지 체크할 객체)	
	vector<VCoroutine*> m_vWaitForSecond;	// 실행예정인 WaitForSecond
	vector<VCoroutine*> m_vWaitForOneFrame;	// 실행예정인 WaitForOneFrame


private:	// CoroutineData 캐시
	// 코루틴 임시 주석
	//VObject* ownerCache;		// 코루틴 실행 요청 객체 캐시	
	//void (VObject::*vCFunc)(void);		// void Cache Function
	//void (VObject::*fCFunc)(float);		// float Cache Function
	//float m_fCacheParam;		// 임시 인자 저장변수

public:	// Get
	vector<VCoroutine*>& GetWaitForSecondVector()	{ return m_vWaitForSecond; }
	vector<VCoroutine*>& GetWaitForOneFrameVector() { return m_vWaitForOneFrame; }	

	
public:	// Set



public: // Update
	void UpdateWaitForOneFrame();
	void UpdateWaitForSecond();

public:
	void Init();
	void AddCoroutine(VCoroutine* _routine);		// 코루틴(Class)이 생성될경우 호출될 함수
};

