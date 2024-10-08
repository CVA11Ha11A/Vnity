#include "pch.h"
#include "VCollider.h"

#include "VObject.h"
#include "VCore.h"
#include "VCamera.h"

#include "SelectGDI.h"

UINT VCollider::g_iNextID = 0;

VCollider::VCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)	
	, m_iCol(0)
{

}
VCollider::VCollider(const VCollider& _origin)
	:m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{

}
VCollider::~VCollider()
{

}

void VCollider::FinalUpdate()
{
	// Object의 위치로 Collider의 위치를 옮기겠다.
	Vector2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

}

void VCollider::Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
	{
		ePen = PEN_TYPE::RED;
	}

	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vector2 vRenderPos = VCamera::GetInst()->GetWorldToRenderPos(m_vFinalPos);

	Rectangle(_dc,
		(int)vRenderPos.x - (int)m_vScale.x / (int)2.f,
		(int)vRenderPos.y - (int)m_vScale.y / (int)2.f,
		(int)vRenderPos.x + (int)m_vScale.x / (int)2.f,
		(int)vRenderPos.y + (int)m_vScale.y / (int)2.f);

}

void VCollider::OnCollisionEnter(VCollider* _pOther)
{
	m_iCol++;
	m_pOwner->OnCollisionEnter(_pOther);
}

void VCollider::OnCollisionStay(VCollider* _pOther)
{
	m_pOwner->OnCollisionStay(_pOther);
}

void VCollider::OnCollisionExit(VCollider* _pOther)
{
	m_pOwner->OnCollisionExit(_pOther);
	m_iCol--;
	assert(0 <= m_iCol);
}
