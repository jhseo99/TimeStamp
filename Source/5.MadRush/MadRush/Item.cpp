#include "stdafx.h"

Item::Item(void)
{
}

Item::Item(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

Item::~Item(void)
{
}

void Item::Create()
{
	nFrameWidth = 60;
	nFrameHeight = 60;
	bVisible = false;

	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	fSpeed = 2.5f;
	bHit = false;

	SetRect(rt);
}

void Item::Respawn()
{
	SetPosition(GATIMER()->GetRand(900, 10), -200, 0);
}

void Item::Move()
{
	if (bVisible)
	{
		this->vPosition.y += fSpeed;
		if (this->vPosition.y > 768)
		{
			bVisible = false;
		}
	}
}

void Item::HitHp()
{
	if (bHit)
	{
		bHit = false;
		bVisible = false;
		OBJMANAGER()->SetHP(1.0);
	}
}

void Item::HitGun()
{
	if (bHit)
	{
		bHit = false;
		bVisible = false;
		OBJMANAGER()->SetGun(1);
	}
}

void Item::Process()
{
}