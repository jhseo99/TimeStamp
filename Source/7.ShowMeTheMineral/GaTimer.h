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
	void Create();
	void Update();

public:
	float GetTimer() { return fCurrentTime; }
	void SetTimer() { Create(); }
};

#define GATIMER() GaTimer::Instance()