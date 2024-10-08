#pragma once
#include "VState.h"


class VTraceState : public VState
{
private:

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


public:
	VTraceState();
	~VTraceState();


};

