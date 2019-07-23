#include "stdafx.h"

Effect::Effect(void)
{
}

Effect::Effect(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	nFrameWidth = width;
	nFrameHeight = height;
	Create();
}

Effect::~Effect(void)
{
}

void Effect::Create()
{
	bVisible = false;

	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);
}

void Effect::Process()
{
}