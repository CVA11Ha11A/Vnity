#include "pch.h"
#include "VCamera.h"

#include "VCore.h"

#include "VKeyManager.h"
#include "VTimeManager.h"
#include "VResourceManager.h"

#include "VObject.h"
#include "VTexture.h"

VCamera::VCamera()
	:m_pTargetObj(nullptr)
	, m_pVeilTex(nullptr)	
	, m_fAccTime(0.5f)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)	
{

}

VCamera::~VCamera()
{

}


void VCamera::Init()
{
	Vector2 vResolution = VCore::GetInst()->GetResolution();

	m_pVeilTex = VResourceManager::GetInst()->CreateTexture(L"CameraVeil",
		(UINT)vResolution.x, (UINT)vResolution.y);


}

void VCamera::Update()
{
	if (m_pTargetObj != nullptr)
	{
		if (m_pTargetObj->IsDead() == true)
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * (float)DeltaTime;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * (float)DeltaTime;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * (float)DeltaTime;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * (float)DeltaTime;


	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();


}	// Update()

void VCamera::Render(HDC _dc)
{
	if (m_listCamEffect.empty())
	{
		return;
	}
	
	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += DeltaTime;

	float fRatio = 0.f; // 이펙트 진행 비율	
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
	{
		fRatio = 0.f;
	}
	if (1.f < fRatio)
	{
		fRatio = 1.f;
	}

	int iAlpha = 0;	

	if (effect.eEffect == CAM_EFFECT::FADE_OUT)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (effect.eEffect == CAM_EFFECT::FADE_IN)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	// 알파 블렌드
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->GetWidth()
		, (int)m_pVeilTex->GetHeight()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->GetWidth()
		, (int)m_pVeilTex->GetHeight()
		, bf);

	if (effect.fDuration < effect.fCurTime)
	{	// if : 효과가 종료 되었을경우 진입
		m_listCamEffect.pop_front();		
	}



}		// Render()

void VCamera::CalDiff()
{
	// 이전 LookAt 과 현재 LookAt 의 차이값을 보정해서 현재의 LookAt을 구한다.
	m_fAccTime += (float)DeltaTime;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vector2 vLookDir = m_vLookAt - m_vPrevLookAt;	// 이동할 방향 계산

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * DeltaTime;
		}

	}

	Vector2 vResolution = VCore::GetInst()->GetResolution();
	Vector2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;

}		// CalDiff()
