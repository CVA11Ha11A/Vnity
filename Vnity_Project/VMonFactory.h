#pragma once

class VMonster;

enum class MON_TYPE
{
	NOMAL,
	RANGE,

};

class VMonFactory
{

public:
	static VMonster* CreateMonster(MON_TYPE _eType, Vector2 _vPos);








private:
	VMonFactory() {};
	~VMonFactory() {};


};

