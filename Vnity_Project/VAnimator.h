#pragma once


class VObject;
class VAnimation;
class VTexture;

class VAnimator
{	// �ִϸ��̼��� �������� ��ü

private:
	map<wstring, VAnimation*>	m_mapAnim;		// �ִϸ��̼��� ��Ƶ� Map
	VAnimation*					m_pCurAnim;		// ���� ������� Animation
	VObject*					m_pOwner;		// �ش� ������Ʈ�� ������ �ִ� ��ü�� ������
	bool						m_bIsLoop;		// �ִϸ��̼��� �ݺ���� �� ������

public:
	VObject* GetObj() 	{ return m_pOwner; }

public:
	/// <summary>
	/// �ִϸ��̼� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_strName"> : ������ �ִϸ��̼� �̸�</param>
	/// <param name="_pTex"> : ����� �ؽ���</param>
	/// <param name="_vLT"> : �ִϸ��̼ǿ� ����� �ؽ����� �»��(������ ����)</param>
	/// <param name="_SliceSize"> : ��ŭ�ڸ�������</param>
	/// <param name="_vStep"> : ��ŭ�� ������ ������ϴ���</param>
	/// <param name="_iFrameCount"> : �� frame����</param>
	void CreateAnimation(const wstring& _strName, VTexture* _pTex , Vector2 _vLT,
		Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount);
	void LoadAnimation(const wstring& _strRelativePath);
	VAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bIsLoop);


	void Update();
	void FinalUpdate();
	void Render(HDC _dc);



public:
	VAnimator();
	~VAnimator();

	friend class VObject;	

};

