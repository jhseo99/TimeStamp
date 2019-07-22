#include "DXUT.h"
#include "EnemySplit.h"


EnemySplit::EnemySplit()
{
	InitEnemySplit();
}

EnemySplit::~EnemySplit()
{
}

void EnemySplit::InitEnemySplit()
{
	RECT rt;
	rt.left = 0;
	rt.right = E_SPLIT_WIDTH;
	rt.top = 0;
	rt.bottom = E_SPLIT_HEIGHT;
	SetRect(rt);

	SetSpeedX(-1.5f);
	SetSpeedY(0);

	AniMoveCount = 0;
	AniCurMove = 0;

	lastFrame = 0;

	fHp = 10.0f;

	for (int i = 0; i < SPLIT_NUM; i++)
	{
		pMiniSplit[i] = new MiniSplit;
	}

	SetAniRect();
	InitAimObject();
	CreateBullet(40, 40);
}

void EnemySplit::Process(Player* pPlayer)
{
	if (bVisible)
	{
		UpdateCollision(30, 138, 102, 124);
		HitSystem(15.0f);
		Move();
		AniMove();
		Shot(pPlayer, vPosition.x + 22, vPosition.y + 180, 1.0f);
	}
	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBullet[i]->Move(true);
	}
	Die();
	DieSystem(pPlayer);
	for (int i = 0; i < SPLIT_NUM; i++)
	{
		pMiniSplit[i]->Process();
	}
}

void EnemySplit::AniMove()
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

void EnemySplit::SetAniRect()
{
	for (int i = 0; i < ANI_MOVE; i++)
	{
		rtMove[AniMoveCount].left = i * E_SPLIT_WIDTH;
		rtMove[AniMoveCount].right = rtMove[AniMoveCount].left + E_SPLIT_WIDTH;
		rtMove[AniMoveCount].top = 0;
		rtMove[AniMoveCount].bottom = E_SPLIT_HEIGHT;
		AniMoveCount++;
	}
}

void EnemySplit::DieSystem(Player* pPlayer)
{
	if (GetSplit())
	{
		SplitSystem(pPlayer);
		SetSplit(false);
	}
}

void EnemySplit::SplitSystem(Player* pPlayer)
{
	for (int i = 0; i < SPLIT_NUM; i++)
	{
		D3DXVECTOR3 vPos;
		vPos.x = vPosition.x + 50;
		vPos.y = vPosition.y + 30 + (i * 70);
		vPos.z = 0;

		pMiniSplit[i]->SetVisible(true);
		pMiniSplit[i]->SetPosition(vPos);
		pMiniSplit[i]->Dash(pPlayer);
	}
}