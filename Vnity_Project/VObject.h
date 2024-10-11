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
	wstring		m_strName;		// ������Ʈ�� �̸�
	Vector2		m_vPos;
	Vector2		m_vScale;

	GROUP_TYPE  m_eObjGroup;		// ������Ʈ�� � �׷��� ���� ��ü����(��������� �����ɰ���)

	// Component
	VCollider*	m_pCollider;
	VAnimator*	m_pAnimator;
	VRigidBody* m_pRigidBody;

	bool		m_bAlive;		// ������Ʈ ���� ����(���� ��������)

private:
	bool		m_bIsDonDestroy;	// ������Ʈ ���� ���� ����(!�� �̵���!) (Alive ���ο��� �ı� ����)


public:
	void SetPos(Vector2 _vPos) { this->m_vPos = _vPos; }
	void SetScale(Vector2 _vScale) { this->m_vScale = _vScale; }

	Vector2 GetPos() { return this->m_vPos; }
	Vector2 GetScale() { return this->m_vScale; }

	GROUP_TYPE GetObjGroup() { return  this->m_eObjGroup; }
	void SetObjGroup(GROUP_TYPE _group) { this->m_eObjGroup = _group; }

	VCollider* GetCollider() { return this->m_pCollider; }
	VAnimator* GetAnimator() { return this->m_pAnimator; }
	VRigidBody* GetRigidBody() { return this->m_pRigidBody; }

	const wstring& GetName() { return this->m_strName; }
	void SetName(const wstring& _strName) { this->m_strName = _strName; }

	
	bool IsDead() { return !m_bAlive; }	

	void DonDestroy() { this->m_bIsDonDestroy = true; }
	bool GetIsDonDestroy() { return m_bIsDonDestroy; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

	virtual void OnCollisionStay(VCollider* _pOther) {}		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	virtual void OnCollisionEnter(VCollider* _pOther) {}		// �浹 ���Խ�
	virtual void OnCollisionExit(VCollider* _pOther) {}		// �浹 Ż���

private:
	void SetDead() { m_bAlive = false; }


public:
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	void Component_Render(HDC _dc);

	virtual VObject* Clone() = 0;		// ���� ��ü�� �ڽ��� �������ִ� �Լ��� �����Ұ�

public:
	VObject();
	VObject(const VObject& _origin);
	virtual ~VObject();


	
};

