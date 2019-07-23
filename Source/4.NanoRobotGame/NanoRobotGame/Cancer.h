#pragma once

#define CANCER_MOVE 20
#define CANCER_DIE 8

class Cancer
	:public Enemy
{
public:
	Cancer();
	Cancer(LPDIRECT3DTEXTURE9 texture);
	~Cancer();

private:
	MotionState motion;
	int AniCurCount;
	RECT AniRect[CANCER_MOVE];
	int AniCount;
	int AniCurDieCount;
	RECT DieRect[CANCER_DIE];
	int AniDieCount;
	bool bClear;

public:
	virtual void Create();

public:
	virtual void AniMove();
	virtual void AniDie();
	void Animation();

public:
	void SetAniState(MotionState state) { motion = state; }
	bool GetClear() { return bClear; }
	void SetClear(bool clear) { bClear = clear; }
};

