#pragma once
#include "AimObject.h"
#include "MiniSplit.h"

#define E_SPLIT_WIDTH 320
#define E_SPLIT_HEIGHT 250

#define ANI_MOVE 4

#define SPLIT_NUM 2

class EnemySplit
	:public AimObject
{
public:
	EnemySplit();
	~EnemySplit();

private:
	MiniSplit* pMiniSplit[SPLIT_NUM];

	RECT rtMove[ANI_MOVE];
	int AniMoveCount;
	int AniCurMove;

	float lastFrame;

public:
	void InitEnemySplit();
	void SetAniRect();
	void AniMove();
	void Process(Player* pPlayer);
	void DieSystem(Player* pPlayer);
	void SplitSystem(Player* pPlayer);

public:
	MiniSplit* GetMiniSplit(int num) { return pMiniSplit[num]; }
};
