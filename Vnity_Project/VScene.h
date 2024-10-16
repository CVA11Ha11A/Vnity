#pragma once
#include "VGlobal.h"

#include "VMonFactory.h"


// ���漱��
class VObject;

class VScene
{



private:
	// m_arrObj[arrindex][vectorIndex]
	vector<VObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// ������Ʈ ���� �� ������ ���͸� �׷� ������ŭ ���� 	

	vector<VObject*>	m_vAwakeObjList;						// Awake�ܰ踦 ���ƾ��ϴ� ��ü�� ��Ƶδ� �ڷᱸ��
	vector<VObject*>	m_vStartObjList;						// Start�ܰ踦 ���ƾ��ϴ� ��ü�� ��Ƶδ� �ڷᱸ��

	wstring				m_strName;	// Scene �̸�

	UINT				m_iTileX;	// Ÿ���� ���� ����
	UINT				m_iTileY;	// Ÿ���� ���� ����


	VObject*			m_pPlayer;	// �÷��̾� ������Ʈ ������

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();		// ������Ʈ ���� ������Ʈ
	virtual void FinalUpdate();	// �۾� ������ ������Ʈ (ex : �浹ü ������Ʈ ��ġ�� �̵�)
	virtual void Render(HDC _dc);
	void Render_Tile(HDC _dc);

	virtual void SceneEnter() = 0;		// �� ���Խ� ȣ��
	virtual void SceneExit() = 0;		// �� ����� ȣ��


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

