#pragma once
#include "pch.h"
#include "VObject.h"

#include "VCollider.h"
#include "VAnimator.h"
#include "VRigidbody.h"

VObject::VObject()
	:m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_bAlive(true)
{
}

VObject::VObject(const VObject& _origin)
	:m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_bAlive(true)
{
	if (_origin.m_pCollider != nullptr)
	{
		m_pCollider = new VCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator != nullptr)
	{
		m_pAnimator = new VAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
	if (_origin.m_pRigidBody != nullptr)
	{
		m_pRigidBody = new VRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}
	
}



VObject::~VObject()
{
	if (m_pCollider != nullptr)
	{
		delete m_pCollider;
	}

	if (m_pAnimator != nullptr)
	{
		delete m_pAnimator;
	}
	if (m_pRigidBody != nullptr)
	{
		delete m_pRigidBody;
	}

}



void VObject::Update()
{
}

void VObject::FinalUpdate()
{	
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->FinalUpdate();
	}

	if (m_pRigidBody != nullptr)
	{
		m_pRigidBody->FinalUpdate();
	}

	if (m_pCollider != nullptr)
	{
		m_pCollider->FinalUpdate();
	}

}		// FinalUpdate()

void VObject::Render(HDC _dc)
{
	Vector2 vRenderPos = VCamera::GetInst()->GetWorldToRenderPos(m_vPos);

	Rectangle(_dc,
		(int)vRenderPos.x - (int)m_vScale.x / 2,
		(int)vRenderPos.y - (int)m_vScale.y / 2,
		(int)vRenderPos.x + (int)m_vScale.x / 2,
		(int)vRenderPos.y + (int)m_vScale.y / 2);

	Component_Render(_dc);

}

void VObject::Component_Render(HDC _dc)
{
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Render(_dc);
	}

#ifdef _DEBUG
	if (m_pCollider != nullptr)
	{
		m_pCollider->Render(_dc);
	}
#endif

}

void VObject::CreateCollider()
{
	m_pCollider = new VCollider();
	m_pCollider->m_pOwner = this;

}

void VObject::CreateAnimator()
{	
	m_pAnimator = new VAnimator();
	m_pAnimator->m_pOwner = this;
}

void VObject::CreateRigidBody()
{
	m_pRigidBody = new VRigidBody();
	m_pRigidBody->m_pOwner = this;
}
