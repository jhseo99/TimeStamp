#include "stdafx.h"

GaugeBar::GaugeBar(void)
{
}

GaugeBar::GaugeBar(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

GaugeBar::~GaugeBar(void)
{
}

void GaugeBar::Create()
{
	nFrameWidth = 170;
	nFrameHeight = 210;
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = nFrameWidth;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	SetPosition(10, 550, 0);
}

void GaugeBar::Process()
{
}