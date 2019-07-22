#pragma once
#include "Enemy.h"
#include "Effect.h"

#define MATT_WIDTH 120
#define MATT_HEIGHT 100
#define ANI_MOVE 3

class Matt
	:public Enemy
{
public:
	Matt();
	Matt(LPDIRECT3DTEXTURE9 texture);
	~Matt();

	Effect* pBombEffect;

private:
	D3DXVECTOR3 vDirect;

	RECT rtMove[ANI_MOVE];
	float fAniMoveTime;
	int nMoveCount;
	int nCurrentMove;

public:
	void Create();
	void Update(Player* pPlayer);
	void Move();
	void Aim(Player* pPlayer);
	void SetAniRect();
	void AniMove();
};

