#include "DXUT.h"
#include "Background.h"

Background::Background()
{
	InitBackground();
}

Background::~Background()
{
}

void Background::InitBackground()
{
	bVisible = true;

	RECT rt;
	rt.left = 0;
	rt.right = STAGE_WIDTH;
	rt.top = 0;
	rt.bottom = STAGE_HEIGHT;

	SetRect(rt);

	SetSpeedX(10.0f);
}

void Background::MoveBackground()
{
	vPosition.x -= fSpeedX;

	if (vPosition.x <= -STAGE_WIDTH)
	{
		vPosition.x = STAGE_WIDTH;
	}
}