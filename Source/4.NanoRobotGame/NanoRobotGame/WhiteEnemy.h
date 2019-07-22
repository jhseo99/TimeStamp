#pragma once

#define WHITE_MOVE 8
#define WHITE_DIE 8

class WhiteEnemy
	:public Enemy
{
public:
	WhiteEnemy();
	WhiteEnemy(LPDIRECT3DTEXTURE9 texture);
	~WhiteEnemy();

private:
	MotionState motion;
	int RandNum;
	int AniCurCount;
	RECT AniRect[WHITE_MOVE];
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