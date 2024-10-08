#pragma once

class VCollider;

union COLLIDER_ID
{
	struct 
	{
		UINT Left_id;
		UINT Right_id;
	};
	LONGLONG ID;
};

class VCollisionManager
{	// TODO : �⺻������ ��� �浹�� �ǵ��� �����ϱ�
	SINGLETON(VCollisionManager);

private:
	// �浹ü ���� ���� ������ �浹 ����
	map<ULONGLONG, bool> m_mapColInfo;
	UINT				m_arrCheck[(UINT)GROUP_TYPE::END];	// �׷찣�� �浹 üũ ��Ʈ����

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }


private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(VCollider* _pLeftCol, VCollider* _pRightCol);

};

