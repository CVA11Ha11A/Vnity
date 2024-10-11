#pragma once
#include "pch.h"
#include "VCore.h"
#include "VScene.h"


#include "VObject.h"
#include "VTile.h"

#include "VSceneManager.h"
#include "VResourceManager.h"
#include "VPathManager.h"
#include "VEventManager.h"
#include "VCamera.h"



VScene::VScene()
	:m_iTileX(0)
	, m_iTileY(0)
	, m_pPlayer(nullptr)
{
}

VScene::~VScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j] != nullptr)
			{
				// m_arrObj[i] �׷� ������ j ��ü�� ����
				delete m_arrObj[i][j];
			}
		}
	}
}
void VScene::AddObject(VObject* _pObj, GROUP_TYPE _eType)
{
	m_arrObj[(UINT)_eType].push_back(_pObj);
}



void VScene::Awake()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j] == nullptr)
			{
				assert(nullptr);
				continue;
			}
			m_arrObj[i][j]->Awake();
		}
	}
}

void VScene::Start()
{	// TODO : Awake, Start�Լ� ����������Ŭ�� �������� (������� �� Enter���� 1ȸ ȣ�� 24.10.05)
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j] != nullptr)
			{
				VObject* temp = m_arrObj[i][j];
				m_arrObj[i][j]->Start();
			}
			else
			{
				// Pass
			}
		}
	}
}		// Start()

void VScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j] == nullptr)
			{
				continue;
			}
			if (m_arrObj[i][j]->IsDead() == false)
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}		// Update()

void VScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j] == nullptr)
			{
				continue;
			}
			m_arrObj[i][j]->FinalUpdate();
		}
	}

}		// FinalUpdate()


void VScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if (i == (UINT)GROUP_TYPE::TILE)
		{
			Render_Tile(_dc);
			continue;
		}

		vector<VObject*>::iterator iter = m_arrObj[i].begin();

		if (iter == m_arrObj[i].end() || *iter == nullptr)
		{
			continue;
		}

		for (; iter != m_arrObj[i].end(); )
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}

}		// Render()

void VScene::Render_Tile(HDC _dc)
{
	const vector<VObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vector2 vCamLook = VCamera::GetInst()->GetLookAt();		 // ī�޶� �ٶ󺸰��ִ���ǥ
	Vector2 vResolution = VCore::GetInst()->GetResolution(); // �ػ�
	Vector2 vLeftTop = vCamLook - vResolution / 2.f;		 // ���� �����ִ� ī�޶��� �»�� ��ǥ

	int iTileSize = TILE_SIZE;

	int iLTCol = (int)vLeftTop.x / iTileSize;	// �� ���ϱ�
	int iLTRow = (int)vLeftTop.y / iTileSize;	// �� ���ϱ�



	int iClientWidth = ((int)vResolution.x / iTileSize) + 1;
	int iClientHeight = ((int)vResolution.y / iTileSize) + 1;

	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{

			if (iCurCol < 0 || m_iTileX <= static_cast<unsigned int>(iCurCol)
				|| iCurRow < 0 || m_iTileY <= static_cast<unsigned int>(iCurRow))
			{	// if : ������ �ͺ��� ���������� (�����̰ų� �ʰ��� ���)
				continue;
			}


			int iIdx = (m_iTileX * iCurRow) + iCurCol;
			vecTile[iIdx]->Render(_dc);
		}
	}
	// ! note : TILE�� Dead�� ���� �ʴ´ٴ� �����Ͽ� ������ (Ÿ���� ��������Ѵٸ� Deadó�� �߰��ؾ���)

}		// Render_Tile()


void VScene::DeleteGroup(GROUP_TYPE _eTarget)
{
#pragma region Before (Ư�� ������Ʈ ������ ���ϱ� ��)
	// Safe_Delete_Vec<VObject*>(m_arrObj[(UINT)_eTarget]);
#pragma endregion

#pragma region ���̵��� ������ ������Ʈ ���� ����
	vector<VObject*>& targetVector = m_arrObj[(UINT)_eTarget];
	tEvent nextScene = VEventManager::GetInst()->FindNextEvent(E_EVENT_TYPE::SCENE_CHANGE);

	for (size_t i = 0; i < targetVector.size(); ++i)
	{
		if (targetVector[i] != nullptr
			&& targetVector[i]->GetIsDonDestroy() == false)
		{
			delete targetVector[i];
		}
		else if (targetVector[i] != nullptr
			&& targetVector[i]->GetIsDonDestroy() == true)
		{	// else if : ����� �ȵǴ� ������Ʈ(DonDestroy�Լ� ȣ���� ��ü)��� ����

			// �ڽ��� ������ �ִ� ����� �ȵǴ� ������Ʈ�� �������� �ѱ��� ������ �ε����� nullptr�� �Ҵ�			
			VSceneManager::GetInst()->GetScene((E_SCENE_TYPE)nextScene.lParam)
				->AddObject(targetVector[i], targetVector[i]->GetObjGroup());						
		}
	}
	targetVector.clear();
#pragma endregion ���̵��� ������ ������Ʈ ���� ����

}		// DeleteGroup()

void VScene::DeleteAll()
{
	for (size_t i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void VScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	VTexture* pTileTex = VResourceManager::GetInst()->LoadTexture(L"Tile", L"Texture\\Tile\\Tiles.bmp");

	// Ÿ�� ����
	for (UINT i = 0; i < _iYCount; i++)
	{
		for (UINT j = 0; j < _iXCount; j++)
		{
			VTile* pTile = new VTile();
			pTile->SetPos(Vector2((float)(TILE_SIZE * j), (float)(TILE_SIZE * i)));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}

}

void VScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// FILE�� �ᱹ Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// Ÿ�� ���� ���� ���� �ҷ�����
	UINT xCount = 0;
	UINT yCount = 0;


	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// �ҷ��� ������ �°� EmptyTile �� �����α�
	CreateTile(xCount, yCount);

	// ������� Ÿ�� ������ �ʿ��� ������ �ҷ����� ��
	const vector<VObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((VTile*)vecTile[i])->Load(pFile);
	}


	fclose(pFile);
}

void VScene::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = VCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;	// Default : ALL
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFoler = VPathManager::GetInst()->GetContentPath();
	strTileFoler += L"Tile";
	ofn.lpstrInitialDir = strTileFoler.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal ��� : ��� ��Ŀ���� �ڱⰡ �������� ���ϵǱ� ������ �ٸ� ������ ��� �Ұ�
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = VPathManager::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}

}		// LoadTileData()

