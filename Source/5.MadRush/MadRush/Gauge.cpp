#include "stdafx.h"

Gauge::Gauge(void)
{
}

Gauge::Gauge(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

Gauge::~Gauge(void)
{
}

void Gauge::Create()
{
	nFrameWidth = 150;
	nFrameHeight = 31;
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);
}

void Gauge::Process()
{
}