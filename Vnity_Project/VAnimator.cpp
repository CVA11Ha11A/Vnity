#include "pch.h"
#include "VAnimator.h"

#include "VAnimation.h"
#include "VObject.h"

VAnimator::VAnimator()
	:m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bIsLoop(false)
{

}


VAnimator::~VAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}


void VAnimator::Update()
{

}

void VAnimator::FinalUpdate()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->Update();

		if (m_bIsLoop == true && m_pCurAnim->IsFinish() == true)
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void VAnimator::Render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->Render(_dc);
	}

}


void VAnimator::CreateAnimation(const wstring& _strName, VTexture* _pTex, Vector2 _vLT,
	Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount)
{
	VAnimation* pAnim = FindAnimation(_strName);	

	if (pAnim == nullptr)
	{
		pAnim = new VAnimation;
	}


	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}		// CreateAnimation()

void VAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	VAnimation* pAnim = new VAnimation();
	//pAnim->Load(_strRelativePath);
	pAnim->Load1ByteVer(_strRelativePath);

	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}		// LoadAnimation()

VAnimation* VAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, VAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}


void VAnimator::Play(const wstring& _strName, bool _bIsLoop)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bIsLoop = _bIsLoop;
}

