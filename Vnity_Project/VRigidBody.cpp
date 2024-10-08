#include "pch.h"
#include "VRigidBody.h"

#include "VObject.h"

#include "VTimeManager.h"



VRigidBody::VRigidBody()
	:m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vector2(200.f, 600.f))
	, m_fGravityScale(1.f)
	, m_bIsGravityInfluence(true)
	, m_bIsGround(false)
{
}

VRigidBody::~VRigidBody()
{
}

void VRigidBody::FinalUpdate()
{
	if (m_bIsGravityInfluence == true)
	{	// if : 중력 영향을 받는다 설정이 되었다면 진입
		GravityFinalUpdate();
	}

	// RigidBody
	// m_vForce;	// 여기엔 힘의 방향정보, 크기정보가 들어있음
	// 순수 힘의 정보(크기)
	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{	// if : 힘(fForce)이 존재하면 진입
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;

		// 가속도 = 방향 * 속도의 크기
		m_vAccel = m_vForce * m_fAccel;
	}

	// 추가 가속도
	m_vAccel += m_vAccelA;

	// 속도
	m_vVelocity += m_vAccel * DeltaTime;

	// 마찰력에의한 반대방향으로의 가속도
	if (!m_vVelocity.IsZero())
	{
		Vector2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vector2 vFriction = vFricDir * m_fFricCoeff * DeltaTime;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 큰 경우
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// 속도 제한 검사
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{		
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = Vector2(0.f, 0.f);
	// 가속도, 추가 가속도 초기화
	m_vAccel = Vector2(0.f, 0.f);
	m_vAccelA = Vector2(0.f, 0.f);




}		// FinalUpdate()


void VRigidBody::GravityFinalUpdate()
{
	SetAccelAlpha(Vector2(0.f, 500.f));
}	// GravityFinalUpdate()

void VRigidBody::SetGround(bool _b)
{
	m_bIsGround = _b;

	if (m_bIsGround == true)
	{
		SetVelocity(Vector2(GetVelocity().x, 0.f));
	}
}		// SetGround()


void VRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f)
	{
		// 이동 방향
		Vector2 vDir = m_vVelocity;
		vDir.Normalize();

		Vector2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * DeltaTime;

		m_pOwner->SetPos(vPos);
	}
}		// Move()

