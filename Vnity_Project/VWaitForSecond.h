#pragma once
#include "VCoroutine.h"



class VWaitForSecond : public VCoroutine
{

private:
	float m_fDurationTime;		// 객체가 생성된후 지나간 시간


public:
	virtual bool Execute();



public:	
	VWaitForSecond(float _duration);
	~VWaitForSecond();

private:	

};

