#pragma once
#include "VGlobal.h"

#include "VMonFactory.h"


// 전방선언
class VObject;

class VScene
{



private:
	// m_arrObj[arrindex][vectorIndex]
	vector<VObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// 오브젝트 저장 및 관리할 백터를 그룹 개수만큼 선언 	

	vector<VObject*>	m_vAwakeObjList;						// Awake단계를 돌아야하는 객체를 담아두는 자료구조
	vector<VObject*>	m_vStartObjList;						// Start단계를 돌아야하는 객체를 담아두는 자료구조

	wstring				m_strName;	// Scene 이름

	UINT				m_iTileX;	// 타일의 가로 갯수
	UINT				m_iTileY;	// 타일의 세로 갯수


	VObject*			m_pPlayer;	// 플레이어 오브젝트 포인터

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();		// 오브젝트 조작 업데이트
	virtual void FinalUpdate();	// 작업 마무리 업데이트 (ex : 충돌체 오브젝트 위치로 이동)
	virtual void Render(HDC _dc);
	void Render_Tile(HDC _dc);

	virtual void SceneEnter() = 0;		// 씬 진입시 호출
	virtual void SceneExit() = 0;		// 씬 퇴장시 호출


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	VObject* GetPlayer() { return m_pPlayer; }

	
public:
	const vector<VObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void AddObject(VObject* _pObj, GROUP_TYPE _eType);
	void RegisterPlayer(VObject* _pPlayer) { m_pPlayer = _pPlayer; }

	void CreateTile(UINT _iXCount, UINT _iYCount);

	void LoadTile(const wstring& _strRelativePath);
	void LoadTileData();

	vector<VObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }


public:
	VScene();
	virtual ~VScene();

};

