#pragma once

class VScene;


class VSceneManager
{
	SINGLETON(VSceneManager);

private:
	VScene*		m_arrScene[(UINT)E_SCENE_TYPE::END];	// 게임내 모든 씬
	VScene*		m_pCurScene;			// 현재 씬


public:
	void Init();

	// 사이클
	void Awake();
	void Start();
	void Update();

	void Render(HDC _dc);

public:
	VScene* GetCurScene() { return m_pCurScene; }
	VScene* GetScene(E_SCENE_TYPE _targetScene) { return m_arrScene[(UINT)_targetScene]; }

private:
	void ChangeScene(E_SCENE_TYPE _eNext);
	friend class VEventManager;

};

