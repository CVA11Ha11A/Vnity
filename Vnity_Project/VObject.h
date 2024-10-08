#pragma once
#include "VGlobal.h"

#include "VCamera.h"

class VCollider;
class VAnimator;
class VRigidBody;


class VObject
{
	friend class VEventManager;

private:
	wstring		m_strName;		// 오브젝트의 이름
	Vector2		m_vPos;
	Vector2		m_vScale;

	// Component
	VCollider*	m_pCollider;
	VAnimator*	m_pAnimator;
	VRigidBody* m_pRigidBody;

	bool		m_bAlive;		// 오브젝트 생존 여부(삭제 예정인지)

public:
	void SetPos(Vector2 _vPos) { this->m_vPos = _vPos; }
	void SetScale(Vector2 _vScale) { this->m_vScale = _vScale; }

	Vector2 GetPos() { return this->m_vPos; }
	Vector2 GetScale() { return this->m_vScale; }

	VCollider* GetCollider() { return this->m_pCollider; }
	VAnimator* GetAnimator() { return this->m_pAnimator; }
	VRigidBody* GetRigidBody() { return this->m_pRigidBody; }

	const wstring& GetName() { return this->m_strName; }
	void SetName(const wstring& _strName) { this->m_strName = _strName; }

	bool IsDead() { return !m_bAlive; }	

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

	virtual void OnCollisionStay(VCollider* _pOther) {}		// 충돌 중인 경우 호출되는 함수
	virtual void OnCollisionEnter(VCollider* _pOther) {}		// 충돌 진입시
	virtual void OnCollisionExit(VCollider* _pOther) {}		// 충돌 탈출시

private:
	void SetDead() { m_bAlive = false; }


public:
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	void Component_Render(HDC _dc);

	virtual VObject* Clone() = 0;		// 각자 개체는 자신을 복제해주는 함수를 구현할것

public:
	VObject();
	VObject(const VObject& _origin);
	virtual ~VObject();


	
};

