#include "stdafx.h"

Screen::Screen(void)
{
}

Screen::Screen(LPDIRECT3DTEXTURE9 texture, int x, int y)
{
	Create();
	SetTexture(texture);
	SetPosition(x, y, 0);
}

Screen::~Screen(void)
{
}

void Screen::Create()
{
	nFrameWidth = 1024;
	nFrameHeight = 768;
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);
}

void Screen::Process()
{
}