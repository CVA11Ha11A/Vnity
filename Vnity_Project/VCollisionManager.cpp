#include "pch.h"
#include "VCollisionManager.h"

#include "VSceneManager.h"
#include "VScene.h"
#include "VObject.h"
#include "VCollider.h"




VCollisionManager::VCollisionManager()
	:m_arrCheck{}
{

}
VCollisionManager::~VCollisionManager()
{

}


void VCollisionManager::Init()
{

}

void VCollisionManager::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		m_arrCheck[iRow];
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}


void VCollisionManager::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	VScene* pCurScene = VSceneManager::GetInst()->GetCurScene();

	const vector<VObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<VObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (vecLeft[i]->GetCollider() == nullptr)
		{	// if : Left의 오브젝트가 Collider가 존재하지 않는다면 건너뜀
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j])
			{	// if : Collider가 없거나 자기 자신과의 충돌인 경우 건너뛰기
				continue;
			}

			VCollider* pLeftCol = vecLeft[i]->GetCollider();
			VCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();


			iter = m_mapColInfo.find(ID.ID);

			if (iter == m_mapColInfo.end())
			{	// if : 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다 로)
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}



			if (IsCollision(pLeftCol, pRightCol))
			{	// if : 현재 충돌 중이다.

				if (iter->second == true)
				{	// if : 이전에도 충돌 하고 있었다.

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{	// if : 두 충돌체중 둘중하나라도 삭제 예정이라면 충돌탈출 함수 호출
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollisionStay(pRightCol);
						pRightCol->OnCollisionStay(pLeftCol);
					}
					
				}
				else
				{	// else : 이전에는 충돌하지 않았다.

					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{	// if : 두 충돌체중 둘중하나라도 삭제 예정이라면 충돌하지 않은것으로 취급
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}					
				}

			}
			else
			{	// else : 현재 충돌하고 있지 않다.
				if (iter->second)
				{	// if : 이전에는 충돌하고 있었다. (이번엔 탈출 했다.)
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}


		}

	}

}		// CollisionGroupUpdate()

/// <summary>
/// 충돌 여부 확인 함수
/// </summary>
bool VCollisionManager::IsCollision(VCollider* _pLeftCol, VCollider* _pRightCol)
{
	Vector2 vLeftPos = _pLeftCol->GetFinalPos();
	Vector2 vLeftScale = _pLeftCol->GetScale();

	Vector2 vRightPos = _pRightCol->GetFinalPos();
	Vector2 vRightScale = _pRightCol->GetScale();

	if (abs(vLeftPos.x - vRightPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vLeftPos.y - vRightPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}




void VCollisionManager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트) 로 사용
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}




}


