#pragma once
class Fire
	:public CollisionObject
{
public:
	Fire();
	Fire(LPDIRECT3DDEVICE9 pd3dDevice);
	~Fire();

private:
	float fFrameTime;
	int nCurrentFrame;

public:
	void InitFire();
	void Animation();

public:
	float GetFrameTime() { return fFrameTime; }
	void SetFrameTime(float time) { fFrameTime = time; }

	int GetCurrentFrame() { return nCurrentFrame; }
	void SetCurrentFrame(int frame) { nCurrentFrame = frame; }
};

