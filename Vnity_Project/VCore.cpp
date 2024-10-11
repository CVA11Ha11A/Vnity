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

	// DeleteDC(m_hDC);		// �������� ����� �ƴ� DC�� DeleteDC�� ���������� (���� �� �ȳ���)	

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

	// �ػ󵵿� �°� ������ ũ�� ����
	ChangeWindowSize(Vector2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// �޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_VNITYPROJECT));

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� �ؽ��� ������ �����.
	m_pMemTex = VResourceManager::GetInst()->CreateTexture(L"BackBuffer",
		(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	;

	// ���� ��� �� �� �� �귯�� ����
	CreateBrushPen();


	// Manager Class �ʱ�ȭ
	VPathManager::GetInst()->Init();
	VTimeManager::GetInst()->Init();
	VKeyManager::GetInst()->Init();
	VCamera::GetInst()->Init();
	VSoundManager::GetInst()->Init();
	VSceneManager::GetInst()->Init();

	// Sound �ε� �׽�Ʈ
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
	// �� Scene���� ����� menu�� �ٿ��ش�.
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void VCore::DivideMenu()
{
	// �� Scene���� ����� menu�� ����.
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void VCore::ChangeWindowSize(Vector2 _vResoulution, bool _bMenu)
{
	RECT rt = { 0,0, (LONG)_vResoulution.x,(LONG)_vResoulution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // �������� ���ϴ� �ػ� ������
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0); // �ػ� ����

}





void VCore::Progress()
{
	// �׸��� 

	// ==============
	// Manager Update
	// ==============
	VTimeManager::GetInst()->Update();
	VKeyManager::GetInst()->Update();
	VCamera::GetInst()->Update();

	// ==============
	// Scene Update
	// ==============
	// ���⼭ Awake, Start ���� �ɰŰ����� �������� ���� �ڷᱸ������ �ĳ��� �ҰŰ���(Object �����ڿ��� �ڽ��� ������ �˸���)
	// ������Ʈ�� ���� ��ϵ� ���(AddObject) ������Ʈ�� Start Awake�� ������ �ִ���Ȯ���� ó�� ���� �ڷᱸ���� �߰�
	// �׷� ������Ʈ�� �ڽ��� ������ �ʱ�ȭ �ܰ踦 ���ƴ��� Ȯ���ؾ߰ڳ�?
	VSceneManager::GetInst()->Awake();
	VSceneManager::GetInst()->Start();

	VSceneManager::GetInst()->Update();

	// �浹üũ
	VCollisionManager::GetInst()->Update();

	// UI �̺�Ʈ üũ
	VUIManager::GetInst()->Update();


	// ==============
	// Rendering	
	// ==============

	// ȭ�� Clear	
	Clear();

	VSceneManager::GetInst()->Render(m_pMemTex->GetDC());
	VCamera::GetInst()->Render(m_pMemTex->GetDC());

	// MDC�� �׸����� hDC�� �Ű� �׸�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	VTimeManager::GetInst()->Render();


	// ==============
	// �̺�Ʈ ����ó��
	// ==============	
	VEventManager::GetInst()->Update();

}		// Progress()


