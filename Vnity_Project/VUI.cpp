#include "VUI.h"

#include "VKeyManager.h"
#include "VCamera.h"

#include "SelectGDI.h"


VUI::VUI(bool _bCamAffected)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
}

VUI::VUI(const VUI& _origin)
	: VObject(_origin)
	,m_pParentUI(nullptr)
	,m_bCamAffected(_origin.m_bCamAffected)
	,m_bMouseOn(false)
	,m_bLbtnDown(false)	
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}

}

VUI::~VUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}


void VUI::Awake()
{
}

void VUI::Start()
{
}

void VUI::Update()
{

	// ChildUI Update는 부모의 Update가 끝난후에 실행
	Update_Child();
}

void VUI::FinalUpdate()
{
	VObject::FinalUpdate();

	// UI의 최종 좌표를 구한다.
	m_vFinalPos = GetPos();

	if (GetParent())
	{	// if : 자신이 어떤 UI의 자식오브젝트라면 Final포지션을 상대위치로 변경
		Vector2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	// UI Mouse 체크
	MouseOnCheck();



	FinalUpdate_Child();
}

void VUI::Render(HDC _dc)
{
	Vector2 vPos = GetFinalPos();
	Vector2 vScale = GetScale();

	if (m_bCamAffected == true)
	{
		vPos = VCamera::GetInst()->GetWorldToRenderPos(vPos);
	}

	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

		
	Render_Child(_dc);

}

void VUI::Update_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Update();
	}
}

void VUI::FinalUpdate_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->FinalUpdate();
	}
}

void VUI::Render_Child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
}

void VUI::MouseOnCheck()
{
	Vector2 vMousePos = MOUSE_POS;
	Vector2 vScale = GetScale();

	if (m_bCamAffected == true)
	{
		vMousePos = VCamera::GetInst()->GetRenderToWorldPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

}		 // MouseOnCheck()


void VUI::MouseOn()
{

}

void VUI::MouseLbtnDown()
{

}

void VUI::MouseLbtnUp()
{


}

void VUI::MouseLbtnClicked()
{


}

