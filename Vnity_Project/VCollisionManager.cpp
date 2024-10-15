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
		{	// if : Left�� ������Ʈ�� Collider�� �������� �ʴ´ٸ� �ǳʶ�
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j])
			{	// if : Collider�� ���ų� �ڱ� �ڽŰ��� �浹�� ��� �ǳʶٱ�
				continue;
			}

			VCollider* pLeftCol = vecLeft[i]->GetCollider();
			VCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();


			iter = m_mapColInfo.find(ID.ID);

			if (iter == m_mapColInfo.end())
			{	// if : �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴ� ��)
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}



			if (IsCollision(pLeftCol, pRightCol))
			{	// if : ���� �浹 ���̴�.

				if (iter->second == true)
				{	// if : �������� �浹 �ϰ� �־���.

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{	// if : �� �浹ü�� �����ϳ��� ���� �����̶�� �浹Ż�� �Լ� ȣ��
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
				{	// else : �������� �浹���� �ʾҴ�.

					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{	// if : �� �浹ü�� �����ϳ��� ���� �����̶�� �浹���� ���������� ���
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}					
				}

			}
			else
			{	// else : ���� �浹�ϰ� ���� �ʴ�.
				if (iter->second)
				{	// if : �������� �浹�ϰ� �־���. (�̹��� Ż�� �ߴ�.)
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}


		}

	}

}		// CollisionGroupUpdate()

/// <summary>
/// �浹 ���� Ȯ�� �Լ�
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���
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


