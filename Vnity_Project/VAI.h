#pragma once

class VMonster;
class VState;

class VAI
{

private:
	map<MON_STATE, VState*>	m_mapState;
	VMonster*				m_pOwner;
	VState*					m_pCurState;

public:
	void Update();	


public:
	void AddState(VState* _pState);
	VState* GetState(MON_STATE _eState);
	void SetCurState(MON_STATE _eState);

	void ChangeState(MON_STATE _eNextState);

	VMonster* GetOwner() { return m_pOwner; }

public:
	VAI();
	~VAI();

	friend class VMonster;
};


