#include "DXUT.h"
#include "Richard.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

Richard::Richard()
{
}

Richard::Richard(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

Richard::~Richard()
{
}

void Richard::Create()
{
	SetRect(0, RICHARD_WIDTH, 0, RICHARD_HEIGHT);

	fHp = 1000.0f;
	fSpeed = 5.0f;

	bVisible = false;
	bRandMove = false;
	bRespawn = false;
	bDie = false;

	fAniTime = 0.0f;
	nAniCount = 0;
	nCurrentAni = 0;

	fLazerTime = 0.0f;

	pBombEffect = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::MIDDLE_BOSS_BOMB1), 470, 370, 6, 1);

	pHpBar = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::BOSS_HP_BAR), 310, 40, 0, 0);
	pHpBar->SetVisible(false);
	for (int i = 0; i < MAX_BOSS_HP; i++)
	{
		pHp[i] = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::BOSS_HP), 2, 34, 0, 0);
		pHp[i]->SetVisible(false);
	}

	pLazer = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::LAZER), 1024, 34, 10, 1);

	SetAniRect();
}

void Richard::Update(Player* pPlayer)
{
	SetCollision(109, 126, 29, 295);
	SetCenterPos(vPosition.x + 112, vPosition.y + 146, 0);

	if (bVisible)
	{
		Move();
		Shot();
		AniRichard();
		pBombEffect->SetPosition(vPosition.x - 75, vPosition.y + 15, 0);
		pHpBar->SetPosition(vPosition.x - 5, vPosition.y + 410, 0);
		for (int i = 0; i < MAX_BOSS_HP; i++)
		{
			pHp[i]->SetPosition(pHpBar->GetPosition()->x + 2 + (i * 3), pHpBar->GetPosition()->y + 2, 0);
		}
		pLazer->SetPosition(vPosition.x - 1024, vPosition.y + 118, 0);
		pLazer->SetCollision(0, 1024, 0, 34);
		if (pLazer->GetVisible())
		{
			pLazer->Animation(0.1f, 10, false);
		}
		if (pLazer->GetFinish())
		{
			pLazer->SetFinish(false);
			pLazer->SetVisible(false);
			pLazer->SetHit(false);
		}
	}
	if (fHp <= 0 && !bDie)
	{
		bDie = true;
		bVisible = false;
		pLazer->SetVisible(false);
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

void Richard::Shot()
{
	if (GATIMER()->GetTimer() - fLazerTime > 3.0f)
	{
		pLazer->SetVisible(true);

		fLazerTime = GATIMER()->GetTimer();
	}
}

void Richard::SetAniRect()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			rtAni[nAniCount].left = j * RICHARD_WIDTH;
			rtAni[nAniCount].right = rtAni[nAniCount].left + RICHARD_WIDTH;
			rtAni[nAniCount].top = i * RICHARD_HEIGHT;
			rtAni[nAniCount].bottom = rtAni[nAniCount].top + RICHARD_HEIGHT;
			nAniCount++;
		}
	}
}

void Richard::AniRichard()
{
	if (GATIMER()->GetTimer() - fAniTime > 0.2f)
	{
		SetRect(rtAni[nCurrentAni++]);

		fAniTime = GATIMER()->GetTimer();
	}
	if (nCurrentAni >= ANI_RICHARD)
	{
		nCurrentAni = 0;
	}
}