#pragma once

#include "VObject.h"


class VBullet : public VObject
{

private:
	float		m_fTheta; // 미사일의 각도

	Vector2		m_vDir;

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vector2 _vDir);

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void OnCollisionEnter(VCollider* _col);

	virtual VBullet* Clone() { return new VBullet(*this); }

public:
	VBullet();
	virtual ~VBullet();
	
};

