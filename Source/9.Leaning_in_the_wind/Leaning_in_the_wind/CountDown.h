#pragma once
class CountDown
	:public RenderObject
{
public:
	CountDown();
	CountDown(LPDIRECT3DDEVICE9 pd3dDevice);
	~CountDown();

private:
	float fStartTime;

public:
	void Init();
	void Process();

public:
	float GetStartTime() { return fStartTime; }
	void SetStartTime(float time) { fStartTime = time; }
};

