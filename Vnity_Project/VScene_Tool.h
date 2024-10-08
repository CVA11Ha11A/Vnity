#pragma once
#include "VScene.h"


class VUI;

class VScene_Tool : public VScene
{

private:
	VUI* m_pUI;

public:
	virtual void SceneEnter();
	virtual void SceneExit();
	virtual void Update();


public:
	void SetTileIdx();

	void SaveTileData();
	void SaveTile(const wstring& _strFilePath);

public:
	VScene_Tool();
	~VScene_Tool();

};

