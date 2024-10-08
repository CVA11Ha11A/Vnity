#pragma once

class VObject;

class VCollider
{
private:
	static UINT g_iNextID;

	VObject*	m_pOwner;		// 자신을 소유하고있는 Object의 포인터
	Vector2		m_vOffsetPos;	// Offset : 어떠한 기준위치에서 떨어진 정도 // 오브젝트로 부터 상대적인 위치
	Vector2		m_vFinalPos;	// FinalUpdate에서 매 프레임마다 계산
	Vector2		m_vScale;		// Collider의 크기

	UINT		m_iID;			// 콜라이더의 고유한 ID 값
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
	void OnCollisionStay(VCollider* _pOther);		// 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(VCollider* _pOther);		// 충돌 진입시
	void OnCollisionExit(VCollider* _pOther);		// 충돌 탈출시

	// 대입연산자 방어(콜라이더끼리 대입하지 못하게 막기)
	VCollider& operator = (VCollider& _origin) = delete;



public:
	VCollider();
	VCollider(const VCollider& _origin);
	~VCollider();

	friend class VObject;

};

