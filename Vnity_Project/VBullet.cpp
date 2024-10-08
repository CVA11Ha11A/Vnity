#include "pch.h"
#include "VBullet.h"

#include "VTimeManager.h"

#include "VCollider.h"


VBullet::VBullet()
	:m_fTheta(PI / 2.f), m_vDir(Vector2(1,1))
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vector2(15.f,15.f));
}

VBullet::~VBullet()
{
}


void VBullet::SetDir(Vector2 _vDir)
{
	m_vDir = _vDir;
	m_vDir.Normalize();
}

void VBullet::Awake()
{
}

void VBullet::Start()
{
}

void VBullet::Update()
{
	Vector2 vPos = GetPos();

	vPos.x += 600.f * m_vDir.x * DeltaTime;
	vPos.y += 600.f * m_vDir.y * DeltaTime;

	SetPos(vPos);
}

void VBullet::Render(HDC _dc)
{
	Vector2 objPos = GetPos();
	Vector2 objScale = GetScale();
	Ellipse(_dc, (int)objPos.x - (int)objScale.x / 2, (int)objPos.y - (int)objScale.y / 2,
		(int)objPos.x + (int)objScale.x / 2, (int)objPos.y + (int)objScale.y / 2);

	Component_Render(_dc);
}

void VBullet::OnCollisionEnter(VCollider* _col)
{
	VObject* colObj = _col->GetObj();
	if (colObj->GetName() == L"MonsterObj")
	{
		Destroy(this);
	}
}


