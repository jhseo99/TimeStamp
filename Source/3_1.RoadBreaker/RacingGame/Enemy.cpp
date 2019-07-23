#include "stdafx.h"

Enemy::Enemy()
{
}

Enemy::Enemy(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

Enemy::~Enemy()
{
}

void Enemy::Create()
{
	nFrameWidth = 120;
	nFrameHeight = 220;
	nFrameSpeed = 10;
	fSpeed = 0.0f;
	RandNum = 0;
	RandSpeed = 0;
	fDistance = 0.0f;
	CurrentDirectionFrame = 0;
	CurrentSpeedFrame = 0;
	bVisible = true;
	bHit = false;
	bGoal = false;

	RECT rt;
	rt.left = 0;
	rt.right = nFrameWidth;
	rt.top = 0;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	SetPosition(-550, -400, 0);
}

void Enemy::Move(DWORD absoluteFrame)
{
	fDistance += fSpeed;

	fSpeed = RandSpeed;

	if (bHit)
	{
		vPostion.x += (vDirection.x * 20.0f);
		RandSpeed = (int)OBJMANAGER()->GetPlayer()->GetSpeed() - 3;

		RandNum = 2;
		bHit = false;
	}

	vPostion.y -= OBJMANAGER()->GetPlayer()->GetSpeed() - fSpeed;

	if (absoluteFrame - CurrentDirectionFrame > 100)
	{
		RandNum = GATIMER()->GetRand(3, 0);

		CurrentDirectionFrame = absoluteFrame;
	}

	if (absoluteFrame - CurrentSpeedFrame > 20 && !bHit)
	{
		if (OBJMANAGER()->GetPlayer()->GetSpeed() <= 30)
		{
			RandSpeed += 2;
			if (RandSpeed >= 40)
			{
				RandSpeed = 40;
			}
		}
		else if (OBJMANAGER()->GetPlayer()->GetSpeed() > 30 && OBJMANAGER()->GetPlayer()->GetSpeed() < 40)
		{
			RandSpeed = GATIMER()->GetRand(15, 30);
		}
		else if (OBJMANAGER()->GetPlayer()->GetSpeed() == 40)
		{
			if (OBJMANAGER()->GetPlayer()->GetDistance() + 10 < fDistance)
			{
				RandSpeed = GATIMER()->GetRand(10, 20);
			}
			else
			{
				RandSpeed = GATIMER()->GetRand(5, 40);
			}
		}

		CurrentSpeedFrame = absoluteFrame;
	}
	
	if (!bHit)
	{
		switch (RandNum)
		{
		case 0:
			vPostion.x -= 10.0f;
			break;
		case 1:
			vPostion.x += 10.0f;
			break;
		case 2:
			break;
		default:
			break;
		}
	}

	if (vPostion.x >= -300)
	{
		vPostion.x = -300;
	}
	if (vPostion.x <= -630)
	{
		vPostion.x = -630;
	}
}