#include "DXUT.h"
#include "James.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

James::James()
{
}

James::James(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

James::~James()
{
}

void James::Create()
{
	SetRect(0, JAMES_WIDTH, 0, JAMES_HEIGHT);

	fHp = 5.0f;
	fSpeed = 2.0f;

	bHitAni = false;
	fHitTime = 0.0f;
	bDie = false;

	fBulletRespawn = 0.0f;
	fBulletTime = 0.0f;
	nBulletCount = 0;
	nBulletCheck = 0;

	fAniMoveTime = 0.0f;
	nMoveCount = 0;
	nCurrentMove = 0;

	bVisible = false;

	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::BOMB_EFFECT1), 270, 230, 6, 1);

	CreateBullet();
	SetAniRect();
}

void James::Update(Player* pPlayer)
{
	SetCollision(7, 60, 11, 34);
	SetCenterPos(vPosition.x + 25, vPosition.y + 20, 0);

	if (bVisible)
	{
		if (vPosition.x > 400)
		{
			Shot(pPlayer);
		}
		StraightMove();
		AniMove();
		pBombEffect->SetPosition(vPosition.x - 90, vPosition.y - 90, 0);
	}
	if (fHp <= 0 && !bDie)
	{
		bDie = true;
		bVisible = false;
		OBJMANAGER()->SetScore(OBJMANAGER()->GetScore() + 100);
	}

	for (int i = 0; i < JAMES_MAX_BULLET; i++)
	{
		pBullet[i]->SetCollision(0, 25, 0, 25);

		pBullet[i]->Shot();
	}
	if (bDie)
	{
		SOUNDMANAGER()->pBomb2->Play(0, NULL);
		pBombEffect->SetVisible(true);
		pBombEffect->Animation(0.1f, 6, false);
		if (pBombEffect->GetFinish())
		{
			pBombEffect->SetFinish(false);
			bDie = false;
			fHp = 5.0f;
		}
	}
	HitSystem(pPlayer);
}

void James::Shot(Player* pPlayer)
{
	D3DXVECTOR3 vDirect;

	if (GATIMER()->GetTimer() - fBulletRespawn > 3.0f)
	{
		nBulletCheck = 0;
		fBulletRespawn = GATIMER()->GetTimer();
	}
	if (GATIMER()->GetTimer() - fBulletTime > 0.1f && nBulletCheck < 3)
	{
		pBullet[nBulletCount]->SetVisible(true);
		pBullet[nBulletCount]->SetPosition(vPosition.x + 7, vPosition.y + 23, 0);
		pBullet[nBulletCount]->SetSpeed(10.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);
		pBullet[nBulletCount]->SetAim(true);

		vDirect.x = pPlayer->GetPosition()->x + 70 - vPosition.x;
		vDirect.y = pPlayer->GetPosition()->y + 12 - vPosition.y;
		vDirect.z = 0.0f;

		D3DXVec3Normalize(&vDirect, &vDirect);

		pBullet[nBulletCount]->SetDirect(vDirect);

		nBulletCount++;
		nBulletCheck++;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= JAMES_MAX_BULLET)
	{
		nBulletCount = 0;
	}
}

void James::CreateBullet()
{
	for (int i = 0; i < JAMES_MAX_BULLET; i++)
	{
		pBullet[i] = new AimBullet(OBJMANAGER()->GetTexture(GaBase::JAMES_BULLET), 25, 25);
	}
}

void James::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[nMoveCount].left = i * JAMES_WIDTH;
		rtMove[nMoveCount].right = rtMove[nMoveCount].left + JAMES_WIDTH;
		rtMove[nMoveCount].top = 0;
		rtMove[nMoveCount].bottom = JAMES_HEIGHT;
		nMoveCount++;
	}
}

void James::AniMove()
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