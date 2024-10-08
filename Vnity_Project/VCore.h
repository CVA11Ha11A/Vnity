#pragma once

class VTexture;

class VCore
{
	SINGLETON(VCore);

private:
	HWND	m_hWnd;				// 윈도우 메인 핸들
	POINT	m_ptResolution;		// 메인 윈도우 해상도
	HDC		m_hDC;				// 메인 윈도우에 Draw 할 DC

	VTexture* m_pMemTex;		// 백버퍼 텍스쳐(더블버퍼링에 사용)

	// 자주 사용하는 GDI Object (GDI : Grapic Divice InterfaceObject)
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// 메뉴
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




