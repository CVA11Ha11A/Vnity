#pragma once

class VObject;

class VRigidBody
{
private:
	VObject* m_pOwner;		// 소유 객체

	// RigidBody
	// F = M * A;
	// V += A * DT
	Vector2		m_vForce;		// 크기, 방향
	Vector2		m_vAccel;		// 가속도
	Vector2		m_vAccelA;		// 가속도 추가 (알파)
	Vector2		m_vVelocity;	// 속도 ( 크기 : 속력, 방향)
	Vector2		m_vMaxVelocity; // 최대 속도

	float		m_fMass;		// 질량
	// 정지마찰계수(운동마찰계수보다큼) , 운동마찰계수 설정하지않고 한가지로 구현함
	float		m_fFricCoeff;	// 마찰 계수


	// Gravity
	float		m_fGravityScale;		// 중력의 영향을 받을 정도(Default == 1)
	bool		m_bIsGravityInfluence;	// 중력의 영향을 받을것인지 bool값 (Default == true)

	bool		m_bIsGround;			// 땅에 붙어있는지




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

