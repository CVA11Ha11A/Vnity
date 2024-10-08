#pragma once
#include "VGlobal.h"

class VAnimator;
class VTexture;

struct tAnimFrm
{
	Vector2 vLT;		// �ڽ� �������ؽ����� �»��
	Vector2 vSlice;		// �ڸ� ������ ����
	Vector2 vOffset;	// �ش� �������� offset
	float	fDuration;	// �ִϸ��̼� ��� �ð�

};


class VAnimation
{


private:
	wstring				m_strName;
	VAnimator*			m_pAnimator;
	VTexture*			m_pTex;		// Animation�� ����ϴ� TexturePointer
	vector<tAnimFrm>	m_vecFrm;	// ��� ������ ����
	int					m_iCurFrm;	// ���� ������
	float				m_fAccTime;	// �ð��� ������ ����

	bool				m_bFinish;	// ��� ���� ���޿���

public:

	const wstring& GetName() { return this->m_strName; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_fAccTime = 0.f;
		if (m_vecFrm.size() < _iFrameIdx)
		{	
			_iFrameIdx = (int)m_vecFrm.size();
		}
		m_iCurFrm = _iFrameIdx;
	}
	bool IsFinish() { return m_bFinish; }
	tAnimFrm& GetFrame(int _iIdx) {	return m_vecFrm[_iIdx];	}
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { this->m_strName = _strName; }	


public:
	void Update();
	void Render(HDC _dc);
	void Create(VTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize
		, Vector2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	void Save(const wstring& _strRelativePath);
	void Save1ByteVer(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);
	void Load1ByteVer(const wstring& _strRelativePath);


public:
	VAnimation();
	~VAnimation();

	friend class VAnimator;
};

