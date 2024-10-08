#pragma once

class VObject;

class VRigidBody
{
private:
	VObject* m_pOwner;		// ���� ��ü

	// RigidBody
	// F = M * A;
	// V += A * DT
	Vector2		m_vForce;		// ũ��, ����
	Vector2		m_vAccel;		// ���ӵ�
	Vector2		m_vAccelA;		// ���ӵ� �߰� (����)
	Vector2		m_vVelocity;	// �ӵ� ( ũ�� : �ӷ�, ����)
	Vector2		m_vMaxVelocity; // �ִ� �ӵ�

	float		m_fMass;		// ����
	// �����������(������������ŭ) , �������� ���������ʰ� �Ѱ����� ������
	float		m_fFricCoeff;	// ���� ���


	// Gravity
	float		m_fGravityScale;		// �߷��� ������ ���� ����(Default == 1)
	bool		m_bIsGravityInfluence;	// �߷��� ������ ���������� bool�� (Default == true)

	bool		m_bIsGround;			// ���� �پ��ִ���




public:
	void FinalUpdate();


public:	// RigidBody
	void  AddForce(Vector2 _vForce) { m_vForce += _vForce; }
	void  AddVelocity(Vector2 _v) { m_vVelocity += _v; }

	float GetSpeed() { return m_vVelocity.Length(); }
	float GetMass() { return m_fMass; }
	Vector2 GetVelocity() { return m_vVelocity; }


	void SetMaxVelocity(Vector2 _MaxVelocity) { m_vMaxVelocity = _MaxVelocity; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	void SetVelocity(Vector2 _v) { m_vVelocity = _v; }
	void SetAccelAlpha(Vector2 _vAccel) { m_vAccelA = _vAccel; }

public:	// Gravity
	void  GravityFinalUpdate();
	float SetGravityScale(float _fGravityScale) { m_fGravityScale = _fGravityScale; }
	void  SetGravityInfluence(bool _bIsGravityInfluence) { m_bIsGravityInfluence = _bIsGravityInfluence; }
	void  SetGround(bool _b);

private:
	void Move();


public:
	VRigidBody();
	~VRigidBody();


	friend class VObject;
};

