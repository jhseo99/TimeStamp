#include "stdafx.h"

GaTimer GaTimer::singleton;

GaTimer::GaTimer()
{
	nInitFPS = 80;
	realFPS = 0;
	realFPSCount = 0;
	fRealFPSTime = 0.0f;
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
	fRealFPSTime += fDelta;

	if (fRealFPSTime >= 1)
	{
		realFPS = realFPSCount / fRealFPSTime;
		realFPSCount = 0;
		fRealFPSTime = 0;
	}

	dwLastFrame = dwCurTimer;

	fAnimationTime += fDelta;

	if (fAnimationTime >= fOneFrameTime)
	{
		fAnimationTime = 0;
		++nCurFrame;
		++dwAbsoluteTime;
		if (nCurFrame == nInitFPS)
		{
			nCurFrame = 0;
		}
	}
}

DWORD GaTimer::GetRand(DWORD scope)
{
	return rand() % scope;
}