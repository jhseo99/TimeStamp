#include "stdafx.h"

Bomber::Bomber(void)
{
}

Bomber::Bomber(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Bomber::~Bomber(void)
{
}

void Bomber::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 7.0f;

	fHp = 1.0f;
}

void Bomber::Process()
{
}