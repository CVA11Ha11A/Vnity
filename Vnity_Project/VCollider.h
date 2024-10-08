#pragma once

class VObject;

class VCollider
{
private:
	static UINT g_iNextID;

	VObject*	m_pOwner;		// �ڽ��� �����ϰ��ִ� Object�� ������
	Vector2		m_vOffsetPos;	// Offset : ��� ������ġ���� ������ ���� // ������Ʈ�� ���� ������� ��ġ
	Vector2		m_vFinalPos;	// FinalUpdate���� �� �����Ӹ��� ���
	Vector2		m_vScale;		// Collider�� ũ��

	UINT		m_iID;			// �ݶ��̴��� ������ ID ��
	UINT		m_iCol;

public:
	void SetOffsetPos(Vector2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }

	Vector2 GetOffsetPos()	{ return m_vOffsetPos; }
	Vector2 GetScale()		{ return m_vScale; }
	Vector2 GetFinalPos()	{ return m_vFinalPos; }

	VObject* GetObj()		{ return m_pOwner; }

	UINT	GetID()			{ return m_iID; }


public:
	void FinalUpdate();
	void Render(HDC _dc);



public:
	void OnCollisionStay(VCollider* _pOther);		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(VCollider* _pOther);		// �浹 ���Խ�
	void OnCollisionExit(VCollider* _pOther);		// �浹 Ż���

	// ���Կ����� ���(�ݶ��̴����� �������� ���ϰ� ����)
	VCollider& operator = (VCollider& _origin) = delete;



public:
	VCollider();
	VCollider(const VCollider& _origin);
	~VCollider();

	friend class VObject;

};

