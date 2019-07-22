#include "DXUT.h"
#include "Chris.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

Chris::Chris()
{
}

Chris::Chris(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Chris::~Chris()
{
}

void Chris::Create()
{
	SetRect(0, CHRIS_WIDTH, 0, CHRIS_HEIGHT);

	fHp = 15.0f;
	fSpeed = 3.0f;

	bHitAni = false;
	fHitTime = 0.0f;
	bDie = false;

	fBulletTime = 0.0f;
	nBulletCount = 0;

	fAniMoveTime = 0.0f;
	nMoveCount = 0;
	nCurrentMove = 0;

	bVisible = false;

	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::BOMB_EFFECT2), 200, 150, 6, 1);

	CreateBullet();
	SetAniRect();
}

void Chris::Update(Player* pPlayer)
{
	SetCollision(39, 93, 14, 64);
	SetCenterPos(vPosition.x + 62, vPosition.y + 44, 0);

	if (bVisible)
	{
		if (vPosition.x > 400)
		{
			Shot(pPlayer);
		}
		StraightMove();
		AniMove();
		pBombEffect->SetPosition(vPosition.x - 20, vPosition.y - 30, 0);
	}
	if (fHp <= 0 && !bDie)
	{
		bDie = true;
		bVisible = false;
		OBJMANAGER()->SetScore(OBJMANAGER()->GetScore() + 100);
	}

	for (int i = 0; i < CHRIS_MAX_BULLET; i++)
	{
		pBullet[i]->SetCollision(0, 25, 0, 25);

		pBullet[i]->Shot();
	}
	if (bDie)
	{
		SOUNDMANAGER()->pBomb1->Play(0, NULL);
		pBombEffect->SetVisible(true);
		pBombEffect->Animation(0.1f, 6, false);
		if (pBombEffect->GetFinish())
		{
			pBombEffect->SetFinish(false);
			bDie = false;
			fHp = 10.0f;
		}
	}
	HitSystem(pPlayer);
}

void Chris::Shot(Player* pPlayer)
{
	D3DXVECTOR3 vDirect;

	if (GATIMER()->GetTimer() - fBulletTime > 2.0f)
	{
		pBullet[nBulletCount]->SetVisible(true);
		pBullet[nBulletCount]->SetPosition(vPosition.x + 32, vPosition.y + 43, 0);
		pBullet[nBulletCount]->SetSpeed(-8.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);

		pBullet[nBulletCount+1]->SetVisible(true);
		pBullet[nBulletCount+1]->SetPosition(vPosition.x + 32, vPosition.y + 43, 0);
		pBullet[nBulletCount+1]->SetSpeed(-8.0f);
		pBullet[nBulletCount+1]->SetAngle(0.1f);
		pBullet[nBulletCount+1]->SetShot(true);

		pBullet[nBulletCount+2]->SetVisible(true);
		pBullet[nBulletCount+2]->SetPosition(vPosition.x + 32, vPosition.y + 43, 0);
		pBullet[nBulletCount+2]->SetSpeed(-8.0f);
		pBullet[nBulletCount+2]->SetAngle(-0.1f);
		pBullet[nBulletCount+2]->SetShot(true);

		nBulletCount += 3;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= CHRIS_MAX_BULLET - 3)
	{
		nBulletCount = 0;
	}
}

void Chris::CreateBullet()
{
	for (int i = 0; i < CHRIS_MAX_BULLET; i++)
	{
		pBullet[i] = new Bullet(OBJMANAGER()->GetTexture(GaBase::CHRIS_BULLET), 25, 25);
	}
}

void Chris::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[nMoveCount].left = i * CHRIS_WIDTH;
		rtMove[nMoveCount].right = rtMove[nMoveCount].left + CHRIS_WIDTH;
		rtMove[nMoveCount].top = 0;
		rtMove[nMoveCount].bottom = CHRIS_HEIGHT;
		nMoveCount++;
	}
}

void Chris::AniMove()
{
	if (GATIMER()->GetTimer() - fAniMoveTime > 0.1f)
	{
		SetRect(rtMove[nCurrentMove++]);

		fAniMoveTime = GATIMER()->GetTimer();
	}
	if (nCurrentMove >= ANI_MOVE)
	{
		nCurrentMove = 0;
	}
}