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
	// Ÿ���� �� Player�� �i�ư���.
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

