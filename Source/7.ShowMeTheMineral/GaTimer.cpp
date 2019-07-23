#include "DXUT.h"
#include "GaTimer.h"
#include <time.h>

GaTimer GaTimer::singleton;

GaTimer::GaTimer()
{
}


GaTimer::~GaTimer()
{
}

void GaTimer::Create()
{
	dwLastTime = 0;
	fCurrentTime = 0.0f;

	srand((unsigned int)time(NULL));
}

void GaTimer::Update()
{
	DWORD dwCurrentTime = timeGetTime();
	float fDelta = (float)(dwCurrentTime - dwLastTime) * 0.001f;

	if (dwLastTime == 0)
	{
		fDelta = 0;
	}

	fCurrentTime += fDelta;
	dwLastTime = dwCurrentTime;
}