#pragma once
#include "DashObject.h"
#include "Player.h"

#define E_MINI_SPLIT_WIDHT 60
#define E_MINI_SPLIT_HEIGHT 40

#define ANI_MOVE 4

class MiniSplit
	:public DashObject
{
public:
	MiniSplit();
	~MiniSplit();

private:
	RECT rtMove[ANI_MOVE];
	int AniMoveCount;
	int AniCurMove;

	float lastFrame;

public:
	void InitMiniSplit();
	void SetAniRect();
	void AniMove();
	void Process();
};

