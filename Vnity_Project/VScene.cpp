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
				// m_arrObj[i] 그룹 벡터의 j 물체를 삭제
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
{	// TODO : Awake, Start함수 라이프사이클로 돌려야함 (현재기준 씬 Enter에서 1회 호출 24.10.05)
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

	Vector2 vCamLook = VCamera::GetInst()->GetLookAt();		 // 카메라가 바라보고있는좌표
	Vector2 vResolution = VCore::GetInst()->GetResolution(); // 해상도
	Vector2 vLeftTop = vCamLook - vResolution / 2.f;		 // 현재 보고있는 카메라의 좌상단 좌표

	int iTileSize = TILE_SIZE;

	int iLTCol = (int)vLeftTop.x / iTileSize;	// 행 구하기
	int iLTRow = (int)vLeftTop.y / iTileSize;	// 열 구하기



	int iClientWidth = ((int)vResolution.x / iTileSize) + 1;
	int iClientHeight = ((int)vResolution.y / iTileSize) + 1;

	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{

			if (iCurCol < 0 || m_iTileX <= static_cast<unsigned int>(iCurCol)
				|| iCurRow < 0 || m_iTileY <= static_cast<unsigned int>(iCurRow))
			{	// if : 렌더할 것보다 삐져나가면 (음수이거나 초과할 경우)
				continue;
			}


			int iIdx = (m_iTileX * iCurRow) + iCurCol;
			vecTile[iIdx]->Render(_dc);
		}
	}
	// ! note : TILE은 Dead가 되지 않는다는 가정하에 렌더중 (타일이 사라져야한다면 Dead처리 추가해야함)

}		// Render_Tile()


void VScene::DeleteGroup(GROUP_TYPE _eTarget)
{
#pragma region Before (특정 오브젝트 지우지 못하기 전)
	// Safe_Delete_Vec<VObject*>(m_arrObj[(UINT)_eTarget]);
#pragma endregion

#pragma region 씬이동시 설정한 오브젝트 제거 방지
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
		{	// else if : 지우면 안되는 오브젝트(DonDestroy함수 호출한 개체)라면 진입

			// 자신이 가지고 있던 지우면 안되는 오브젝트를 다음씬에 넘긴후 현재의 인덱스를 nullptr로 할당			
			VSceneManager::GetInst()->GetScene((E_SCENE_TYPE)nextScene.lParam)
				->AddObject(targetVector[i], targetVector[i]->GetObjGroup());						
		}
	}
	targetVector.clear();
#pragma endregion 씬이동시 설정한 오브젝트 제거 방지

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

	// 타일 생성
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

	// FILE도 결국 커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// 타일 가로 세로 개수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;


	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// 불러온 개수에 맞게 EmptyTile 들 만들어두기
	CreateTile(xCount, yCount);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 함
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

	// Modal 방식 : 모든 포커싱을 자기가 가져가고 리턴되기 전까지 다른 윈도우 사용 불가
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = VPathManager::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}

}		// LoadTileData()

