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

	// Ÿ�� ����
	CreateTile(5, 5);

	// UI �ϳ� ������
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



	// UI ���纻
	/*VUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vector2(-50.f, 0.f));
	((VButtonUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);

	AddObject(pClonePanel, E_GROUP_TYPE::UI);

	m_pUI = pClonePanel;*/

	//Camera Look ����	
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
		vMousePos = VCamera::GetInst()->GetRenderToWorldPos(vMousePos);		// Ŭ���� ������ World���������� ������

		int iTileX = (int)GetTileX();	// ���� Ÿ���� X���� ����
		int iTileY = (int)GetTileY();	// ���� Ÿ���� Y���� ����

		int iCol = (int)vMousePos.x / TILE_SIZE;		// ���� ���� X ��ġ / Ÿ���� ������ ����
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

	// Modal ��� : ��� ��Ŀ���� �ڱⰡ �������� ���ϵǱ� ������ �ٸ� ������ ��� �Ұ� 
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

	// FILE�� �ᱹ Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	//assert(pFile);

	// Ÿ�� ���μ��� ���� ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// ��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��
	const vector<VObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((VTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);

}		// SaveTile()








//	------------------------------------------
//  Tile Count Window Proc	// �ش��Լ��� ���ν����Լ��� ����Լ��� �ƴ�
//  ------------------------------------------
// CALLBACK = __stdcall : �Լ� ȣ�� �Ծ�
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

			// dynamic_cast = ĳ���ÿ� �����ϸ� ���� ��ü�� ������ �����ϸ� null�� ���� C# is�� ����
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
