#pragma once
#include "VObject.h"


enum class PLAYER_STATE
{
	IDLE,
	WALK,
	ATTACK,
	JUMP,
	DEAD,
};

enum class PLAYER_ATTACK_STATE
{
	NOMAL_ATT_1,
	NOMAL_ATT_2,
	NOMAL_ATT_3,

	SKILL_ATT_1,

};



class VTexture;

class VPlayer : public VObject
{
private:

	int m_iDir;
	int m_iPrevDir;
	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;


public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();

	virtual void Render(HDC _dc);

	virtual void OnCollisionEnter(VCollider* _pOther);


public:	
	CLONE(VPlayer);


private:
	void CreateBullet();
	void Update_State();
	void Update_Move();
	void Update_Animation();
		
public:
	VPlayer();	
	virtual ~VPlayer();
};

