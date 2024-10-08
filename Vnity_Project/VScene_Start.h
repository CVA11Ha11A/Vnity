#pragma once
#include "VScene.h"


class VScene_Start final : public VScene
{

private:
	Vector2		m_vForcePos;
	float		m_fForceRadius;
	float		m_fCurRadius;
	float		m_fForce;
	bool		m_bUseForce;

public:
	virtual void Update();
	virtual void Render(HDC _dc); 

	virtual void SceneEnter();
	virtual void SceneExit();


public:
	void CreateForce();
	

public:
	VScene_Start();
	~VScene_Start();

};

