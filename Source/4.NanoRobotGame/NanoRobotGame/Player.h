#pragma once

#define ANICOUNT 15

class Player
	:public Object
{
public:
	Player();
	Player(LPDIRECT3DTEXTURE9 texture);
	~Player();

	enum MotionState{NORMAL, UP, DOWN, LEFT, RIGHT};

private:
	MotionState motion;
	int AniCurCount;
	RECT AniRect[ANICOUNT];
	float fMoveSpeed;
	int nMissilePointX;
	int nMissilePointY;
	int nMissileCount;
	int nCurrentShoot;
	Missile* m_pMissile[100];

public:
	virtual void Create();
	virtual void Update();

public:
	void SetAniState(MotionState state) { motion = state; }
	void SetMotion(MotionState state);
	void AniDown();
	void AniUp();
	void AniNormal();

	void Move(MotionState state);

	void CreateMissile();
	void Shot(DWORD absoluteFrame);

	Missile* GetMissile(int num) { return m_pMissile[num]; }
};

