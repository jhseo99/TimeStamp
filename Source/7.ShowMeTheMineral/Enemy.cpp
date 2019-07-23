#include "DXUT.h"
#include "Enemy.h"
#include "GaTimer.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Respawn(float hp, float speed)
{
	vPosition.x = 1024.0f;
	vPosition.y = (rand() % 450) + 100;
	vPosition.z = 0;

	bHitAni = false;
	fHitTime = 0.0f;
	bDie = false;

	bVisible = true;

	fHp = hp;
	fSpeed = speed;
}

void Enemy::StraightMove()
{
	vPosition.x -= fSpeed;
}

void Enemy::HitSystem(Player* pPlayer)
{
	if (bHit)
	{
		fHp -= pPlayer->GetDamage();
		bHitAni = true;
		fHitTime = GATIMER()->GetTimer();
		bHit = false;
	}
	if (bHitAni)
	{
		SetColor(1.0f, 0.5f, 0.2f, 1.0f);
		if (GATIMER()->GetTimer() - fHitTime > 0.2f)
		{
			SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			bHitAni = false;

			fHitTime = GATIMER()->GetTimer();
		}
	}
}