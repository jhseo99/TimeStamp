#include "DXUT.h"
#include "Boris.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

Boris::Boris()
{
}

Boris::Boris(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Boris::~Boris()
{
}

void Boris::Create()
{
	SetRect(0, BORIS_WIDTH, 0, BORIS_HEIGHT);

	fHp = 1000.0f;
	fSpeed = 5.0f;

	fBulletRespawn = 0.0f;
	fBulletTime = 0.0f;
	nBulletCount = 0;
	nBulletCheck = 0;

	bVisible = false;
	bRandMove = false;
	bRespawn = false;
	bDie = false;

	fAniTime = 0.0f;
	nAniCount = 0;
	nCurrentAni = 0;

	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::MIDDLE_BOSS_BOMB1), 470, 370, 6, 1);

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

void Boris::Update(Player* pPlayer)
{
	SetCollision(110, 140, 17, 348);
	SetCenterPos(vPosition.x + 160, vPosition.y + 200, 0);

	if (bVisible)
	{
		Move();
		Shot();
		AniBoris();
		pBombEffect->SetPosition(vPosition.x - 75, vPosition.y + 15, 0);
		pHpBar->SetPosition(vPosition.x - 5, vPosition.y + 410, 0);
		for (int i = 0; i < MAX_BOSS_HP; i++)
		{
			pHp[i]->SetPosition(pHpBar->GetPosition()->x + 2 + (i * 3), pHpBar->GetPosition()->y + 2, 0);
		}
	}
	for (int i = 0; i < BORIS_MAX_BULLET; i++)
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
			fHp = 1000.0f;
		}
	}
	HitSystem(pPlayer);
}

void Boris::CreateBullet()
{
	for (int i = 0; i < BORIS_MAX_BULLET; i++)
	{
		pBullet[i] = new DirectBullet(OBJMANAGER()->GetTexture(GaBase::TextureID::BORIS_BULLET), 35, 35);
	}
}

void Boris::Shot()
{
	if (GATIMER()->GetTimer() - fBulletRespawn > 3.0f)
	{
		nBulletCheck = 0;
		fBulletRespawn = GATIMER()->GetTimer();
	}
	if (GATIMER()->GetTimer() - fBulletTime > 0.1f && nBulletCheck < 5)
	{
		for (int i = 0; i < 16; i++)
		{
			pBullet[nBulletCount]->SetVisible(true);
			pBullet[nBulletCount]->SetPosition(vPosition.x + 115, vPosition.y + 262, 0);
			pBullet[nBulletCount]->SetSpeed(10.0f);
			pBullet[nBulletCount]->SetAngle(0.0f);
			pBullet[nBulletCount]->SetShot(true);

			CircleRespawn(pBullet[nBulletCount], i);

			nBulletCount++;
		}

		nBulletCheck++;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= BORIS_MAX_BULLET)
	{
		nBulletCount = 0;
	}
}

void Boris::CircleRespawn(DirectBullet* pBullet, int num)
{
	D3DXVECTOR3 vDirect;

	vDirect.x = cos(2.0 * PI * (num / 16.0f));
	vDirect.y = sin(2.0 * PI * (num / 16.0f));
	vDirect.z = 0.0f;

	D3DXVec3Normalize(&vDirect, &vDirect);

	pBullet->SetDirect(vDirect);
}

void Boris::SetAniRect()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			rtAni[nAniCount].left = j * BORIS_WIDTH;
			rtAni[nAniCount].right = rtAni[nAniCount].left + BORIS_WIDTH;
			rtAni[nAniCount].top = i * BORIS_HEIGHT;
			rtAni[nAniCount].bottom = rtAni[nAniCount].top + BORIS_HEIGHT;
			nAniCount++;
		}
	}
}

void Boris::AniBoris()
{
	if (GATIMER()->GetTimer() - fAniTime > 0.2f)
	{
		SetRect(rtAni[nCurrentAni++]);
		
		fAniTime = GATIMER()->GetTimer();
	}
	if (nCurrentAni >= ANI_BORIS)
	{
		nCurrentAni = 0;
	}
}