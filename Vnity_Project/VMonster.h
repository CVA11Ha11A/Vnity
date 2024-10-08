#pragma once
#include "VObject.h"


struct tMonInfo
{
	float	m_fSpeed;		// �ӵ�
	float	m_fHP;			// ü��
	float	m_fRecogRange;	// ���� ����
	float	m_fAttRange;	// ���� ����
	float	m_fAtt;			// ���ݷ�
};



class VAI;

class VMonster : public VObject
{

public:
	

private:
	tMonInfo m_tInfo;

	VAI*	m_pAI;

public:
	void	SetAI(VAI* _pAI);
	float	GetSpeed() { return m_tInfo.m_fSpeed; }
	void	SetSpeed(float _speed) { m_tInfo.m_fSpeed = _speed; }
	const tMonInfo& GetInfo() { return m_tInfo; }

	//void	SetCenterPos(Vector2 _pos) { this->m_vCenterPos = _pos; }
	//void	SetMaxDistance(float _newDistance) { this->m_fMaxDistance = _newDistance; }	
	//Vector2 GetCenterPos() { return m_vCenterPos; }

private:
	void SetMonInfo(const tMonInfo& _info)
	{
		m_tInfo = _info;
	}


public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();


	virtual void OnCollisionEnter(VCollider* _pOhter);
	virtual VMonster* Clone() { return new VMonster(*this); }

public:
	VMonster();
	virtual ~VMonster();

	friend class VMonFactory;

};

