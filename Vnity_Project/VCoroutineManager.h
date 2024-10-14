#pragma once

class VObject;
class VCoroutine;


class VCoroutineManager
{
	SINGLETON(VCoroutineManager);
	
private:
	// ����� ��ƾ��ұ� (�ڷ�ƾ�� ȣ�� �ֱⰡ �Ϸ�Ǿ����� üũ�� ��ü)	
	vector<VCoroutine*> m_vWaitForSecond;	// ���࿹���� WaitForSecond
	vector<VCoroutine*> m_vWaitForOneFrame;	// ���࿹���� WaitForOneFrame


private:	// CoroutineData ĳ��
	VObject* ownerCache;		// �ڷ�ƾ ���� ��û ��ü ĳ��	
	void (VObject::*vCFunc)(void);		// void Cache Function
	void (VObject::*fCFunc)(float);		// float Cache Function
	float m_fCacheParam;		// �ӽ� ���� ���庯��

public:	// Get
	vector<VCoroutine*>& GetWaitForSecondVector()	{ return m_vWaitForSecond; }
	vector<VCoroutine*>& GetWaitForOneFrameVector() { return m_vWaitForOneFrame; }

	void (VObject::*GetVoidFunction() const)(void) { return vCFunc; }
	void (VObject::*GetFloatFunction() const)(float) { return fCFunc; }
	float GetCacheParam() { return m_fCacheParam; }
	VObject* GetOwnerCache() { return ownerCache; }

	
public:	// Set
	void SetOwnerCache(VObject* _owner) { ownerCache = _owner; }
	template<typename T>
	void SetVoidFuncPointer(void(T::*vf)(void)) { vCFunc = vf; }
	template<typename T>
	void SetFloatFuncPointer(void(T::*ff)(float), float _f) { fCFunc = ff; m_fCacheParam = _f; }
	void ClearCache();

	

public: // Update
	void UpdateWaitForOneFrame();
	void UpdateWaitForSecond();

public:
	void Init();
	void AddCoroutine(VCoroutine* _routine);		// �ڷ�ƾ(Class)�� �����ɰ�� ȣ��� �Լ�
};

