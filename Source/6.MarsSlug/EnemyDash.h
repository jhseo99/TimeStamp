#pragma once
#include "DashObject.h"
#include "Player.h"

#define E_DASH_WIDTH 300
#define E_DASH_HEIGHT 110

#define ANI_MOVE 4

class EnemyDash
	:public DashObject
{
public:
	EnemyDash();
	~EnemyDash();

private:
	RECT rtMove[ANI_MOVE];
	int AniMoveCount;
	int AniCurMove;

	float lastFrame;

public:
	void InitEnemyDash();
	void SetAniRect();
	void AniMove();
	void Process();
};

