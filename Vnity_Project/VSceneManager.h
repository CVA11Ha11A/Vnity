#pragma once

class VScene;


class VSceneManager
{
	SINGLETON(VSceneManager);

private:
	VScene*		m_arrScene[(UINT)E_SCENE_TYPE::END];	// °ÔÀÓ³» ¸ðµç ¾À
	VScene*		m_pCurScene;			// ÇöÀç ¾À


public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	VScene* GetCurScene() { return m_pCurScene; }
	VScene* GetScene(E_SCENE_TYPE _targetScene) { return m_arrScene[(UINT)_targetScene]; }

private:
	void ChangeScene(E_SCENE_TYPE _eNext);
	friend class VEventManager;

};

