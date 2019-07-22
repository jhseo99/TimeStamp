#pragma once

#define VIRUS_MOVE 36
#define VIRUS_DIE 8

class Virus
	:public Enemy
{
public:
	Virus();
	Virus(LPDIRECT3DTEXTURE9 texture);
	~Virus();

private:
	MotionState motion;
	int AniCurCount;
	RECT AniRect[VIRUS_MOVE];
	int AniCount;
	int RandNum;
	int AniCurDieCount;
	RECT DieRect[VIRUS_DIE];
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
