#include "pch.h"
#include "VMonster.h"

#include "VAI.h"

#include "VTimeManager.h"
#include "VCollider.h"

void VMonster::Awake()
{
}

void VMonster::Start()
{
}

void VMonster::Update()
{
	if (m_pAI != nullptr)
	{
		m_pAI->Update();
	}

}




inline void VMonster::SetAI(VAI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}

void VMonster::OnCollisionEnter(VCollider* _pOther)
{
	VObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Missle_Player")
	{

	}


}

VMonster::VMonster()
	:m_tInfo{}
	, m_pAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(45.f, 45.f));
}

VMonster::~VMonster()
{
	if (m_pAI != nullptr)
	{
		delete m_pAI;
	}
}


