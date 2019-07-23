#include "DXUT.h"
#include "Matt.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

Matt::Matt()
{
}

Matt::Matt(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Matt::~Matt()
{
}

void Matt::Create()
{
	SetRect(0, MATT_WIDTH, 0, MATT_HEIGHT);

	fHp = 1.0f;
	fSpeed = 5.0f;

	bHitAni = false;
	fHitTime = 0.0f;
	bDie = false;

	bVisible = false;

	fAniMoveTime = 0.0f;
	nMoveCount = 0;
	nCurrentMove = 0;

	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::BOMB_EFFECT1), 270, 230, 6, 1);

	SetAniRect();

	ZeroMemory(&vDirect, sizeof(vDirect));
}

void Matt::Update(Player* pPlayer)
{
	SetCollision(25, 45, 30, 40);
	SetCenterPos(vPosition.x + 44, vPosition.y + 48, 0);

	if (bVisible)
	{
		Move();
		pBombEffect->SetPosition(vPosition.x - 75, vPosition.y - 65, 0);
		AniMove();
	}
	if (fHp <= 0 && !bDie)
	{
		bDie = true;
		bVisible = false;
		OBJMANAGER()->SetScore(OBJMANAGER()->GetScore() + 50);
	}
	if (bDie)
	{
		SOUNDMANAGER()->pBomb3->Play(0, NULL);
		pBombEffect->SetVisible(true);
		pBombEffect->Animation(0.1f, 6, false);
		if (pBombEffect->GetFinish())
		{
			pBombEffect->SetFinish(false);
			bDie = false;
			fHp = 1.0f;
		}
	}
	HitSystem(pPlayer);
}

void Matt::Move()
{
	vPosition.x += vDirect.x * fSpeed;
	vPosition.y += vDirect.y * fSpeed;
}

void Matt::Aim(Player* pPlayer)
{
	vDirect.x = pPlayer->GetCenterPos()->x - vPosition.x;
	vDirect.y = pPlayer->GetCenterPos()->y - vPosition.y;
	vDirect.z = 0.0f;

	D3DXVec3Normalize(&vDirect, &vDirect);
}

void Matt::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[nMoveCount].left = i * MATT_WIDTH;
		rtMove[nMoveCount].right = rtMove[nMoveCount].left + MATT_WIDTH;
		rtMove[nMoveCount].top = 0;
		rtMove[nMoveCount].bottom = MATT_HEIGHT;
		nMoveCount++;
	}
}

void Matt::AniMove()
{
	if (GATIMER()->GetTimer() - fAniMoveTime > 0.1f)
	{
		SetRect(rtMove[nMoveCount++]);

		fAniMoveTime = GATIMER()->GetTimer();
	}
	if (nMoveCount >= ANI_MOVE)
	{
		nMoveCount = 0;
	}
}