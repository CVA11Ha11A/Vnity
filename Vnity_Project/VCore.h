#pragma once

class VTexture;

class VCore
{
	SINGLETON(VCore);

private:
	HWND	m_hWnd;				// ������ ���� �ڵ�
	POINT	m_ptResolution;		// ���� ������ �ػ�
	HDC		m_hDC;				// ���� �����쿡 Draw �� DC

	VTexture* m_pMemTex;		// ����� �ؽ���(������۸��� ���)

	// ���� ����ϴ� GDI Object (GDI : Grapic Divice InterfaceObject)
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU	m_hMenu;

public:
	int		Init(HWND _hWnd, POINT _ptResolution);	
	void	Progress();


private:
	void	Clear();
	void	CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vector2 _vResoulution, bool _bMenu);

public:
	HWND	GetMainHwnd() { return m_hWnd; }
	POINT	GetResolution() { return m_ptResolution; }
	HDC		GetMainDC() { return m_hDC; }
	HBRUSH	GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN	GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }	

};


#pragma region HeapInstance
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//
//public:
//	static CCore* GetInstance()
//	{
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore;
//		}
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (g_pInst != nullptr)
//		{
//			delete g_pInst;
//			g_pInst
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//
//
//};
#pragma endregion




