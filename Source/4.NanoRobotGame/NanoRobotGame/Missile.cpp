#include "stdafx.h"

Missile::Missile()
{
}

Missile::Missile(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	Create(width, height);
	SetTexture(texture);
}

Missile::~Missile()
{
}

void Missile::Create(int width, int height)
{
	nFrameWidth = width;
	nFrameHeight = height;
	nStartPosX = 0;
	nStartPosY = 0;
	bHit = false;
	bShot = false;
}

void Missile::Shoot()
{
	if (bShot)
	{
		D3DXVECTOR3* vPos = GetPosition();

		vPos->x += 20.0f;
		
		if (vPos->x > 1024)
		{
			vPos->x = 0;
			bShot = false;
			bVisible = false;

			SetPosition(nStartPosX, nStartPosY, 0);
		}
	}
	if (bHit)
	{
		bVisible = false;
		bHit = false;
	}
}

void Missile::SetStartPoint(int x, int y)
{
	nStartPosX = x;
	nStartPosY = y;

	SetPosition(nStartPosX, nStartPosY, 0);
}