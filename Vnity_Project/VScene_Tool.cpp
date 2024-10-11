#include "pch.h"
#include "VScene_Tool.h"

#include "VKeyManager.h"
#include "VSceneManager.h"
#include "VTile.h"
#include "VUI.h"

#include "VCore.h"
#include "VResourceManager.h"
#include "VSceneManager.h"
#include "VUIManager.h"
#include "VPathManager.h"

#include "resource.h"
#include "VPanelUI.h"
#include "VButtonUI.h"


void ChangeScene(DWORD_PTR, DWORD_PTR);

VScene_Tool::VScene_Tool()
	:m_pUI(nullptr)
{
}

VScene_Tool::~VScene_Tool()
{
}

void VScene_Tool::SceneEnter()
{	
	VCore::GetInst()->DockMenu();

	// 타일 생성
	CreateTile(5, 5);

	// UI 하나 만들어보기
	Vector2 vResolution = VCore::GetInst()->GetResolution();

	VUI* pPanelUI = new VPanelUI();
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vector2(500.f, 300.f));
	pPanelUI->SetPos(Vector2(vResolution.x - pPanelUI->GetScale().x, 0.f));
	AddObject(pPanelUI, GROUP_TYPE::UI);

	VButtonUI* pBtnUI = new VButtonUI();
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vector2(100.f, 40.f));
	pBtnUI->SetPos(Vector2(0.f, 0.f));
	((VButtonUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)& VScene_Tool::SaveTileData);

	pPanelUI->AddChild(pBtnUI);



	// UI 복사본
	/*VUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vector2(-50.f, 0.f));
	((VButtonUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);

	AddObject(pClonePanel, E_GROUP_TYPE::UI);

	m_pUI = pClonePanel;*/

	//Camera Look 지정	
	VCamera::GetInst()->SetLookAt(vResolution / 2);

}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(E_SCENE_TYPE::START);
}

void VScene_Tool::SceneExit()
{
	VCore::GetInst()->DivideMenu();
	DeleteAll();
}

void VScene_Tool::Update()
{
	VScene::Update();

	SetTileIdx();

	if (KEY_ENTER(KEY::LSHIFT))
	{
		//VUIManager::GetInst()->SetFocusedUI(m_pUI);
		SaveTileData();
	}

	if (KEY_ENTER(KEY::CTRL))
	{
		LoadTileData();
	}

	if (KEY_ENTER(KEY::SPACE))
	{
		ChangeScene(E_SCENE_TYPE::START);
	}

}		// Update()

void VScene_Tool::SetTileIdx()
{
	if (KEY_ENTER(KEY::LBTN))
	{
		Vector2 vMousePos = MOUSE_POS;
		vMousePos = VCamera::GetInst()->GetRenderToWorldPos(vMousePos);		// 클릭한 포지션 World포지션으로 가져옴

		int iTileX = (int)GetTileX();	// 현재 타일의 X축의 갯수
		int iTileY = (int)GetTileY();	// 현재 타일의 Y축의 갯수

		int iCol = (int)vMousePos.x / TILE_SIZE;		// 현재 누른 X 위치 / 타일의 사이즈 나눔
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<VObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((VTile*)vecTile[iIdx])->AddImgIdx();

	}

}		// SetTileIdx()

void VScene_Tool::SaveTileData()
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
	if (GetSaveFileName(&ofn))
	{
		//VPathManager::GetInst()->GetRelativePath(szName);
		SaveTile(szName);
	}

}

void VScene_Tool::SaveTile(const wstring& _strFilePath)
{
	/*wstring strFilePath = VPathManager::GetInst()->GetContentPath();
	strFilePath += _strFilePath;*/

	// FILE도 결국 커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	//assert(pFile);

	// 타일 가로세로 갯수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
	const vector<VObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((VTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);

}		// SaveTile()








//	------------------------------------------
//  Tile Count Window Proc	// 해당함수는 프로시저함수임 멤버함수가 아님
//  ------------------------------------------
// CALLBACK = __stdcall : 함수 호출 규약
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			VScene* pCurScene = VSceneManager::GetInst()->GetCurScene();

			// dynamic_cast = 캐스팅에 성공하면 실제 개체가 나오고 실패하면 null이 나옴 C# is와 유사
			VScene_Tool* pToolScene = dynamic_cast<VScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
