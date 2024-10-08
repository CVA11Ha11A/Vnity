#pragma once
#include "VObject.h"

class VCollider;


class VGround :  public VObject
{

private:
	


public:	
	virtual void Awake();
	virtual void Start();
	virtual void Update();

	virtual void OnCollisionEnter(VCollider* _pOther);
	virtual void OnCollisionStay(VCollider* _pOther);
	virtual void OnCollisionExit(VCollider* _pOther);


	CLONE(VGround);
public:
	VGround();
	~VGround();
};

