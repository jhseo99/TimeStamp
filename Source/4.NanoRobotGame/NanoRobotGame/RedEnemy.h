#pragma once

#define RED_MOVE 36
#define RED_DIE 8

class RedEnemy
	:public Enemy
{
public:
	RedEnemy();
	RedEnemy(LPDIRECT3DTEXTURE9 texture);
	~RedEnemy();

private:
	MotionState motion;
	int AniCurCount;
	RECT AniRect[RED_MOVE];
	int AniCount;
	int AniCurDieCount;
	RECT DieRect[RED_DIE];
	int AniDieCount;

public:
	virtual void Create();

public:
	virtual void AniMove();
	virtual void AniDie();
	void Animation();

public:
	void SetAniState(MotionState state) { motion = state; }
};

