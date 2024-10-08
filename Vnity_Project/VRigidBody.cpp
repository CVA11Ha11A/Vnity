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
	{	// if : �߷� ������ �޴´� ������ �Ǿ��ٸ� ����
		GravityFinalUpdate();
	}

	// RigidBody
	// m_vForce;	// ���⿣ ���� ��������, ũ�������� �������
	// ���� ���� ����(ũ��)
	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{	// if : ��(fForce)�� �����ϸ� ����
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		// ���ӵ� = ���� * �ӵ��� ũ��
		m_vAccel = m_vForce * m_fAccel;
	}

	// �߰� ���ӵ�
	m_vAccel += m_vAccelA;

	// �ӵ�
	m_vVelocity += m_vAccel * DeltaTime;

	// �����¿����� �ݴ���������� ���ӵ�
	if (!m_vVelocity.IsZero())
	{
		Vector2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vector2 vFriction = vFricDir * m_fFricCoeff * DeltaTime;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� ū ���
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// �ӵ� ���� �˻�
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{		
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	m_vForce = Vector2(0.f, 0.f);
	// ���ӵ�, �߰� ���ӵ� �ʱ�ȭ
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
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f)
	{
		// �̵� ����
		Vector2 vDir = m_vVelocity;
		vDir.Normalize();

		Vector2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * DeltaTime;

		m_pOwner->SetPos(vPos);
	}
}		// Move()

