#include "stdafx.h"

GaTimer GaTimer::singleton;

GaTimer::GaTimer(void)
{
	nInitFPS = 80;
	realFPS = 0;
	realFPSCount = 0;
	fRealFPSTime = 0.0f;
	fAnimaionTime = 0.0f;
	dwAbsoluteFrame = 0;
	fOneFrameTime = 1 / (float)nInitFPS;
	srand(time(NULL));
}

GaTimer::~GaTimer(void)
{
}

void GaTimer::Update()
{
	DWORD dwCurTimer = timeGetTime();
	float fDelta = (float)(dwCurTimer - dwLastFrame) * 0.001;

	++realFPSCount;
	fRealFPSTime += fDelta;
	if (fRealFPSTime >= 1)
	{
		realFPS = realFPSCount / fRealFPSTime;
		realFPSCount = 0;
		fRealFPSTime = 0.0f;
	}

	dwLastFrame = dwCurTimer;

	fAnimaionTime += fDelta;

	if (fAnimaionTime >= fOneFrameTime)
	{
		fAnimaionTime = 0;
		++nCurFrame;
		++dwAbsoluteFrame;
		if (nCurFrame == nInitFPS)
		{
			nCurFrame = 0;
		}
	}
}

void GaTimer::Timer()
{
	DWORD dwCurTimer = timeGetTime();
	float fDelta = (float)(dwCurTimer - dwLastTime) * 0.001;

	if (dwLastTime == 0)
	{
		fDelta = 0;
	}

	fCurrentTime += fDelta;

	dwLastTime = dwCurTimer;
}


DWORD GaTimer::GetRand(DWORD scope, DWORD start)
{
	return (rand() % scope) + start;
}