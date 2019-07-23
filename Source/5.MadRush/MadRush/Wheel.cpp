#include "stdafx.h"

Wheel::Wheel(void)
{
}

Wheel::Wheel(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Wheel::~Wheel(void)
{
}

void Wheel::Create()
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	fSpeed = 10.0f;

	fHp = 1.0f;
}

void Wheel::Process()
{
}