#include "pch.h"
#include "VScene_Start.h"

#include "Test001.h"

#include "VPlayer.h"
#include "VMonster.h"
#include "VGround.h"
#include "VAI.h"
#include "VIdleState.h"
#include "VTraceState.h"

#include "VCore.h"
#include "VTexture.h"

#include "VPathManager.h"
#include "VCollisionManager.h"
#include "VKeyManager.h"
#include "VSceneManager.h"
#include "VTimeManager.h"
#include "VCamera.h"

#include "VRigidBody.h"
#include "SelectGDI.h"

// TestInclude
#include "VUI.h"
#include "VButtonUI.h"
#include "VPanelUI.h"

VScene_Start::VScene_Start()
	:m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fForce(500.f)
	, m_fCurRadius(0.f)
{
}

VScene_Start::~VScene_Start()
{
}


void VScene_Start::Update()
{
	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}


	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<VObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{			
			if (vecObj[j]->IsDead() == false)
			{
				if (m_bUseForce == true && vecObj[j]->GetRigidBody())
				{
					Vector2 vDiff = vecObj[j]->GetPos() -m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio; 

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);						
					}
					
				}
				vecObj[j]->Update();

			}
		}
	}


	if (KEY_ENTER(KEY::SPACE))
	{
		ChangeScene(E_SCENE_TYPE::TOOL);
	}

	//if (KEY_ENTER(E_KEY::LBTN))
	//{
	//	Vector2 vLookAt = VCamera::GetInst()->GetRenderToWorldPos(MOUSE_POS);
	//	VCamera::GetInst()->SetLookAt(vLookAt);
	//}



}		// Update()

void VScene_Start::Render(HDC _dc)
{
	VScene::Render(_dc);

	if (m_bUseForce == true)
	{
		SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

		m_fCurRadius += (m_fForceRadius * 2.f) * DeltaTime;
		if (m_fForceRadius < m_fCurRadius)
		{
			m_fCurRadius = 0.f;
		}

		Vector2 vRenderPos = VCamera::GetInst()->GetWorldToRenderPos(m_vForcePos);

		Ellipse(_dc
			, (int)vRenderPos.x - (int)m_fCurRadius
			, (int)vRenderPos.y - (int)m_fCurRadius
			, (int)vRenderPos.x + (int)m_fCurRadius
			, (int)vRenderPos.y + (int)m_fCurRadius);
	}
}		// Render()



void VScene_Start::SceneEnter()
{
	VObject* test = new Test001();
	AddObject(test, GROUP_TYPE::DEFAULT);


	Vector2 vResolution = VCore::GetInst()->GetResolution();

#pragma region UI
	//// UI 하나 만들어보기
	//VUI* pPanelUI = new VPanelUI();
	//pPanelUI->SetName(L"ParentUI");
	//pPanelUI->SetScale(Vector2(500.f, 300.f));
	//pPanelUI->SetPos(Vector2(vResolution.x - pPanelUI->GetScale().x, 0.f));
	//AddObject(pPanelUI, GROUP_TYPE::UI);
	//
	//VButtonUI* pBtnUI = new VButtonUI();
	//pBtnUI->SetName(L"ChildUI");
	//pBtnUI->SetScale(Vector2(100.f, 40.f));
	//pBtnUI->SetPos(Vector2(0.f, 0.f));		
	//pPanelUI->AddChild(pBtnUI);
#pragma endregion UI


	// Object추가 Player
	VObject* pObj = new VPlayer();
	pObj->SetName(L"Player");
	pObj->SetPos(Vector2(640.f, 384.f));
	pObj->SetScale(Vector2(100.f, 100.f));

	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	//VCamera::GetInst()->SetTarget(pObj);


	// 몬스터 배치
	//Vector2 vResolution = VCore::GetInst()->GetResolution();
	/*
	VMonster* pMon = VMonFactory::CreateMonster(MON_TYPE::NOMAL, vResolution / 2.f - Vector2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);*/


	// 땅 물체 배치
	VObject* pGround = new VGround();
	pGround->SetName(L"Ground");
	pGround->SetPos(Vector2(640.f, 584.f));
	pGround->SetScale(Vector2(200.f, 60.f));
	AddObject(pGround, GROUP_TYPE::GROUND);

	// 타일 로딩
	//LoadTile(L"Tile\\Start.tile");


	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	VCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	VCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	VCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);


	// 카메라 LookAt지정	
	VCamera::GetInst()->SetLookAt(vResolution / 2.f);


	// 카메라 효과 지정 
	VCamera::GetInst()->FadeOut(0.5f);
	VCamera::GetInst()->FadeIn(0.5f);

	//Start();
}

void VScene_Start::SceneExit()
{
	DeleteAll();

	VCollisionManager::GetInst()->Reset();
}

void VScene_Start::CreateForce()
{
	m_vForcePos = VCamera::GetInst()->GetRenderToWorldPos(MOUSE_POS);


}


