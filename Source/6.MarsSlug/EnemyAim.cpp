#include "DXUT.h"
#include "EnemyAim.h"


EnemyAim::EnemyAim()
{
	InitEnemyAim();
}


EnemyAim::~EnemyAim()
{
}

void EnemyAim::InitEnemyAim()
{
	RECT rt;
	rt.left = 0;
	rt.right = E_AIM_WIDTH;
	rt.top = 0;
	rt.bottom = E_AIM_HEIGHT;
	SetRect(rt);

	SetSpeedX(-2.0f);
	SetSpeedY(0);

	AniMoveCount = 0;
	AniCurMove = 0;

	lastFrame = 0;

	fHp = 3.0f;

	SetAniRect();
	InitAimObject();
	CreateBullet(20, 20);
}

void EnemyAim::Process(Player* pPlayer)
{
	if (bVisible)
	{
		UpdateCollision(32, 114, 22, 71);
		HitSystem(5.0f);
		Move();
		//AniMove();
		Shot(pPlayer, vPosition.x + 25, vPosition.y + 55, 1.0f);
	}
	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBullet[i]->Move(true);
	}
	Die();
}

void EnemyAim::AniMove()
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

void EnemyAim::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[AniMoveCount].left = i * E_AIM_WIDTH;
		rtMove[AniMoveCount].right = rtMove[AniMoveCount].left + E_AIM_WIDTH;
		rtMove[AniMoveCount].top = 0;
		rtMove[AniMoveCount].bottom = E_AIM_HEIGHT;
		AniMoveCount++;
	}
}