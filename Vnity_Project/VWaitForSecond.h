#pragma once
#include "VCoroutine.h"



class VWaitForSecond : public VCoroutine
{

private:
	float m_fDurationTime;		// ��ü�� �������� ������ �ð�


public:
	virtual bool Execute();



public:	
	VWaitForSecond(float _duration);
	~VWaitForSecond();

private:	

};

