#include "stdafx.h"

Car::Car()
{
}

Car::Car(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	Create(width, height);
	SetTexture(texture);
}

Car::~Car()
{
}

void Car::Create(int width, int height)
{
	nFrameWidth = width;
	nFrameHeight = height;
	fSpeed = 0.0f;
	bVisible = false;
	bHit = false;

	RECT rt;
	rt.left = 0;
	rt.right = width;
	rt.top = 0;
	rt.bottom = height;

	SetRect(rt);
}

void Car::Respawn()
{
	bVisible = true;
	vPostion.y = nFrameHeight;
	vPostion.x = -(float)(GATIMER()->GetRand(330, 300));
}

void Car::Move()
{
	vPostion.y -= OBJMANAGER()->GetPlayer()->GetSpeed() - 35.0f;
	
	if (vPostion.x >= -300)
	{
		vPostion.x = -300;
	}
	if (vPostion.x <= -630)
	{
		vPostion.x = -630;
	}

	if (vPostion.y < -768)
	{
		bVisible = false;
	}
	if (vPostion.y > nFrameHeight)
	{
		bVisible = false;
	}
}