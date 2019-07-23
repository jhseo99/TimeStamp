#include "stdafx.h"

LandRover::LandRover()
{
}

LandRover::LandRover(LPDIRECT3DTEXTURE9 texture)
{
	Create();
	SetTexture(texture);
}

LandRover::~LandRover()
{
}

void LandRover::Create()
{
	nFrameWidth = 120;
	nFrameHeight = 220;
	nFrameSpeed = 10;
	fSpeed = 0.0f;
	fAccel = 1.0f;
	fPlusSpeed = 0.0f;
	fDistance = 0.0f;
	bBoost = false;
	bVisible = true;
	bHit = false;
	bGoal = false;

	RECT rt;
	rt.left = 0;
	rt.right = nFrameWidth;
	rt.top = 0;
	rt.bottom = nFrameHeight;

	SetRect(rt);

	SetPosition(-350, -400, 0);
}

void LandRover::Process()
{
	fDistance += fSpeed;

	if (bHit)
	{
		vPostion.x += (vDirection.x * 10.0f);
		fAccel -= 5.0f;
		fSpeed -= 5.0f;

		bHit = false;
	}
	if (fSpeed < 0)
	{
		fSpeed = 0;
		fAccel = 0.0f;
	}
	if (fAccel <= 0)
	{
		fAccel = 0.0f;
	}

	if (vPostion.x >= -300)
	{
		vPostion.x = -300;
	}
	if (vPostion.x <= -630)
	{
		vPostion.x = -630;
	}
}

void LandRover::Move(MotionState state)
{
	switch (state)
	{
	case MotionState::UP:
		fAccel += 0.1f;
		fSpeed = (fAccel + fPlusSpeed);

		if (fAccel > 40)
		{
			fAccel = 40;
		}
		if (fSpeed >= 40 && bBoost == false)
		{
			fSpeed = 40.0f;
		}
		break;
	case MotionState::LEFT:
		vPostion.x += 10.0f;
		if (vPostion.x >= -300)
		{
			vPostion.x = -300;
		}
		break;
	case MotionState::RIGHT:
		vPostion.x -= 10.0f;
		if (vPostion.x <= -630)
		{
			vPostion.x = -630;
		}
		break;
	default:
		break;
	}
}

void LandRover::Break()
{
	fSpeed = fAccel;

	fAccel--;
}