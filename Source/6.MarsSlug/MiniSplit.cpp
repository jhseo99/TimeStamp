#include "DXUT.h"
#include "MiniSplit.h"


MiniSplit::MiniSplit()
{
	InitMiniSplit();
}


MiniSplit::~MiniSplit()
{
}

void MiniSplit::InitMiniSplit()
{
	RECT rt;
	rt.left = 0;
	rt.right = E_MINI_SPLIT_WIDHT;
	rt.top = 0;
	rt.bottom = E_MINI_SPLIT_HEIGHT;
	SetRect(rt);

	AniMoveCount = 0;
	AniCurMove = 0;

	lastFrame = 0;

	fHp = 5.0f;

	SetSpeed(10.0f);

	SetAniRect();
}

void MiniSplit::Process()
{
	if (bVisible)
	{
		UpdateCollision(7, 40, 11, 21);
		HitSystem(10.0f);
		Move();
		//AniMove();
	}
	Die();
}

void MiniSplit::AniMove()
{
	if (DXUTGetTime() - lastFrame > 0.1f)
	{
		SetRect(rtMove[AniCurMove++]);
		lastFrame = DXUTGetTime();
	}
	if (AniCurMove >= ANI_MOVE)
	{
		AniCurMove = 0;
	}
}

void MiniSplit::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[AniMoveCount].left = i * E_MINI_SPLIT_WIDHT;
		rtMove[AniMoveCount].right = rtMove[AniMoveCount].left + E_MINI_SPLIT_WIDHT;
		rtMove[AniMoveCount].top = 0;
		rtMove[AniMoveCount].bottom = E_MINI_SPLIT_HEIGHT;
		AniMoveCount++;
	}
}