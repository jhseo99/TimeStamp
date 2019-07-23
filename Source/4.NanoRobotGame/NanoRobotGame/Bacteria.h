#pragma once

#define BACTERIA_MOVE 2
#define BACTERIA_DIE 8

class Bacteria
	:public Enemy
{
public:
	Bacteria();
	Bacteria(LPDIRECT3DTEXTURE9 texture);
	~Bacteria();

private:
	MotionState motion;
	int RandNum;
	int AniCurCount;
	RECT AniRect[BACTERIA_MOVE];
	int AniCount;
	int AniCurDieCount;
	RECT DieRect[WHITE_DIE];
	int AniDieCount;

public:
	virtual void Create();

public:
	virtual void AniMove();
	virtual void AniDie();
	void Animation();

	int GetRandNum() { return RandNum; }
	void SetRandNum(int num) { RandNum = num; }

public:
	void SetAniState(MotionState state) { motion = state; }
};