#pragma once

class Enemy
	:public Object
{
public:
	Enemy();
	~Enemy();

	enum MotionState{ UP, DOWN, LEFT, RIGHT, DIE };

protected:
	float fMoveSpeed;
	bool bDie;
	int lastFrame;

public:
	virtual void Create() = 0;

public:
	virtual void AniMove();
	
	virtual void Move(MotionState state);
};
