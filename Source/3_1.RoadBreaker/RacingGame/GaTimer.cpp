#include "stdafx.h"

GaTimer GaTimer::singleton;

GaTimer::GaTimer()
{
	nInitFPS = 80;
	realFPS = 0;
	realFPSCount = 0;
	realFPSTime = 0.0f;
	fAnimationTime = 0.0f;
	dwAbsoluteTime = 0;
	fOneFrameTime = 1 / (float)nInitFPS;
	srand(time(NULL));
}

GaTimer::~GaTimer()
{
}

void GaTimer::Update()
{
	DWORD dwCurTimer = timeGetTime();
	float fDelta = (float)(dwCurTimer - dwLastFrame) * 0.001;

	++realFPSCount;
	realFPSTime += fDelta;

	if (realFPSTime >= 1)
	{
		realFPS = realFPSCount / realFPSTime;
		realFPSCount = 0;
		realFPSTime = 0;
	}

	dwLastFrame = dwCurTimer;

	fAnimationTime += fDelta;
	
	if (fAnimationTime >= fOneFrameTime)
	{
		fAnimationTime = 0;
		++ncurFrame;
		++dwAbsoluteTime;
		if (ncurFrame == nInitFPS)
		{
			ncurFrame = 0;
		}
	}
}