#include "DXUT.h"
#include "GaBase.h"


Fire::Fire()
{
}

Fire::Fire(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CreateTexture(pd3dDevice, L"texture\\fire.png");
	InitFire();
}

Fire::~Fire()
{
}

void Fire::InitFire()
{
	fFrameTime = 0.0f;
	nCurrentFrame = 0;

	SetRect(0, 250, 0, 260);
	SetTranslate(0, 0);
	SetPosition(0, 0, 0);
	SetVisible(false);

	bHit = false;
}

void Fire::Animation()
{
	if (bVisible)
	{
		if (GATIMER()->GetTimer() - fFrameTime > 0.1f)
		{
			rtRect.left = nCurrentFrame * 250;
			rtRect.right = rtRect.left + 250;

			nCurrentFrame++;
			fFrameTime = GATIMER()->GetTimer();
		}
		if (nCurrentFrame >= 7)
		{
			nCurrentFrame = 0;
		}
	}
}