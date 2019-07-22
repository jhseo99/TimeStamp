#include "DXUT.h"
#include "John.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

John::John()
{
}

John::John(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

John::~John()
{
}

void John::Create()
{
	SetRect(0, JOHN_WIDTH, 0, JOHN_HEIGHT);

	fHp = 10.0f;
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

	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::BOMB_EFFECT2), 200, 150, 6, 1);

	CreateBullet();
	SetAniRect();
}

void John::Update(Player* pPlayer)
{
	SetCollision(34, 25, 3, 103);
	SetCenterPos(vPosition.x + 36, vPosition.y + 42, 0);

	if (bVisible)
	{
		if (vPosition.x > 400)
		{
			Shot(pPlayer);
		}
		StraightMove();
		AniMove();
		pBombEffect->SetPosition(vPosition.x - 65, vPosition.y - 20, 0);
	}
	if (fHp <= 0 && !bDie)
	{
		bDie = true;
		bVisible = false;
		OBJMANAGER()->SetScore(OBJMANAGER()->GetScore() + 100);
	}

	for (int i = 0; i < JOHN_MAX_BULLET; i++)
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
			fHp = 10.0f;
		}
	}
	HitSystem(pPlayer);
}

void John::Shot(Player* pPlayer)
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
		pBullet[nBulletCount]->SetPosition(vPosition.x + 7, vPosition.y, 0);
		pBullet[nBulletCount]->SetSpeed(10.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);
		pBullet[nBulletCount]->SetAim(true);

		pBullet[nBulletCount+1]->SetVisible(true);
		pBullet[nBulletCount+1]->SetPosition(vPosition.x + 7, vPosition.y + 100, 0);
		pBullet[nBulletCount+1]->SetSpeed(10.0f);
		pBullet[nBulletCount+1]->SetAngle(0.0f);
		pBullet[nBulletCount+1]->SetShot(true);
		pBullet[nBulletCount+1]->SetAim(true);

		vDirect.x = pPlayer->GetPosition()->x + 70 - vPosition.x;
		vDirect.y = pPlayer->GetPosition()->y + 12 - vPosition.y;
		vDirect.z = 0.0f;

		D3DXVec3Normalize(&vDirect, &vDirect);

		pBullet[nBulletCount]->SetDirect(vDirect);
		pBullet[nBulletCount+1]->SetDirect(vDirect);

		nBulletCount += 2;
		nBulletCheck++;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= JOHN_MAX_BULLET - 2)
	{
		nBulletCount = 0;
	}
}

void John::CreateBullet()
{
	for (int i = 0; i < JOHN_MAX_BULLET; i++)
	{
		pBullet[i] = new AimBullet(OBJMANAGER()->GetTexture(GaBase::JOHN_BULLET), 25, 25);
	}
}

void John::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[nMoveCount].left = i * JOHN_WIDTH;
		rtMove[nMoveCount].right = rtMove[nMoveCount].left + JOHN_WIDTH;
		rtMove[nMoveCount].top = 0;
		rtMove[nMoveCount].bottom = JOHN_HEIGHT;
		nMoveCount++;
	}
}

void John::AniMove()
{
	if (GATIMER()->GetTimer() - fAniMoveTime > 0.2f)
	{
		SetRect(rtMove[nCurrentMove++]);

		fAniMoveTime = GATIMER()->GetTimer();
	}
	if (nCurrentMove >= ANI_MOVE)
	{
		nCurrentMove = 0;
	}
}