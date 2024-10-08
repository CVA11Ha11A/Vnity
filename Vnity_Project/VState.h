#pragma once

class VAI;
class VMonster;

class VState
{
private:
	VAI*		m_pAI;
	MON_STATE	m_eState;

public:
	VAI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }
	VMonster* GetMonster();


public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	VState(MON_STATE _eState);
	virtual ~VState();


	friend class VAI;
};

