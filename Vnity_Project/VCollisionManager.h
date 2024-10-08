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
{	// TODO : 기본적으로 모두 충돌이 되도록 설정하기
	SINGLETON(VCollisionManager);

private:
	// 충돌체 간의 이전 프레임 충돌 정보
	map<ULONGLONG, bool> m_mapColInfo;
	UINT				m_arrCheck[(UINT)GROUP_TYPE::END];	// 그룹간의 충돌 체크 메트릭스

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }


private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(VCollider* _pLeftCol, VCollider* _pRightCol);

};

