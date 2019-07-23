#pragma once

class GaTimer
{
public:
	~GaTimer(void);

	static GaTimer* Instance() { return &singleton; }

private:
	GaTimer(void);

	static GaTimer singleton;

	UINT nInitFPS;
	UINT realFPSCount;
	UINT realFPS;
	float fRealFPSTime;
	UINT nCurFrame;
	DWORD dwLastFrame;
	DWORD dwLastTime;
	float fAnimaionTime;
	DWORD dwAbsoluteFrame;
	float fOneFrameTime;
	float fCurrentTime;

public:
	void Update();
	void Timer();

	DWORD GetAbsoluteFrame() { return dwAbsoluteFrame; }
	void SetAbsoliteFrame(float _time) { dwAbsoluteFrame = _time; }

	DWORD GetRand(DWORD scope, DWORD start);

	float GetGameTime() { return fCurrentTime; }
	void SetGameTime(float gametime) { fCurrentTime = gametime; }
};

#define GATIMER() GaTimer::Instance()