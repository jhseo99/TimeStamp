#include "DXUT.h"
#include "EnemyDash.h"


EnemyDash::EnemyDash()
{
	InitEnemyDash();
}


EnemyDash::~EnemyDash()
{
}

void EnemyDash::InitEnemyDash()
{
	RECT rt;
	rt.left = 0;
	rt.right = E_DASH_WIDTH;
	rt.top = 0;
	rt.bottom = E_DASH_HEIGHT;
	SetRect(rt);

	AniMoveCount = 0;
	AniCurMove = 0;

	lastFrame = 0;

	fHp = 5.0f;

	SetSpeed(15.0f);

	SetAniRect();
}

void EnemyDash::Process()
{
	if (bVisible)
	{
		UpdateCollision(57, 222, 35, 42);
		HitSystem(10.0f);
		Move();
		AniMove();
	}
	Die();
}

void EnemyDash::AniMove()
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

void EnemyDash::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[AniMoveCount].left = i * E_DASH_WIDTH;
		rtMove[AniMoveCount].right = rtMove[AniMoveCount].left + E_DASH_WIDTH;
		rtMove[AniMoveCount].top = 0;
		rtMove[AniMoveCount].bottom = E_DASH_HEIGHT;
		AniMoveCount++;
	}
}