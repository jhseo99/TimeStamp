#pragma once

class GaTimer
{
public:
	~GaTimer();

	static GaTimer* Instance() { return &singleton; }

private:
	GaTimer();

	static GaTimer singleton;

	UINT nInitFPS;
	UINT realFPSCount;
	UINT realFPS;
	float fRealFPSTime;
	UINT nCurFrame;
	DWORD dwLastFrame;
	float fAnimationTime;
	DWORD dwAbsoluteTime;
	float fOneFrameTime;
	float fCurrentTime;

public:
	void Update();
	
	float GetRealFPSTime() { return fRealFPSTime; }

	DWORD GetAbsoluteFrame() { return dwAbsoluteTime; }
	void SetAbsoluteFrame(float time) { dwAbsoluteTime = time; }

	DWORD GetRand(DWORD scope);
};

#define GATIMER() GaTimer::Instance()