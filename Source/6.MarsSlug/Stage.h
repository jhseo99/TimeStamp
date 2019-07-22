#pragma once
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "EnemyAim.h"
#include "EnemyDash.h"
#include "EnemySplit.h"

#define MAX_ENEMY 20 

class Stage
	:public Scene
{
public:
	Stage();
	~Stage();

protected:
	Background* pStage_1;
	Background* pStage_2;
	Background* pStone1;
	Background* pStone2;

	EnemyAim* pEnemyAim[MAX_ENEMY];
	int nCurEnemyAim;
	float fLastEnemyAim;

	EnemyDash* pEnemyDash[MAX_ENEMY];
	int nCurEnemyDash;
	float fLastEnemyDash;

	EnemySplit* pEnemySplit[MAX_ENEMY];
	int nCurEnemySplit;
	float fLastEnemySplit;

public:
	void CreateObject(LPDIRECT3DDEVICE9 pd3dDevice);
	void UpdateStage();
	void RenderStage(LPD3DXSPRITE pSprite);
	void KeyProc();
	void CollisionCheck(Object* pObject1, Object* pObject2);

public:
	void InitObject();
	void RespawnAim();
	void RespawnDash();
	void RespawnSplit();
};

