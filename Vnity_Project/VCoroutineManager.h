#pragma once

class VObject;
class VCoroutine;

struct tCouroutineDatas
{
	VObject* ownerCache;		// 코루틴 실행 요청 객체 캐시
	function<void()>		vFuncCache;
	function<void(float)>	fFuncCache;
	float fCacheParam;		// 임시 인자 저장변수
};

class VCoroutineManager
{
	SINGLETON(VCoroutineManager);

private:
	// 어떤것을 담아야할까 (코루틴의 호출 주기가 완료되었는지 체크할 객체)
	list<VCoroutine*> m_lWaitForSecond;	// 실행예정인 WaitForSecond
	list<VCoroutine*> m_lWaitForOneFrame;	// 실행예정인 WaitForOneFrame
	vector<VCoroutine*> m_vAddRouitnes;	// 코루틴실행 타이밍이 아닐경우 이벤트처럼 모아두었다가 한번에 재추가(즉시추가시 실행 반복문에서 중복 실행가능성 존재)
	vector<VCoroutine*>	m_vGarbageRoutines;	// 한번 사용된 대기 Class들을 모여두고 한번에 처리할 vector

	tCouroutineDatas m_tCache;	// 잠시 기억해둘 캐시 데이터

private:
	bool isFSwitch; // bool : 코루틴 오류 실드용 [만일 yield return을 하지 않는순간 코루틴의 캐시를 얻어갈때 생길 문제방지]
	bool isVSwitch;


public:	// Get
	list<VCoroutine*>& GetWaitForSecondVector() { return m_lWaitForSecond; }
	list<VCoroutine*>& GetWaitForOneFrameVector() { return m_lWaitForOneFrame; }
	
	tCouroutineDatas& GetCouroutineCache() { return m_tCache; }
	bool GetFSwitch() { return isFSwitch; }
	bool GetVSwitch() { return isVSwitch; }

public:	// Set
	void SetCouroutineCache(function<void()> _func, VObject* _pOwner)
	{
		m_tCache.vFuncCache = _func;
		m_tCache.ownerCache = _pOwner;
	}
	void SetCouroutineCache(function<void(float)> _func, float _fParam, VObject* _pOwner)
	{
		m_tCache.fFuncCache = _func;
		m_tCache.fCacheParam = _fParam;
		m_tCache.ownerCache = _pOwner;
	}
	void SetCouroutineCache(VCoroutine* _routine);
	void OnVSwitch()
	{
		if (isFSwitch == true)
		{
			isFSwitch = false;
		}
		isVSwitch = true;
	}
	void OnFSwitch() 
	{
		if (isVSwitch == true)
		{
			isVSwitch = false;
		}
		isFSwitch = true;
	}

public:
	void ClearCacheData()
	{
		m_tCache.fCacheParam = 0.f;
		m_tCache.vFuncCache = nullptr;
		m_tCache.fFuncCache = nullptr;
		m_tCache.ownerCache = nullptr;
	}
	void ClearGarbage();

	void AddGarbageRoutine(VCoroutine* _garbage) { m_vGarbageRoutines.push_back(_garbage); }

public: // Update
	void UpdateWaitForOneFrame();
	void UpdateWaitForSecond();

	void UpdateRoutineSetting();		// 

public:
	void Init();
	void AddCoroutine(VCoroutine* _routine);		// 코루틴(Class)이 생성될경우 호출될 함수
};

