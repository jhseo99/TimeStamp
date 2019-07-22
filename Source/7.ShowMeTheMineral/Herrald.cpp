#include "DXUT.h"
#include "Herrald.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

Herrald::Herrald()
{
}

Herrald::Herrald(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Herrald::~Herrald()
{
}

void Herrald::Create()
{
	SetRect(0, HERRALD_WIDTH, 0, HERRALD_HEIGHT);

	fHp = 1500.0f;
	fSpeed = 5.0f;

	fBulletTime = 0.0f;
	nBulletCount = 0;
	
	bVisible = false;
	bRandMove = false;
	bRespawn = false;
	bDie = false;

	fAniTime = 0.0f;
	nAniCount = 0;
	nCurrentAni = 0;

	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::BOSS_BOMB1), 550, 480, 6, 1);

	pHpBar = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::BOSS_HP_BAR), 310, 40, 0, 0);
	pHpBar->SetVisible(false);
	for (int i = 0; i < MAX_BOSS_HP; i++)
	{
		pHp[i] = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::BOSS_HP), 2, 34, 0, 0);
		pHp[i]->SetVisible(false);
	}

	CreateBullet();
	SetAniRect();
}

void Herrald::Update(Player* pPlayer)
{
	SetCollision(151, 301, 77, 140);
	SetCenterPos(vPosition.x + 190, vPosition.y + 131, 0);

	if (bVisible)
	{
		Move();
		Shot();
		AniHerrald();
		pBombEffect->SetPosition(vPosition.x - 30, vPosition.y - 55, 0);
		pHpBar->SetPosition(vPosition.x - 5, vPosition.y + 410, 0);
		for (int i = 0; i < MAX_BOSS_HP; i++)
		{
			pHp[i]->SetPosition(pHpBar->GetPosition()->x + 2 + (i * 3), pHpBar->GetPosition()->y + 2, 0);
		}
	}
	for (int i = 0; i < HERRALD_MAX_BULLET; i++)
	{
		pBullet1[i]->SetCollision(0, 20, 0, 20);
		pBullet1[i]->Shot();
		pBullet2[i]->SetCollision(0, 20, 0, 20);
		pBullet2[i]->Shot();
	}

	if (fHp <= 0 && !bDie)
	{
		bDie = true;
		bVisible = false;
		OBJMANAGER()->SetScore(OBJMANAGER()->GetScore() + 50);
	}
	if (bDie && bRespawn)
	{
		SOUNDMANAGER()->pBomb2->Play(0, NULL);
		pHpBar->SetVisible(false);
		for (int i = 0; i < MAX_BOSS_HP; i++)
		{
			pHp[i]->SetVisible(false);
		}
		pBombEffect->SetVisible(true);
		pBombEffect->Animation(0.15f, 6, false);
		if (pBombEffect->GetFinish())
		{
			pBombEffect->SetFinish(false);
			pBombEffect->SetVisible(false);
			bRespawn = false;
			fHp = 1500.0f;
		}
	}
	HitSystem(pPlayer);
}

void Herrald::CreateBullet()
{
	for (int i = 0; i < HERRALD_MAX_BULLET; i++)
	{
		pBullet1[i] = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::HERRALD_BULLET1), 20, 20);
		pBullet2[i] = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::HERRALD_BULLET2), 20, 20);
	}
}

void Herrald::Shot()
{
	if (GATIMER()->GetTimer() - fBulletTime > 0.1f)
	{
		float randNum;

		randNum = (float)(rand() % 20) + -10;
		randNum = randNum * 0.1f;

		pBullet1[nBulletCount]->SetVisible(true);
		pBullet1[nBulletCount]->SetPosition(vPosition.x + 61, vPosition.y + 117, 0);
		pBullet1[nBulletCount]->SetSpeed(-5.0f);
		pBullet1[nBulletCount]->SetAngle(randNum);
		pBullet1[nBulletCount]->SetShot(true);

		randNum = (float)(rand() % 20) + -10;
		randNum = randNum * 0.1f;

		pBullet2[nBulletCount]->SetVisible(true);
		pBullet2[nBulletCount]->SetPosition(vPosition.x + 61, vPosition.y + 117, 0);
		pBullet2[nBulletCount]->SetSpeed(-5.0f);
		pBullet2[nBulletCount]->SetAngle(randNum);
		pBullet2[nBulletCount]->SetShot(true);

		nBulletCount++;

		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= HERRALD_MAX_BULLET)
	{
		nBulletCount = 0;
	}
}

void Herrald::SetAniRect()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			rtAni[nAniCount].left = j * HERRALD_WIDTH;
			rtAni[nAniCount].right = rtAni[nAniCount].left + HERRALD_WIDTH;
			rtAni[nAniCount].top = i * HERRALD_HEIGHT;
			rtAni[nAniCount].bottom = rtAni[nAniCount].top + HERRALD_HEIGHT;
			nAniCount++;
		}
	}
}

void Herrald::AniHerrald()
{
	if (GATIMER()->GetTimer() - fAniTime > 0.2f)
	{
		SetRect(rtAni[nCurrentAni++]);

		fAniTime = GATIMER()->GetTimer();
	}
	if (nCurrentAni >= ANI_HERRALD)
	{
		nCurrentAni = 0;
	}
}