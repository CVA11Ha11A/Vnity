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
	vector<VCoroutine*> m_vWaitForSecond;	// ���࿹���� WaitForSecond
	vector<VCoroutine*> m_vWaitForOneFrame;	// ���࿹���� WaitForOneFrame
	vector<VCoroutine*>	m_vGarbageRoutines;	// �ѹ� ���� ��� Class���� �𿩵ΰ� �ѹ��� ó���� vector

	tCouroutineDatas m_tCache;	// ��� ����ص� ĳ�� ������

private:
	bool isFSwitch; // bool : �ڷ�ƾ ���� �ǵ�� [���� yield return�� ���� �ʴ¼��� �ڷ�ƾ�� ĳ�ø� ���� ���� ��������]
	bool isVSwitch;


public:	// Get
	vector<VCoroutine*>& GetWaitForSecondVector() { return m_vWaitForSecond; }
	vector<VCoroutine*>& GetWaitForOneFrameVector() { return m_vWaitForOneFrame; }
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

public:
	void Init();
	void AddCoroutine(VCoroutine* _routine);		// �ڷ�ƾ(Class)�� �����ɰ�� ȣ��� �Լ�
};

