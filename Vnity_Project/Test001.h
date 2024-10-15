#pragma once
#include "VObject.h"


class Test001 : public VObject
{
public:
	CLONE(Test001);

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render(HDC _dc);

private:




public:
	void CoroutineTest();



public:
	Test001();
	~Test001();



};

