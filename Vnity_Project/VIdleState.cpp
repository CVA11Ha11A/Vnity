#include "pch.h"
#include "VIdleState.h"

#include "VSceneManager.h"

#include "VScene.h"
#include "VPlayer.h"
#include "VMonster.h"


VIdleState::VIdleState()
	:VState(MON_STATE::IDLE)
{
}

VIdleState::~VIdleState()
{
}


void VIdleState::Update()
{
	// 1.Player의 위치 체크
	VPlayer* pPlayer = (VPlayer*)VSceneManager::GetInst()->GetCurScene()->GetPlayer();
	Vector2 vPlayerPos = pPlayer->GetPos();

	// 2.몬스터의 범위 안에 들어오면 추적상태로 전환
	VMonster* pMonster = GetMonster();
	Vector2 vMonPos = pMonster->GetPos();

	Vector2 vDiff = vPlayerPos - vMonPos;
	float fLen = (float)vDiff.Length();

	if (fLen < pMonster->GetInfo().m_fAttRange)
	{	// if : 플레이어가 몬스터의 인식범위 안으로 진입
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}


}

void VIdleState::Enter()
{
}

void VIdleState::Exit()
{
}
