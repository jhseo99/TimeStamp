#pragma once
class GaTimer
{
public:
	GaTimer();
	~GaTimer();

	static GaTimer* Instance() { return &singleton; }

private:
	static GaTimer singleton;

	DWORD dwLastTime;
	float fCurrentTime;

public:
	void Init();
	void Update();

public:
	float GetTimer() { return fCurrentTime; }
	void InitTimer() { Init(); }
};

#define GATIMER() GaTimer::Instance()