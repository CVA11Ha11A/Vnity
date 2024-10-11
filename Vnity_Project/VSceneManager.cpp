#include "pch.h"
#include "VSceneManager.h"


#include "VScene_Start.h"
#include "VScene_Tool.h"


VSceneManager::VSceneManager()
	:m_pCurScene(nullptr), m_arrScene{}
{

}

VSceneManager::~VSceneManager()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)E_SCENE_TYPE::END; i++)
	{
		if (m_arrScene[i] != nullptr)
		{
			delete m_arrScene[i];
		}
	}
}

void VSceneManager::Init()
{
	// 모든 Scene 생성
	m_arrScene[(UINT)E_SCENE_TYPE::START] = new VScene_Start;
	m_arrScene[(UINT)E_SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)E_SCENE_TYPE::TOOL] = new VScene_Tool;
	m_arrScene[(UINT)E_SCENE_TYPE::START]->SetName(L"Tool Scene");

	//m_arrScene[(UINT)E_SCENE_TYPE::STAGE_01] = new VScene_Stage01;
	//m_arrScene[(UINT)E_SCENE_TYPE::STAGE_02] = new VScene_Stage02;

	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)E_SCENE_TYPE::START];
	m_pCurScene->SceneEnter();
}

void VSceneManager::Awake()
{
	m_pCurScene->Awake();
}

void VSceneManager::Start()
{
	m_pCurScene->Start();
}

void VSceneManager::Update()
{
	m_pCurScene->Update();

	m_pCurScene->FinalUpdate();

}

void VSceneManager::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);

}

void VSceneManager::ChangeScene(E_SCENE_TYPE _eNext)
{	
	m_pCurScene->SceneExit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->SceneEnter();
}

