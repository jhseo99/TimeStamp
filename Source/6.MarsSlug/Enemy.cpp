#include "DXUT.h"
#include "Enemy.h"


Enemy::Enemy()
{
	bSplit = false;
}


Enemy::~Enemy()
{
}

void Enemy::HitSystem(float hp)
{
	if (bHit)
	{
		fHp--;
		lastHit = DXUTGetTime();
		bHitAni = true;
		bHit = false;
	}
	if (fHp <= 0)
	{
		bDie = true;
		bVisible = false;
		fHp = hp;
		bSplit = true;
	}
	HitAni();
}

void Enemy::HitAni()
{
	if (bHitAni)
	{
		D3DCOLOR color = D3DCOLOR_COLORVALUE(0.5f, 1.0f, 0.5f, 0.5f);

		SetColor(color);
		if (DXUTGetTime() - lastHit > 0.1f)
		{
			bHitAni = false;
		}
	}
	if (!bHitAni)
	{
		D3DCOLOR color = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);

		SetColor(color);
	}
}