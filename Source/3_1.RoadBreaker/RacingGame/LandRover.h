#pragma once

class LandRover
	:public Object
{
public:
	LandRover();
	LandRover(LPDIRECT3DTEXTURE9 texture);
	~LandRover();

	enum MotionState{NORMAL, UP, LEFT, RIGHT, DIE};

private:
	MotionState motion;

	float fDistance;
	float fAccel;
	float fPlusSpeed;
	bool bBoost;
	bool bGoal;

public:
	virtual void Create();
	
	void Process();
	void Move(MotionState state);
	void Break();

	float GetDistance() { return fDistance; }

	bool GetGoal() { return bGoal; }
	void SetGoal(bool goal) { bGoal = goal; }

	MotionState GetMotion() { return motion; }
	void SetMotion(MotionState _motion) { motion = _motion; }
};