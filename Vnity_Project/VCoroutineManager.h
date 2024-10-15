#pragma once

class VObject;
class VCoroutine;

struct tCouroutineDatas
{
	VObject* ownerCache;		// �ڷ�ƾ ���� ��û ��ü ĳ��
	function<void()>		vFuncCache;
	function<void(float)>	fFuncCache;
	float fCacheParam;		// �ӽ� ���� ���庯��
};

class VCoroutineManager
{
	SINGLETON(VCoroutineManager);

private:
	// ����� ��ƾ��ұ� (�ڷ�ƾ�� ȣ�� �ֱⰡ �Ϸ�Ǿ����� üũ�� ��ü)
	list<VCoroutine*> m_lWaitForSecond;	// ���࿹���� WaitForSecond
	list<VCoroutine*> m_lWaitForOneFrame;	// ���࿹���� WaitForOneFrame
	vector<VCoroutine*> m_vAddRouitnes;	// �ڷ�ƾ���� Ÿ�̹��� �ƴҰ�� �̺�Ʈó�� ��Ƶξ��ٰ� �ѹ��� ���߰�(����߰��� ���� �ݺ������� �ߺ� ���డ�ɼ� ����)
	vector<VCoroutine*>	m_vGarbageRoutines;	// �ѹ� ���� ��� Class���� �𿩵ΰ� �ѹ��� ó���� vector

	tCouroutineDatas m_tCache;	// ��� ����ص� ĳ�� ������

private:
	bool isFSwitch; // bool : �ڷ�ƾ ���� �ǵ�� [���� yield return�� ���� �ʴ¼��� �ڷ�ƾ�� ĳ�ø� ���� ���� ��������]
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
	void AddCoroutine(VCoroutine* _routine);		// �ڷ�ƾ(Class)�� �����ɰ�� ȣ��� �Լ�
};

