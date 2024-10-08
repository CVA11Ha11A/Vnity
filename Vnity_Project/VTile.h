#pragma once
#include "VObject.h"

class VTexture;


class VTile : public VObject
{	// �ش� ��ü�� �����Ǵ� �»���� �ش� ������Ʈ�� ��ġ


private:
	VTexture*	m_pTileTex;	// Ÿ�� �ؽ����� ������
	int			m_iImgIdx;		// -1�� ��� �ƹ��͵� �������� ����

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

