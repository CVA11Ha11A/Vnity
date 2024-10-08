#include "pch.h"
#include "VAI.h"

#include "VState.h"


VAI::VAI()
	:m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

VAI::~VAI()
{
	Safe_Delete_Map(m_mapState);
}


void VAI::Update()
{
	m_pCurState->Update();
}

void VAI::AddState(VState* _pState)
{
	VState* pState = GetState(_pState->GetType());
	assert(!pState);

	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
	
}

VState* VAI::GetState(MON_STATE _eState)
{
	map<MON_STATE, VState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void VAI::SetCurState(MON_STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);	
}

void VAI::ChangeState(MON_STATE _eNextState)
{
	VState* pNextState = GetState(_eNextState);

	assert(m_pCurState != pNextState);
	m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}	// ChangeState()


