#pragma once


class VTimeManager
{
	SINGLETON(VTimeManager);
private:
	// FPS�� �˸� 1�����Ӵ� �ɸ��� �ð��� �� �� ���� // Delta Time = 1�����ӿ� �ɸ��� �ð�
	LARGE_INTEGER	m_CurCount;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_Frequency;

	float			m_DeltaTime;	// ������ ���� �ð���
	float			m_dAcc;			// 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	// �ʴ� ȣ�� Ƚ��
	UINT			m_FPS;			// �ʴ� ������


public:
	void Init();
	void Update();
	void Render();

public:
	 float GetDeltaTime() { return m_DeltaTime; }	 
	 //float GetDeltaTime() { return (float)m_DeltaTime; }

};

