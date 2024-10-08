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
	// 1.Player�� ��ġ üũ
	VPlayer* pPlayer = (VPlayer*)VSceneManager::GetInst()->GetCurScene()->GetPlayer();
	Vector2 vPlayerPos = pPlayer->GetPos();

	// 2.������ ���� �ȿ� ������ �������·� ��ȯ
	VMonster* pMonster = GetMonster();
	Vector2 vMonPos = pMonster->GetPos();

	Vector2 vDiff = vPlayerPos - vMonPos;
	float fLen = (float)vDiff.Length();

	if (fLen < pMonster->GetInfo().m_fAttRange)
	{	// if : �÷��̾ ������ �νĹ��� ������ ����
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}


}

void VIdleState::Enter()
{
}

void VIdleState::Exit()
{
}
