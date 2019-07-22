#include "DXUT.h"
#include "Bullet.h"


Bullet::Bullet()
{
	InitBullet();
	ZeroMemory(&vDirection, sizeof(vDirection));
}


Bullet::~Bullet()
{
}

void Bullet::InitBullet()
{
	bVisible = false;
	bShot = false;
	bHit = false;
	fGradiant = 0;
	fSpeedX = 20.0f;
	fSpeedY = 5.0f;
}

void Bullet::Move()
{
	if (bShot)
	{
		vPosition.x += fSpeedX;
		vPosition.y -= fGradiant * fSpeedY;
		if (vPosition.x <= 0 - rtSize.right)
		{
			bVisible = false;
			bShot = false;
		}
	}
	UpdateCollision((rtSize.right / 10), rtSize.right - ((rtSize.right / 10) * 2), 
					(rtSize.right / 10), rtSize.right - ((rtSize.right / 10) * 2));
	Hit();
}

void Bullet::Move(bool bAim)
{
	if (bShot)
	{
		vPosition.x += vDirection.x * fSpeedX;
		vPosition.y += vDirection.y * fSpeedY;
		if (vPosition.x <= 0 - rtSize.right)
		{
			bVisible = false;
			bShot = false;
		}
	}
	UpdateCollision((rtSize.right / 10), rtSize.right - ((rtSize.right / 10) * 2),
					(rtSize.right / 10), rtSize.right - ((rtSize.right / 10) * 2));
	Hit();
}

void Bullet::Hit()
{
	if (bHit)
	{
		bVisible = false;
		bHit = false;
	}
}