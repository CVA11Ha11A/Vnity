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
	// �ڷ�ƾ �ӽ� �ּ�
	//VObject* ownerCache;		// �ڷ�ƾ ���� ��û ��ü ĳ��	
	//void (VObject::*vCFunc)(void);		// void Cache Function
	//void (VObject::*fCFunc)(float);		// float Cache Function
	//float m_fCacheParam;		// �ӽ� ���� ���庯��

public:	// Get
	vector<VCoroutine*>& GetWaitForSecondVector()	{ return m_vWaitForSecond; }
	vector<VCoroutine*>& GetWaitForOneFrameVector() { return m_vWaitForOneFrame; }	

	
public:	// Set



public: // Update
	void UpdateWaitForOneFrame();
	void UpdateWaitForSecond();

public:
	void Init();
	void AddCoroutine(VCoroutine* _routine);		// �ڷ�ƾ(Class)�� �����ɰ�� ȣ��� �Լ�
};

