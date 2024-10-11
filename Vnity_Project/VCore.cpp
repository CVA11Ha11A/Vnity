#include "pch.h"
#include "VCore.h"

#include "VTimeManager.h"
#include "VKeyManager.h"
#include "VSceneManager.h"
#include "VPathManager.h"
#include "VResourceManager.h"
#include "VCollisionManager.h"
#include "VEventManager.h"
#include "VUIManager.h"
#include "VSoundManager.h"

//CCore* CCore::g_pInst = nullptr;

#include "VObject.h"
#include "VTexture.h"
#include "VSound.h"
#include "SelectGDI.h"

#include "resource.h"

VCore::VCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
	, m_pMemTex(nullptr)
	, m_hMenu(nullptr)

{

}

VCore::~VCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	// DeleteDC(m_hDC);		// 메인으로 만든게 아닌 DC는 DeleteDC로 해제애햐함 (이유 모름 안나옴)	

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}



int VCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vector2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// 메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_VNITYPROJECT));

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	m_pMemTex = VResourceManager::GetInst()->CreateTexture(L"BackBuffer",
		(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	;

	// 자주 사용 할 펜 및 브러쉬 생성
	CreateBrushPen();


	// Manager Class 초기화
	VPathManager::GetInst()->Init();
	VTimeManager::GetInst()->Init();
	VKeyManager::GetInst()->Init();
	VCamera::GetInst()->Init();
	VSoundManager::GetInst()->Init();
	VSceneManager::GetInst()->Init();

	// Sound 로드 테스트
	VResourceManager::GetInst()->LoadSound(L"BGM_01", L"Sound\\Title.wav");
	VSound* pNewSound = VResourceManager::GetInst()->FindSound(L"BGM_01");
	pNewSound->PlayToBGM(true);

	pNewSound->SetVolume(5.f);
	pNewSound->SetPosition(20.f);

	return S_OK;
}

void VCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

}

void VCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);;



	// red Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	// green Pen
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// blue Pen
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void VCore::DockMenu()
{
	// 툴 Scene에서 사용할 menu를 붙여준다.
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void VCore::DivideMenu()
{
	// 툴 Scene에서 사용할 menu를 땐다.
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void VCore::ChangeWindowSize(Vector2 _vResoulution, bool _bMenu)
{
	RECT rt = { 0,0, (LONG)_vResoulution.x,(LONG)_vResoulution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // 윈도우의 원하는 해상도 보내기
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0); // 해상도 설정

}





void VCore::Progress()
{
	// 그리기 

	// ==============
	// Manager Update
	// ==============
	VTimeManager::GetInst()->Update();
	VKeyManager::GetInst()->Update();
	VCamera::GetInst()->Update();

	// ==============
	// Scene Update
	// ==============
	// 여기서 Awake, Start 돌면 될거같은데 각씬마다 따로 자료구조에서 쳐내야 할거같음(Object 생성자에서 자신의 생성을 알린후)
	// 오브젝트가 씬에 등록될 경우(AddObject) 오브젝트가 Start Awake가 돈적이 있는지확인후 처리 예정 자료구조에 추가
	// 그럼 오브젝트에 자신이 생성후 초기화 단계를 거쳤는지 확인해야겠네?
	VSceneManager::GetInst()->Awake();
	VSceneManager::GetInst()->Start();

	VSceneManager::GetInst()->Update();

	// 충돌체크
	VCollisionManager::GetInst()->Update();

	// UI 이벤트 체크
	VUIManager::GetInst()->Update();


	// ==============
	// Rendering	
	// ==============

	// 화면 Clear	
	Clear();

	VSceneManager::GetInst()->Render(m_pMemTex->GetDC());
	VCamera::GetInst()->Render(m_pMemTex->GetDC());

	// MDC에 그린것을 hDC로 옮겨 그림
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	VTimeManager::GetInst()->Render();


	// ==============
	// 이벤트 지연처리
	// ==============	
	VEventManager::GetInst()->Update();

}		// Progress()


