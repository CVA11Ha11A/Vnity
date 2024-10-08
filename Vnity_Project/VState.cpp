#include "pch.h"
#include "VState.h"

#include "VMonster.h"
#include "VAI.h"




VState::VState(MON_STATE _eState)
	:m_eState(_eState)
	,m_pAI(nullptr)
{
}

VState::~VState()
{
}

VMonster* VState::GetMonster()
{	
	return m_pAI->GetOwner();
}
