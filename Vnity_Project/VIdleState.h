#pragma once
#include "VState.h"

class VIdleState : public VState
{

private:

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


public:
	VIdleState();
	~VIdleState();



};

