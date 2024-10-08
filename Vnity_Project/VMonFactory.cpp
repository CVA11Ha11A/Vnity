#include "pch.h"
#include "VMonFactory.h"

#include "VMonster.h"
#include "VAI.h"
#include "VRigidBody.h"

#include "VIdleState.h"
#include "VTraceState.h"


VMonster* VMonFactory::CreateMonster(MON_TYPE _eType , Vector2 _vPos)
{
	VMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NOMAL:
	{
		pMon = new VMonster();
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.m_fAtt = 10.f;
		info.m_fAttRange = 50.f;
		info.m_fRecogRange = 300.f;
		info.m_fHP = 100.f;
		info.m_fSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		VAI* pAI = new VAI();
		pAI->AddState(new VIdleState());
		pAI->AddState(new VTraceState());
		pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetAI(pAI);
		break;
	}
		
	case MON_TYPE::RANGE:

		break;	
	}		// switch

	assert(pMon);

	return pMon;
}
