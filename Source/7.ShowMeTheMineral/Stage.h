#pragma once
#include "Object.h"
#include "BackGround.h"
#include "Player.h"
#include "Stone.h"
#include "Matt.h"
#include "James.h"
#include "Obstacle.h"
#include "Boris.h"
#include "Cedric.h"
#include "Item.h"
#include "HpUp.h"
#include "Missile.h"
#include "MissileThree.h"
#include "AimMissile.h"
#include "Bomb.h"
#include "GunUp.h"
#include "SpeedUp.h"
#include "AddOnPlus.h"
#include "John.h"
#include "Chris.h"
#include "Richard.h"
#include "Herrald.h"

#define MAX_HP 5
#define MAX_ENEMY 30

class Stage
{
public:
	Stage();
	~Stage();

private:
	Object* pStage1Water;
	Object* pStage2Water;

	BackGround* pStage1_1_1;
	BackGround* pStage1_1_2;
	BackGround* pStage1_2_1;
	BackGround* pStage1_2_2;
	BackGround* pStage1_3_1;
	BackGround* pStage1_3_2;

	Player* pPlayer;

	Object* pUI;
	Object* pPlayerHP[MAX_HP];
	Object* pPlayerHit;

	Stone* pStone;
	float fStoneTime;

	Obstacle *pObstacle;
	float fObstacleTime;

	Matt* pMatt[MAX_ENEMY];
	float fMattTime;
	int nMattCount;

	James* pJames[MAX_ENEMY];
	float fJameTime;
	int nJameCount;

	Boris* pBoris;
	Cedric* pCedric;

	Item* pItem;
	float fItemTime;

	John* pJohn[MAX_ENEMY];
	float fJohnTime;
	int nJohnCount;

	Chris* pChris[MAX_ENEMY];
	float fChrisTime;
	int nChrisCount;

	Richard* pRichard;
	Herrald* pHerrald;

public:
	void Create();
	void Update();
	void Render();
	void KeyProc();

	void CollsionCheck(Object* pObject1, Object* pObject2, RECT* rtCollision1, RECT* rtCollision2);
	void CollsionCheck(Object* pObject1, Object* pObject2, bool bItem);

public:
	void Stage1Update();
	void Stage1Render();

	void Stage2Update();
	void Stage2Render();

public:
	void StoneRespawn();
	void StoneUpdate();

	void ObstacleRespawn();
	void ObstacleUpdate();

	void ItemRespawn();
	void ItemUpdate();

	void MattRespawn(float fTime);
	void MattUpdate();

	void JamesRespawn(float fTime);
	void JamesUpdate();

	void BorisUpdate();
	void CedricUpdate();

	void JohnRespawn(float fTime);
	void JohnUpdate();

	void ChrisRespawn(float fTime);
	void ChrisUpdate();

	void RichardUpdate();
	void HerraldUpdate();
};

