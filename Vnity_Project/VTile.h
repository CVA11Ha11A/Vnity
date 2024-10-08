#pragma once
#include "VObject.h"

class VTexture;


class VTile : public VObject
{	// 해당 개체는 렌더되는 좌상단이 해당 오브젝트의 위치


private:
	VTexture*	m_pTileTex;	// 타일 텍스쳐의 포인터
	int			m_iImgIdx;		// -1일 경우 아무것도 참조하지 않음

public:
	void SetTexture(VTexture* _pTex) { m_pTileTex = _pTex; }

	void AddImgIdx() { ++m_iImgIdx; }

private:
	virtual void Awake();
	virtual void Start();
	virtual void Render(HDC _dc);
	virtual void Update();

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CLONE(VTile);


public:
	VTile();
	virtual ~VTile();

};

