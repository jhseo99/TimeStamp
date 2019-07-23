#pragma once

class Enemy
	:public Object
{
public:
	Enemy();
	Enemy(LPDIRECT3DTEXTURE9 texture);
	~Enemy();

	enum MotionState{ NORMAL, UP, LEFT, RIGHT, DIE };

private:
	MotionState motion;

	DWORD CurrentDirectionFrame;
	DWORD CurrentSpeedFrame;
	float fDistance;
	bool bGoal;
	int RandNum;
	int RandSpeed;

public:
	virtual void Create();

	void Move(DWORD absoluteFrame);

	float GetDistance() { return fDistance; }

	bool GetGoal() { return bGoal; }
	void SetGoal(bool goal) { bGoal = goal; }

	MotionState GetMotion() { return motion; }
	void SetMotion(MotionState _motion) { motion = _motion; }
};