#pragma once
#include "Object.h"
#include "Bullet.h"

#define PLAYER_WIDTH 160
#define PLAYER_HEIGHT 180

#define ANI_MOVE 7
#define ANI_CHANGE 3

#define MAX_BULLET 50

class Player
	:public Object
{
public:
	Player();
	~Player();

	static Player* Instance() { return &singleton; }

	enum MoveState{LEFT, RIGHT, UP, DOWN};
	enum GunDirection{IDLE, 
					  BACK, 
					  LITTLETOP, TOP, 
					  LITTLEBOTTOM, BOTTOM, 
					  CHANGELT, CHANGET, 
					  CHANGELB, CHANGEB};

private:
	static Player singleton;

	Bullet* pBullet[MAX_BULLET];
	float fLastBullet;
	int nCurBullet;

	MoveState moveState;
	GunDirection gunDirection;

	float fSpeed;
	int AniCount;

	RECT rtIdle[ANI_MOVE];
	int AniIdleCount;
	int AniCurIdle;

	RECT rtBack[ANI_MOVE];
	int AniCurBack;

	RECT rtLittleTop[ANI_MOVE];
	int AniLittleTopCount;
	int AniCurLittleTop;

	RECT rtChangeLT[ANI_CHANGE];
	int AniChangeLTCount;
	int AniCurChangeLT;

	RECT rtTop[ANI_MOVE];
	int AniTopCount;
	int AniCurTop;

	RECT rtChangeT[ANI_CHANGE];
	int AniChangeTCount;
	int AniCurChangeT;

	RECT rtLittleBottom[ANI_MOVE];
	int AniLittleBottomCount;
	int AniCurLittleBottom;

	RECT rtChangeLB[ANI_CHANGE];
	int AniChangeLBCount;
	int AniCurChangeLB;

	RECT rtBottom[ANI_MOVE];
	int AniBottomCount;
	int AniCurBottom;

	RECT rtChangeB[ANI_CHANGE];
	int AniChangeBCount;
	int AniCurChangeB;

	float lastFrame;
	float lastHit;

public:
	void InitPlayer();
	void SetAniRect();
	void CreateBullet();
	void Move();
	void Shot();
	void Hit();
	void HitAni();
	void Process();

public:
	void AniIdle();
	void AniBack();
	void AniLittleTop();
	void AniChangeLT();
	void AniTop();
	void AniChangeT();
	void AniLittleBottom();
	void AniChangeLB();
	void AniBottom();
	void AniChangeB();

public:
	Bullet* GetBullet(int num) { return pBullet[num]; }
	void SetMoveState(MoveState state) { moveState = state; }
	void SetGunState(GunDirection direction) { gunDirection = direction; }
};

#define PLAYER() Player::Instance()