#include "VGround.h"


#include "VCollider.h"
#include "VRigidBody.h"


VGround::VGround()
{
	SetObjGroup(GROUP_TYPE::GROUND);
	CreateCollider();

}
VGround::~VGround()
{

}


void VGround::Awake()
{
}

void VGround::Start()
{
	GetCollider()->SetScale(Vector2(GetScale()));
}

void VGround::Update()
{

}

void VGround::OnCollisionEnter(VCollider* _pOther)
{
	VObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		if (pOtherObj->GetRigidBody())
		{
			pOtherObj->GetRigidBody()->SetGround(true);

			Vector2 vObjPos = _pOther->GetFinalPos();
			Vector2 vObjScale = _pOther->GetScale();

			Vector2 vPos = GetCollider()->GetFinalPos();
			Vector2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.y - vPos.y);
			float fPushValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			// 충돌을 접한상태로 유지하기 위해서 일부러 1픽셀 덜 올려줌
			vObjPos = pOtherObj->GetPos();
			vObjPos.y -= (fPushValue - 1.f);

			pOtherObj->SetPos(vObjPos);
		}
	}

}		// OnCollisionEnter()

void VGround::OnCollisionStay(VCollider* _pOther)
{
	VObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		if (pOtherObj->GetRigidBody())
		{
			pOtherObj->GetRigidBody()->SetGround(true);

			Vector2 vObjPos = _pOther->GetFinalPos();
			Vector2 vObjScale = _pOther->GetScale();

			Vector2 vPos = GetCollider()->GetFinalPos();
			Vector2 vScale = GetCollider()->GetScale();

			float fLen = abs(vObjPos.y - vPos.y);
			float fPushValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			// 충돌을 접한상태로 유지하기 위해서 일부러 1픽셀 덜 올려줌
			vObjPos = pOtherObj->GetPos();
			vObjPos.y -= fPushValue;

			pOtherObj->SetPos(vObjPos);
		}
	}

}		// OnCollisionStay()

void VGround::OnCollisionExit(VCollider* _pOther)
{
	VObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		if (pOtherObj->GetRigidBody())
		{
			pOtherObj->GetRigidBody()->SetGround(false);
		}
	}

}		// OnCollisionExit()
