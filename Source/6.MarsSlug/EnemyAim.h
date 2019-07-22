#pragma once
#include "AimObject.h"

#define E_AIM_WIDTH 170
#define E_AIM_HEIGHT 140

#define ANI_MOVE 10

class EnemyAim
	:public AimObject
{
public:
	EnemyAim();
	~EnemyAim();

private:
	RECT rtMove[ANI_MOVE];
	int AniMoveCount;
	int AniCurMove;

	float lastFrame;

public:
	void InitEnemyAim();
	void SetAniRect();
	void AniMove();
	void Process(Player* pPlayer);
};

