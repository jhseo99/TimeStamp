#include "DXUT.h"
#include "Cedric.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

Cedric::Cedric()
{
}

Cedric::Cedric(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Cedric::~Cedric()
{
}

void Cedric::Create()
{
	SetRect(0, CEDRIC_WIDTH, 0, CEDRIC_HEIGHT);

	fHp = 1500.0f;
	fSpeed = 5.0f;

	fSplitBulletTime = 0.0f;
	fSplitFireTime = 0.0f;
	nSplitBulletCount = 0;
	fBulletTime = 0.0f;
	nBulletCount = 0;
	bSplit = false;

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

void Cedric::Update(Player* pPlayer)
{
	SetCollision(60, 383, 112, 124);
	SetCenterPos(vPosition.x + 160, vPosition.y + 200, 0);

	if (bVisible)
	{
		Move();
		Shot();
		AniCedric();
		pBombEffect->SetPosition(vPosition.x - 30, vPosition.y - 55, 0);
		pHpBar->SetPosition(vPosition.x - 5, vPosition.y + 410, 0);
		for (int i = 0; i < MAX_BOSS_HP; i++)
		{
			pHp[i]->SetPosition(pHpBar->GetPosition()->x + 2 + (i * 3), pHpBar->GetPosition()->y + 2, 0);
		}
	}
	for (int i = 0; i < CEDRIC_SPLIT_BULLET; i++)
	{
		pSplitBullet[i]->SetCollision(5, 25, 5, 25);
		pSplitBullet[i]->Shot();
	}

	for (int i = 0; i < CEDRIC_MAX_BULLET; i++)
	{
		pBullet[i]->SetCollision(5, 25, 5, 25);
		pBullet[i]->Shot();
	}

	if (fHp <= 0 && !bDie)
	{
		bDie = true;
		bVisible = false;
		OBJMANAGER()->SetScore(OBJMANAGER()->GetScore() + 50);
	}
	if (bDie && bRespawn)
	{
		SOUNDMANAGER()->pBomb3->Play(0, NULL);
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

void Cedric::CreateBullet()
{
	for (int i = 0; i < CEDRIC_SPLIT_BULLET; i++)
	{
		pSplitBullet[i] = new DirectBullet(OBJMANAGER()->GetTexture(GaBase::TextureID::CEDRIC_BULLET1), 55, 55);
	}
	for (int i = 0; i < CEDRIC_MAX_BULLET; i++)
	{
		pBullet[i] = new DirectBullet(OBJMANAGER()->GetTexture(GaBase::TextureID::CEDRIC_BULLET2), 35, 35);
	}
}

void Cedric::Shot()
{
	if (GATIMER()->GetTimer() - fSplitBulletTime > 5.0f)
	{
		for (int i = 0; i < 8; i++)
		{
			pSplitBullet[nSplitBulletCount]->SetVisible(true);
			pSplitBullet[nSplitBulletCount]->SetPosition(vPosition.x + 115, vPosition.y + 262, 0);
			pSplitBullet[nSplitBulletCount]->SetSpeed(10.0f);
			pSplitBullet[nSplitBulletCount]->SetAngle(0.0f);
			pSplitBullet[nSplitBulletCount]->SetShot(true);

			CircleRespawn(pSplitBullet[nSplitBulletCount], i);

			nSplitBulletCount++;
		}

		bSplit = true;

		fSplitFireTime = GATIMER()->GetTimer();
		fSplitBulletTime = GATIMER()->GetTimer();
	}
	if (nSplitBulletCount >= CEDRIC_SPLIT_BULLET)
	{
		nSplitBulletCount = 0;
	}
	if (GATIMER()->GetTimer() - fSplitFireTime > 0.5f && bSplit)
	{
		for (int i = 0; i < 8; i++)
		{
			pSplitBullet[i]->SetShot(false);
			pSplitBullet[i]->SetVisible(false);
			for (int j = 0; j < 8; j++)
			{
				pBullet[nBulletCount]->SetVisible(true);
				pBullet[nBulletCount]->SetPosition(pSplitBullet[i]->GetPosition()->x, pSplitBullet[i]->GetPosition()->y, 0);
				pBullet[nBulletCount]->SetSpeed(5.0f);
				pBullet[nBulletCount]->SetAngle(0.0f);
				pBullet[nBulletCount]->SetShot(true);

				CircleRespawn(pBullet[nBulletCount], j);

				nBulletCount++;
			}
		}
	
		bSplit = false;
		fSplitFireTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= CEDRIC_MAX_BULLET)
	{
		nBulletCount = 0;
	}
}

void Cedric::CircleRespawn(DirectBullet* pBullet, int num)
{
	D3DXVECTOR3 vDirect;

	vDirect.x = cos(2.0 * PI * (num / 8.0f));
	vDirect.y = sin(2.0 * PI * (num / 8.0f));
	vDirect.z = 0.0f;

	D3DXVec3Normalize(&vDirect, &vDirect);

	pBullet->SetDirect(vDirect);
}

void Cedric::SetAniRect()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			rtAni[nAniCount].left = j * CEDRIC_WIDTH;
			rtAni[nAniCount].right = rtAni[nAniCount].left + CEDRIC_WIDTH;
			rtAni[nAniCount].top = i * CEDRIC_HEIGHT;
			rtAni[nAniCount].bottom = rtAni[nAniCount].top + CEDRIC_HEIGHT;
			nAniCount++;
		}
	}
}

void Cedric::AniCedric()
{
	if (GATIMER()->GetTimer() - fAniTime > 0.2f)
	{
		SetRect(rtAni[nCurrentAni++]);

		fAniTime = GATIMER()->GetTimer();
	}
	if (nCurrentAni >= ANI_CEDRIC)
	{
		nCurrentAni = 0;
	}
}