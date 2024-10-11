#include "pch.h"
#include "VPlayer.h"

#include "VKeyManager.h"
#include "VTimeManager.h"
#include "VSceneManager.h"
#include "VPathManager.h"
#include "VResourceManager.h"

#include "VScene.h"
#include "VBullet.h"
#include "VTexture.h"

#include "VCollider.h"
#include "VAnimator.h"
#include "VAnimation.h"
#include "VRigidBody.h"


VPlayer::VPlayer()
	:m_iDir(1)
	, m_iPrevDir(1)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::IDLE)
{
	SetObjGroup(GROUP_TYPE::PLAYER);
	// Texture 로딩하기
	//m_pTex = VResourceManager::GetInst()->LoadTexture(L"PlayerTex", L"Texture\\Player.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2(0.f, 12.f));
	GetCollider()->SetScale(Vector2(20.f, 40.f));

	CreateRigidBody();


	VTexture* m_pTex = VResourceManager::GetInst()->LoadTexture(L"PlayerTex", L"Texture\\link_Anime.bmp");

	CreateAnimator();

	//GetAnimator()->LoadAnimation(L"Animation\\Player_Wake_Down.anim");
	//GetAnimator()->LoadAnimation(L"Animation\\Player_Wake_Down001.anim");
	GetAnimator()->CreateAnimation(L"WALK_DOWN", m_pTex, Vector2(0.f, 520.f),
		Vector2(120.f, 130.f), Vector2(120.f, 0.f), 0.1f, 10);

	GetAnimator()->Play(L"WALK_DOWN", true);

	// Animation 저장해보기
	 GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"Animation\\Player_Wake_Down.anim");
	 GetAnimator()->FindAnimation(L"WALK_DOWN")->Save1ByteVer(L"Animation\\Player_Wake_Down001.anim");



	VAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -20.f);
	}



}		// ctor()

VPlayer::~VPlayer()
{

}



void VPlayer::Awake()
{
}

void VPlayer::Start()
{
	DonDestroy();

}

void VPlayer::Update()
{
	Update_Move();

	Update_State();

	//	Update_Animation(); // 현재 리소스가 알맞지않아서 주석 24.10.05

	/*if (KEY_ENTER(KEY::E) == true)
	{
		int a = 1;
		CreateBullet();
		assert(true);
	}*/
	if (KEY_ENTER(KEY::ENTER))
	{
		SetPos(Vector2(GetPos().x, 0.f));
	}

	GetAnimator()->Update();


	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;

}		// Update()

void VPlayer::Render(HDC _dc)
{
	// 컴포넌트(충돌체, etc...가 존재할경우 렌더)
	VObject::Component_Render(_dc);

}

void VPlayer::OnCollisionEnter(VCollider* _pOther)
{
	VObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground")
	{
		Vector2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}

}



void VPlayer::CreateBullet()
{
	VBullet* pBullet = new VBullet();

	Vector2 spawnPos = GetPos();
	pBullet->SetScale(Vector2(25.f, 25.f));
	pBullet->SetPos(spawnPos);
	pBullet->SetDir(Vector2(-2.f, -2.f));
	pBullet->SetName(L"Missle_Player");

	CreateObject(pBullet, GROUP_TYPE::PROJ_PLAYER);

}

void VPlayer::Update_State()
{

	if (KEY_HOLD(KEY::A) == true)
	{
		m_iDir = -1;
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_HOLD(KEY::D) == true)
	{
		m_iDir = 1;
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (GetRigidBody()->GetSpeed() == 0.f && m_eCurState != PLAYER_STATE::JUMP)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_ENTER(KEY::Z))
	{
		m_eCurState = PLAYER_STATE::JUMP;
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vector2(GetRigidBody()->GetVelocity().x, -300.f));
		}

	}

}		// Update_State()

void VPlayer::Update_Move()
{
	VRigidBody* pRigid = GetRigidBody();


	if (KEY_ENTER(KEY::A) == true)
	{

		pRigid->SetVelocity(Vector2(-100.f, pRigid->GetVelocity().y));
	}

	if (KEY_ENTER(KEY::D) == true)
	{
		pRigid->SetVelocity(Vector2(100.f, pRigid->GetVelocity().y));
	}


	if (KEY_HOLD(KEY::A) == true)
	{
		pRigid->AddForce(Vector2(-200.f, 0.f));
	}

	if (KEY_HOLD(KEY::D) == true)
	{
		pRigid->AddForce(Vector2(200.f, 0.f));
	}
}		// Update_Move()

void VPlayer::Update_Animation()
{
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
	{
		return;
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)
		{
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		}
		else
		{
			GetAnimator()->Play(L"IDLE_LEFT", true);
		}
	}
	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
		{
			GetAnimator()->Play(L"WALK_RIGHT", true);
		}
		else
		{
			GetAnimator()->Play(L"WALK_LEFT", true);
		}
	}
	break;
	case PLAYER_STATE::JUMP:

		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	}

}		// Update_Animation()


