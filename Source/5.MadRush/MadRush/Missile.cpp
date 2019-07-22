#include "stdafx.h"

Missile::Missile(void)
{
}

Missile::Missile(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Missile::~Missile(void)
{
}

void Missile::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 10.0f;
	bShoot = false;
	fGradiant = 0;
	fFirePosX = 0;
	fFirePosY = 0;
}

void Missile::Move(D3DXVECTOR3 vDirection)
{
	Hit();

	if (bShoot)
	{
		this->vPosition.x += vDirection.x * fGradiant;
		this->vPosition.y -= vDirection.y * fSpeed;
	}
}

void Missile::SetFirePos(float x, float y)
{
	fFirePosX = x;
	fFirePosY = y;

	SetPosition(fFirePosX, fFirePosY, 0);
}

void Missile::Hit()
{
	if (bHit)
	{
		bHit = false;
		bVisible = false;
	}
}

void Missile::Process()
{
}