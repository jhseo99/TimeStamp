#include "stdafx.h"

Bullet::Bullet(void)
{
}

Bullet::Bullet(LPDIRECT3DTEXTURE9 texture, int width, int height, float fSpeed)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	this->fSpeed = fSpeed;
	Create();
}

Bullet::~Bullet(void)
{
}

void Bullet::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	bShoot = false;
	fGradiant = 0;
	fFirePosX = 0;
	fFirePosY = 0;
	randNum = 0;
	vDirect = { 0, 1 };
}

void Bullet::Move(D3DXVECTOR2* vDirection)
{
	Hit();

	if (bShoot)
	{
		this->vPosition.x += vDirection->x * fSpeed;
		this->vPosition.y += vDirection->y * fSpeed;

		if (this->vPosition.y <= 0 - nFrameHeight || this->vPosition.y > 768)
		{
			bShoot = false;
			bVisible = false;
		}
	}
}

void Bullet::SetFirePos(float x, float y)
{
	fFirePosX = x;
	fFirePosY = y;

	SetPosition(fFirePosX, fFirePosY, 0);
}

void Bullet::Hit()
{
	if (bHit)
	{
		bHit = false;
		bVisible = false;
	}
}

void Bullet::Process()
{
}