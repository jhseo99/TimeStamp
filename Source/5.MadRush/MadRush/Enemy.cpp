#include "stdafx.h"

Enemy::Enemy(void)
{
	Create();
}

Enemy::~Enemy(void)
{
}

void Enemy::Move()
{
	if (bVisible)
	{
		AniHit();
		this->vPosition.y += fSpeed;
		if (this->vPosition.y > 768)
		{
			bVisible = false;
		}
	}
	if (bExplosion)
	{
		AniExplosion();
	}
	if (bBomb)
	{
		AniBomb();
	}
	if (bAniBoss)
	{
		AniBoss();
	}
}

void Enemy::Respawn()
{
	SetPosition(GATIMER()->GetRand(900, 10), -200, 0);
}

void Enemy::Hit(float hp)
{
	if (bHit)
	{
		fHp--;
		bHit = false;
		nAniHitCount = 0;
		bAniHit = true;
		OBJMANAGER()->SetScore(1);
	}
	if (fHp <= 0)
	{
		bVisible = false;
		bHit = false;
		pEffectHit->SetVisible(false);
		bAniHit = false;
		nAniHitCount = 0;
		nAniExplosionCount = 0;
		nAniBombCount = 0;
		nAniBossCount = 0;
		bExplosion = true;
		bBomb = true;
		bAniBoss = true;
		fHp = hp;
	}
}

void Enemy::Create()
{
	bHit = false;
	bAniHit = false;
	bExplosion = false;
	bBomb = false;
	bAniBoss = false;

	nAniHitCount = 0;
	nAniExplosionCount = 0;
	nAniBombCount = 0;
	nAniBossCount = 0;

	lastHitFrame = 0;
	lastExplosionFrame = 0;
	lastBombFrame = 0;
	lastBossFrame = 0;

	bDie = false;

	SetAniRect();
}

void Enemy::SetAniRect()
{
	int numExplosion = 0;
	int numBomb = 0;
	int numBoss = 0;

	pEffectHit = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::HITEFFECT), 192, 192);
	pExplosion = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::EXPLOSION), 120, 120);
	pEffectBomb = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::BOMBEFFECT), 150, 150);
	pEffectBoss = new Effect(OBJMANAGER()->GetTexture(GaBase::TextureID::BOSSEFFECT), 250, 250);

	for (int i = 0; i < ANIHIT; i++)
	{
		rtAniHit[i].left = i * 192;
		rtAniHit[i].top = 0;
		rtAniHit[i].right = rtAniHit[i].left + 192;
		rtAniHit[i].bottom = 192;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rtAniExplosion[numExplosion].left = j * 120;
			rtAniExplosion[numExplosion].top = i * 120;
			rtAniExplosion[numExplosion].right = (j + 1) * 120;
			rtAniExplosion[numExplosion].bottom = (i + 1) * 120;
			numExplosion++;
		}	
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			rtAniBomb[numBomb].left = j * 150;
			rtAniBomb[numBomb].top = i * 150;
			rtAniBomb[numBomb].right = (j + 1) * 150;
			rtAniBomb[numBomb].bottom = (i + 1) * 150;
			numBomb++;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			rtAniBoss[numBoss].left = j * 250;
			rtAniBoss[numBoss].top = i * 250;
			rtAniBoss[numBoss].right = (j + 1) * 250;
			rtAniBoss[numBoss].bottom = (i + 1) * 250;
			numBoss++;
		}
	}
}

void Enemy::AniHit()
{
	int nFrameSpeed = 3;

	if (bAniHit)
	{
		pEffectHit->SetVisible(true);
		pEffectHit->SetPosition(vPosition.x - 50, vPosition.y, 0);
		if (lastHitFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			pEffectHit->SetRect(rtAniHit[nAniHitCount++]);
			lastHitFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
		if (nAniHitCount == ANIHIT)
		{
			nAniHitCount = 0;
			pEffectHit->SetVisible(false);
			bAniHit = false;
		}
	}
}

void Enemy::AniExplosion()
{
	int nFrameSpeed = 5;

	if (bExplosion)
	{
		pExplosion->SetVisible(true);
		pExplosion->SetPosition(vPosition.x, vPosition.y, 0);
		if (lastExplosionFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			pExplosion->SetRect(rtAniExplosion[nAniExplosionCount++]);
			lastExplosionFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
		if (nAniExplosionCount == ANIEXPLOSION)
		{
			nAniExplosionCount = 0;
			pExplosion->SetVisible(false);
			bExplosion = false;
		}
	}
}

void Enemy::AniBomb()
{
	int nFrameSpeed = 6;

	if (bBomb)
	{
		pEffectBomb->SetVisible(true);
		pEffectBomb->SetPosition(vPosition.x, vPosition.y, 0);
		if (lastBombFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			pEffectBomb->SetRect(rtAniBomb[nAniBombCount++]);
			lastBombFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
		if (nAniBombCount == ANIBOMB)
		{
			nAniBombCount = 0;
			pEffectBomb->SetVisible(false);
			bBomb = false;
		}
	}
}

void Enemy::AniBoss()
{
	int nFrameSpeed = 7;

	if (bAniBoss)
	{
		pEffectBoss->SetVisible(true);
		pEffectBoss->SetPosition(vPosition.x - 25, vPosition.y + 25, 0);
		if (lastBossFrame != GATIMER()->GetAbsoluteFrame() / nFrameSpeed)
		{
			pEffectBoss->SetRect(rtAniBoss[nAniBossCount++]);
			lastBossFrame = GATIMER()->GetAbsoluteFrame() / nFrameSpeed;
		}
		if (nAniBossCount == ANIBOSS)
		{
			nAniBossCount = 0;
			pEffectBoss->SetVisible(false);
			bAniBoss = false;
			bDie = true;
		}
	}
}

void Enemy::Process()
{
}