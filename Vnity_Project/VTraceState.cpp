#include "pch.h"
#include "VTraceState.h"

#include "VTimeManager.h"
#include "VSceneManager.h"
#include "VScene.h"
#include "VPlayer.h"
#include "VMonster.h"


VTraceState::VTraceState()
	:VState(MON_STATE::TRACE)
{
}

VTraceState::~VTraceState()
{
}


void VTraceState::Update()
{
	// 타겟팅 된 Player를 쫒아간다.
	VPlayer* pPlayer = (VPlayer*)VSceneManager::GetInst()->GetCurScene()->GetPlayer();
	Vector2 vPlayerPos = pPlayer->GetPos();

	Vector2 vMonPos = GetMonster()->GetPos();

	Vector2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().m_fSpeed* DeltaTime;

	GetMonster()->SetPos(vMonPos);

}

void VTraceState::Enter()
{
}

void VTraceState::Exit()
{
}

