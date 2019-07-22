#include "DXUT.h"
#include "SDKmisc.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "GaTimer.h"
#include "SoundManager.h"

Stage::Stage()
{
	Create();
}


Stage::~Stage()
{
}

void Stage::Create()
{
	pStage1Water = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE1_WATER), 1024, 768, 0, 0);
	pStage2Water = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE2_WATER), 1024, 768, 0, 0);

	pStage1_1_1 = new BackGround(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE1_L1_1), 0, 0);
	pStage1_1_2 = new BackGround(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE1_L1_2), 1024, 0);
	pStage1_2_2 = new BackGround(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE1_L2_1), 0, 0);
	pStage1_2_1 = new BackGround(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE1_L2_2), 1024, 0);
	pStage1_3_1 = new BackGround(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE1_L3_1), 0, 0);
	pStage1_3_2 = new BackGround(OBJMANAGER()->GetTexture(GaBase::TextureID::STAGE1_L3_2), 1024, 0);

	pPlayer = new Player(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER));

	pUI = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::UI), 340, 130, 0, 0);
	for (int i = 0; i < MAX_HP; i++)
	{
		pPlayerHP[i] = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER_HP), 25, 35, 16 + (i * 27), 17);
	}
	pPlayerHit = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::PLAYER_HIT), 1024, 768, 0, 0);
	pPlayerHit->SetVisible(false);

	pStone = new Stone;
	fStoneTime = 0.0f;

	pObstacle = new Obstacle;
	fObstacleTime = 0.0f;

	pItem = new Item;
	fItemTime = 0.0f;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pMatt[i] = new Matt(OBJMANAGER()->GetTexture(GaBase::TextureID::MATT));
		pJames[i] = new James(OBJMANAGER()->GetTexture(GaBase::TextureID::JAMES));
		pJohn[i] = new John(OBJMANAGER()->GetTexture(GaBase::TextureID::JOHN));
		pChris[i] = new Chris(OBJMANAGER()->GetTexture(GaBase::TextureID::CHRIS));
	}
	
	fMattTime = 0.0f;
	nMattCount = 0;

	fJameTime = 0.0f;
	nJameCount = 0;

	fJohnTime = 0.0f;
	nJohnCount = 0;

	fChrisTime = 0.0f;
	nChrisCount = 0;

	pBoris = new Boris(OBJMANAGER()->GetTexture(GaBase::TextureID::BORIS));
	pCedric = new Cedric(OBJMANAGER()->GetTexture(GaBase::TextureID::CEDRIC));
	pRichard = new Richard(OBJMANAGER()->GetTexture(GaBase::TextureID::RICHARD));
	pHerrald = new Herrald(OBJMANAGER()->GetTexture(GaBase::TextureID::HERRALD));

	GATIMER()->SetTimer();
}

void Stage::KeyProc()
{
	bool bKeyDown = false; 

	if (GetAsyncKeyState(VK_LEFT))
	{
		pPlayer->SetMoveState(Player::MoveState::LEFT);
		pPlayer->Move();
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		pPlayer->SetMoveState(Player::MoveState::RIGHT);
		pPlayer->Move();
	}
	if (GetAsyncKeyState(VK_UP))
	{
		pPlayer->SetMoveState(Player::MoveState::UP);
		pPlayer->Move();
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		pPlayer->SetMoveState(Player::MoveState::DOWN);
		pPlayer->Move();
	}
	if (GetAsyncKeyState(VK_LCONTROL))
	{
		pPlayer->Shot();
	}
	if (GetAsyncKeyState('X') && !bKeyDown)
	{
		pPlayer->Bomb();
		bKeyDown = true;
	}
	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		pPlayer->SetPhenix(!pPlayer->GetPhenix());
		bKeyDown = true;
	}
	if (GetAsyncKeyState(VK_F2) && !bKeyDown)
	{
		pPlayer->SetGunState(Player::GunState::MISSILE_THREE);
		pPlayer->SetGunTime(GATIMER()->GetTimer());
		bKeyDown = true;
	}
	if (GetAsyncKeyState(VK_F3) && !bKeyDown)
	{
		pPlayer->SetGunState(Player::GunState::MISSILE_AIM);
		pPlayer->SetGunTime(GATIMER()->GetTimer());
		bKeyDown = true;
	}
	if (GetAsyncKeyState(VK_F4) && !bKeyDown)
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::MENU);
		Create();
		bKeyDown = true;
	}
	if (GetAsyncKeyState(VK_F5) && !bKeyDown)
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::STAGE1);
		Create();
		bKeyDown = true;
	}
	if (GetAsyncKeyState(VK_F6) && !bKeyDown)
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::STAGE2);
		Create();
		bKeyDown = true;
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::MENU);
		Create();
	}
}

void Stage::Update()
{
	GATIMER()->Update();

	KeyProc();
	pPlayer->Update();

	if (pPlayer->GetHitAni())
	{
		pPlayerHit->SetVisible(true);
	}
	else
	{
		pPlayerHit->SetVisible(false);
	}

	switch (OBJMANAGER()->GetScene())
	{
	case ObjectManager::SceneState::STAGE1:
		Stage1Update();
		break;
	case ObjectManager::SceneState::STAGE2:
		Stage2Update();
		break;
	default:
		break;
	}

	if (pPlayer->GetHp() <= 0)
	{
		Create();
		OBJMANAGER()->SetScene(ObjectManager::SceneState::END);
	}
}

void Stage::Render()
{
	switch (OBJMANAGER()->GetScene())
	{
	case ObjectManager::SceneState::STAGE1:
		Stage1Render();
		break;
	case ObjectManager::SceneState::STAGE2:
		Stage2Render();
		break;
	default:
		break;
	}

	pUI->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < (int)pPlayer->GetHp(); i++)
	{
		pPlayerHP[i]->Render(OBJMANAGER()->GetSprite());
	}

	CDXUTTextHelper txtTimer(OBJMANAGER()->GetFontTime(), OBJMANAGER()->GetSprite(), 75);
	txtTimer.Begin();
	txtTimer.SetInsertionPos(450, 10);
	txtTimer.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
	txtTimer.DrawFormattedTextLine(L"%0.f", GATIMER()->GetTimer());
	txtTimer.End();

	CDXUTTextHelper txtStr(OBJMANAGER()->GetFontStr(), OBJMANAGER()->GetSprite(), 30);
	txtStr.Begin();
	txtStr.SetForegroundColor(D3DXCOLOR(0.8f, 0.7f, 0.2f, 1.0f));
	txtStr.SetInsertionPos(204, 18);
	txtStr.DrawFormattedTextLine(L"%0.f", pPlayer->GetDamage());
	txtStr.SetInsertionPos(278, 18);
	txtStr.DrawFormattedTextLine(L"%0.f", pPlayer->GetDefence());
	txtStr.SetInsertionPos(50, 95);
	txtStr.DrawFormattedTextLine(L"%d", pPlayer->GetBombCount());
	txtStr.SetInsertionPos(12, 56);
	txtStr.DrawFormattedTextLine(L"%d", OBJMANAGER()->GetScore());
	txtStr.End();

	pPlayer->pBombEffect->Render(OBJMANAGER()->GetSprite());
	pPlayerHit->Render(OBJMANAGER()->GetSprite());
}

void Stage::CollsionCheck(Object* pObject1, Object* pObject2, RECT* rtCollision1, RECT* rtCollision2)
{
	if (pObject1->GetVisible() && pObject2->GetVisible() &&
		!pObject1->GetHit() && !pObject2->GetHit())
	{
		if (rtCollision1->left >= rtCollision2->right ||
			rtCollision1->right <= rtCollision2->left ||
			rtCollision1->top >= rtCollision2->bottom ||
			rtCollision1->bottom <= rtCollision2->top)
		{
		}
		else
		{
			pObject1->SetHit(true);
			pObject2->SetHit(true);
		}
	}
}

void Stage::CollsionCheck(Object* pObject1, Object* pObject2, bool bItem)
{
	if (pObject1->GetVisible() && pObject2->GetVisible() &&
		!pObject1->GetHit() && !pObject2->GetHit())
	{
		if (pObject1->GetCollision()->left >= pObject2->GetCollision()->right ||
			pObject1->GetCollision()->right <= pObject2->GetCollision()->left ||
			pObject1->GetCollision()->top >= pObject2->GetCollision()->bottom ||
			pObject1->GetCollision()->bottom <= pObject2->GetCollision()->top)
		{
		}
		else
		{
			if (!bItem)
			{
				pObject1->SetHit(true);
			}
			pObject2->SetHit(true);
		}
	}
}

void Stage::Stage1Update()
{
	if (!pBoris->GetRespawn() && !pCedric->GetRespawn())
	{
		// BackGround
		pStage1_1_1->Move(0.5f, 1024);
		pStage1_1_2->Move(0.5f, 1024);
		pStage1_2_1->Move(2.0f, 1024);
		pStage1_2_2->Move(2.0f, 1024);
		pStage1_3_1->Move(8.0f, 1024);
		pStage1_3_2->Move(8.0f, 1024);

		// Stone
		StoneRespawn();

		// Obstacle
		ObstacleRespawn();
		
		if (!pBoris->GetDie())
		{
			// Matt
			MattRespawn(3.0f);

			// James
			JamesRespawn(5.0f);
		}
		if (pBoris->GetDie())
		{
			// Matt
			MattRespawn(1.0f);

			// James
			JamesRespawn(2.0f);
		}
	}
	ItemRespawn();
	ItemUpdate();

	StoneUpdate();
	ObstacleUpdate();
	MattUpdate();
	JamesUpdate();

	BorisUpdate();
	CedricUpdate();

	// Player
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		for (int j = 0; j < MAX_ENEMY; j++)
		{
			pPlayer->pAimMissile[i]->Aim(pMatt[j]);
			pPlayer->pAimMissile[i]->Aim(pJames[j]);
			pPlayer->pAimMissile[i]->Aim(pBoris);
			pPlayer->pAimMissile[i]->Aim(pCedric);
		}
	}
	if (pPlayer->GetBomb())
	{
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			pMatt[i]->SetVisible(false);
			for (int j = 0; j < JAMES_MAX_BULLET; j++)
			{
				pJames[i]->pBullet[j]->SetVisible(false);
			}
		}
		for (int i = 0; i < BORIS_MAX_BULLET; i++)
		{
			pBoris->pBullet[i]->SetVisible(false);
		}
		for (int i = 0; i < CEDRIC_SPLIT_BULLET; i++)
		{
			pCedric->pSplitBullet[i]->SetVisible(false);
		}
		for (int i = 0; i < CEDRIC_MAX_BULLET; i++)
		{
			pCedric->pBullet[i]->SetVisible(false);
		}
		pObstacle->SetVisible(false);
	}
	if (pCedric->GetDie() && !pCedric->GetRespawn())
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::STAGE2);
		fJohnTime = GATIMER()->GetTimer();
		fChrisTime = GATIMER()->GetTimer();
	}
}

void Stage::Stage1Render()
{
	pStage1_1_1->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_1_2->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_2_1->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_2_2->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_3_1->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_3_2->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStone->GetSprite()->SetTransform(pPlayer->GetCamera());

	pStage1Water->Render(OBJMANAGER()->GetSprite());

	pStage1_1_1->Render();
	pStage1_1_2->Render();
	pStage1_2_1->Render();
	pStage1_2_2->Render();

	pObstacle->Render(OBJMANAGER()->GetSprite());

	pPlayer->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < MAX_ADDON; i++)
	{
		pPlayer->pAddon[i]->Render(OBJMANAGER()->GetSprite());
		for (int j = 0; j < ADDON_BULLET; j++)
		{
			pPlayer->pAddon[i]->pBullet[j]->Render(OBJMANAGER()->GetSprite());
		}
	}
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		pPlayer->pBullet[i]->Render(OBJMANAGER()->GetSprite());
		pPlayer->pMissile[i]->Render(OBJMANAGER()->GetSprite());
		pPlayer->pAimMissile[i]->Render(OBJMANAGER()->GetSprite());
	}
	pPlayer->pFireEffect->Render(OBJMANAGER()->GetSprite());

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pMatt[i]->Render(OBJMANAGER()->GetSprite());
		pMatt[i]->pBombEffect->Render(OBJMANAGER()->GetSprite());
		pJames[i]->Render(OBJMANAGER()->GetSprite());
		pJames[i]->pBombEffect->Render(OBJMANAGER()->GetSprite());
		for (int j = 0; j < JAMES_MAX_BULLET; j++)
		{
			pJames[i]->pBullet[j]->Render(OBJMANAGER()->GetSprite());
		}
	}

	pBoris->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < BORIS_MAX_BULLET; i++)
	{
		pBoris->pBullet[i]->Render(OBJMANAGER()->GetSprite());
	}
	pBoris->pHpBar->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < (int)(pBoris->GetHp() / 10.0f); i++)
	{
		pBoris->pHp[i]->Render(OBJMANAGER()->GetSprite());
	}
	pBoris->pBombEffect->Render(OBJMANAGER()->GetSprite());

	pCedric->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < CEDRIC_SPLIT_BULLET; i++)
	{
		pCedric->pSplitBullet[i]->Render(OBJMANAGER()->GetSprite());
	}
	for (int i = 0; i < CEDRIC_MAX_BULLET; i++)
	{
		pCedric->pBullet[i]->Render(OBJMANAGER()->GetSprite());
	}
	pCedric->pHpBar->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < (int)(pCedric->GetHp() / 15.0f); i++)
	{
		pCedric->pHp[i]->Render(OBJMANAGER()->GetSprite());
	}
	pCedric->pBombEffect->Render(OBJMANAGER()->GetSprite());

	pItem->Render(OBJMANAGER()->GetSprite());

	pStage1_3_1->Render();
	pStage1_3_2->Render();
	pStone->Render();
}


void Stage::Stage2Update()
{
	if (!pRichard->GetRespawn() && !pHerrald->GetRespawn())
	{
		// BackGround
		pStage1_1_1->Move(0.5f, 1024);
		pStage1_1_2->Move(0.5f, 1024);
		pStage1_2_1->Move(2.0f, 1024);
		pStage1_2_2->Move(2.0f, 1024);
		pStage1_3_1->Move(8.0f, 1024);
		pStage1_3_2->Move(8.0f, 1024);

		// Stone
		StoneRespawn();

		// Obstacle
		ObstacleRespawn();

		if (!pRichard->GetDie())
		{
			// John
			JohnRespawn(5.0f);

			// Chris
			ChrisRespawn(7.0f);
		}
		if (pRichard->GetDie())
		{
			// Matt
			JohnRespawn(3.0f);

			// James
			ChrisRespawn(5.0f);
		}
	}
	ItemRespawn();
	ItemUpdate();

	StoneUpdate();
	ObstacleUpdate();
	JohnUpdate();
	ChrisUpdate();

	RichardUpdate();
	HerraldUpdate();

	// Player
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		for (int j = 0; j < MAX_ENEMY; j++)
		{
			pPlayer->pAimMissile[i]->Aim(pJohn[j]);
			pPlayer->pAimMissile[i]->Aim(pChris[j]);
			pPlayer->pAimMissile[i]->Aim(pRichard);
			pPlayer->pAimMissile[i]->Aim(pHerrald);
		}
	}
	if (pPlayer->GetBomb())
	{
		pObstacle->SetVisible(false);
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			for (int j = 0; j < JOHN_MAX_BULLET; j++)
			{
				pJohn[i]->pBullet[j]->SetVisible(false);
			}
			for (int j = 0; j < CHRIS_MAX_BULLET; j++)
			{
				pChris[i]->pBullet[j]->SetVisible(false);
			}
		}
		for (int i = 0; i < HERRALD_MAX_BULLET; i++)
		{
			pHerrald->pBullet1[i]->SetVisible(false);
			pHerrald->pBullet2[i]->SetVisible(false);
		}
	}
	if (pHerrald->GetDie() && !pHerrald->GetRespawn())

	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::END);
		Create();
	}
}

void Stage::Stage2Render()
{
	pStage1_1_1->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_1_2->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_2_1->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_2_2->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_3_1->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStage1_3_2->GetSprite()->SetTransform(pPlayer->GetCamera());
	pStone->GetSprite()->SetTransform(pPlayer->GetCamera());

	pStage2Water->Render(OBJMANAGER()->GetSprite());

	pStage1_1_1->Render();
	pStage1_1_2->Render();
	pStage1_2_1->Render();
	pStage1_2_2->Render();

	pObstacle->Render(OBJMANAGER()->GetSprite());

	pPlayer->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < MAX_ADDON; i++)
	{
		pPlayer->pAddon[i]->Render(OBJMANAGER()->GetSprite());
		for (int j = 0; j < ADDON_BULLET; j++)
		{
			pPlayer->pAddon[i]->pBullet[j]->Render(OBJMANAGER()->GetSprite());
		}
	}
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		pPlayer->pBullet[i]->Render(OBJMANAGER()->GetSprite());
		pPlayer->pMissile[i]->Render(OBJMANAGER()->GetSprite());
		pPlayer->pAimMissile[i]->Render(OBJMANAGER()->GetSprite());
	}
	pPlayer->pFireEffect->Render(OBJMANAGER()->GetSprite());

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pJohn[i]->Render(OBJMANAGER()->GetSprite());
		pJohn[i]->pBombEffect->Render(OBJMANAGER()->GetSprite());
		pChris[i]->Render(OBJMANAGER()->GetSprite());
		pChris[i]->pBombEffect->Render(OBJMANAGER()->GetSprite());
		for (int j = 0; j < JOHN_MAX_BULLET; j++)
		{
			pJohn[i]->pBullet[j]->Render(OBJMANAGER()->GetSprite());
		}
		for (int j = 0; j < CHRIS_MAX_BULLET; j++)
		{
			pChris[i]->pBullet[j]->Render(OBJMANAGER()->GetSprite());
		}
	}
	pRichard->Render(OBJMANAGER()->GetSprite());
	pRichard->pLazer->Render(OBJMANAGER()->GetSprite());
	pRichard->pHpBar->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < (int)(pRichard->GetHp() / 10.0f); i++)
	{
		pRichard->pHp[i]->Render(OBJMANAGER()->GetSprite());
	}
	pRichard->pBombEffect->Render(OBJMANAGER()->GetSprite());

	pHerrald->Render(OBJMANAGER()->GetSprite());
	pHerrald->pHpBar->Render(OBJMANAGER()->GetSprite());
	for (int i = 0; i < (int)(pHerrald->GetHp() / 15.0f); i++)
	{
		pHerrald->pHp[i]->Render(OBJMANAGER()->GetSprite());
	}
	for (int i = 0; i < HERRALD_MAX_BULLET; i++)
	{
		pHerrald->pBullet1[i]->Render(OBJMANAGER()->GetSprite());
		pHerrald->pBullet2[i]->Render(OBJMANAGER()->GetSprite());
	}
	pHerrald->pBombEffect->Render(OBJMANAGER()->GetSprite());

	pItem->Render(OBJMANAGER()->GetSprite());

	pStage1_3_1->Render();
	pStage1_3_2->Render();
	pStone->Render();
}

void Stage::StoneRespawn()
{
	if (GATIMER()->GetTimer() - fStoneTime > 15.0f)
	{
		int randNum = rand() % 4;

		switch (randNum)
		{
		case 0:
			pStone = new Stone(OBJMANAGER()->GetTexture(GaBase::TextureID::STONE_WAVE), 490, 295);
			pStone->SetStoneType(Stone::StoneType::WAVE);
			break;
		case 1:
			pStone = new Stone(OBJMANAGER()->GetTexture(GaBase::TextureID::STONE_WAVE_FREE), 490, 315);
			pStone->SetStoneType(Stone::StoneType::FREEWAVE);
			break;
		case 2:
			pStone = new Stone(OBJMANAGER()->GetTexture(GaBase::TextureID::STONE_HORN), 245, 390);
			pStone->SetStoneType(Stone::StoneType::HORN);
			break;
		case 3:
			pStone = new Stone(OBJMANAGER()->GetTexture(GaBase::TextureID::STONE_HOLE), 245, 175);
			pStone->SetStoneType(Stone::StoneType::HOLE);
			break;
		default:
			break;
		}
		pStone->Respawn();

		fStoneTime = GATIMER()->GetTimer();
	}
}

void Stage::StoneUpdate()
{
	pStone->Update();
	for (int i = 0; i < 3; i++)
	{
		CollsionCheck(pPlayer, pStone, pPlayer->GetCollision(), &pStone->rtStoneCollsion[i]);
	}
}

void Stage::ObstacleRespawn()
{
	if (GATIMER()->GetTimer() - fObstacleTime > 20.0f)
	{
		int randNum = rand() % 2;

		switch (randNum)
		{
		case 0:
			pObstacle = new Obstacle(OBJMANAGER()->GetTexture(GaBase::TextureID::ROCK), 190, 140);
			pObstacle->SetType(Obstacle::ObstacleType::ROCK);
			break;
		case 1:
			pObstacle = new Obstacle(OBJMANAGER()->GetTexture(GaBase::TextureID::SEAWEED), 190, 140);
			pObstacle->SetType(Obstacle::ObstacleType::SEAWEED);
			break;
		default:
			break;
		}
		pObstacle->Respawn();

		fObstacleTime = GATIMER()->GetTimer();
	}
}

void Stage::ObstacleUpdate()
{
	pObstacle->Update(pPlayer);
	CollsionCheck(pPlayer, pObstacle, false);
}


void Stage::ItemRespawn()
{
	if (GATIMER()->GetTimer() - fItemTime > 10.0f)
	{
		int randNum = rand() % 8;

		switch (randNum)
		{
		case 0:
			pItem = new HpUp(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_HP));
			break;
		case 1:
			pItem = new Missile(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_MISSILE));
			break;
		case 2:
			pItem = new MissileThree(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_MISSILE_THREE));
			break;
		case 3:
			pItem = new AimMissile(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_AIM_MISSILE));
			break;
		case 4:
			pItem = new Bomb(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_BOMB));
			break;
		case 5:
			pItem = new GunUp(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_GUN));
			break;
		case 6:
			pItem = new SpeedUp(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_SPEED));
			break;
		case 7:
			pItem = new AddOnPlus(OBJMANAGER()->GetTexture(GaBase::TextureID::ITEM_ADDON));
			break;
		default:
			break;
		}
		pItem->Respawn();

		fItemTime = GATIMER()->GetTimer();
	}
}

void Stage::ItemUpdate()
{
	pItem->Update(pPlayer);
	CollsionCheck(pPlayer, pItem, true);
}


void Stage::MattRespawn(float fTime)
{
	if (GATIMER()->GetTimer() - fMattTime > fTime)
	{
		pMatt[nMattCount]->Respawn(1.0f, 5.0f);
		pMatt[nMattCount]->Aim(pPlayer);

		nMattCount++;
		fMattTime = GATIMER()->GetTimer();
	}
	if (nMattCount >= MAX_ENEMY)
	{
		nMattCount = 0;
	}
}

void Stage::MattUpdate()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pMatt[i]->Update(pPlayer);
		CollsionCheck(pPlayer, pMatt[i], false);

		for (int j = 0; j < PLAYER_MAX_BULLET; j++)
		{
			CollsionCheck(pPlayer->pBullet[j], pMatt[i], false);
			CollsionCheck(pPlayer->pMissile[j], pMatt[i], false);
			CollsionCheck(pPlayer->pAimMissile[j], pMatt[i], false);
		}
		for (int j = 0; j < MAX_ADDON; j++)
		{
			for (int k = 0; k < ADDON_BULLET; k++)
			{
				CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pMatt[i], false);
			}
		}
	}
}

void Stage::JamesRespawn(float fTime)
{
	if (GATIMER()->GetTimer() - fJameTime > fTime)
	{
		pJames[nJameCount]->Respawn(5.0f, 2.0f);

		nJameCount++;
		fJameTime = GATIMER()->GetTimer();
	}
	if (nJameCount >= MAX_ENEMY)
	{
		nJameCount = 0;
	}
}

void Stage::JamesUpdate()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pJames[i]->Update(pPlayer);
		for (int j = 0; j < PLAYER_MAX_BULLET; j++)
		{
			CollsionCheck(pPlayer->pBullet[j], pJames[i], false);
			CollsionCheck(pPlayer->pMissile[j], pJames[i], false);
			CollsionCheck(pPlayer->pAimMissile[j], pJames[i], false);
		}
		for (int j = 0; j < JAMES_MAX_BULLET; j++)
		{
			CollsionCheck(pPlayer, pJames[i]->pBullet[j], false);
		}
		for (int j = 0; j < MAX_ADDON; j++)
		{
			for (int k = 0; k < ADDON_BULLET; k++)
			{
				CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pJames[i], false);
			}
		}
	}
}

void Stage::BorisUpdate()
{
	if (OBJMANAGER()->GetScore() >= 2000 && 
		!pBoris->GetRespawn() &&
		!pBoris->GetDie())
	{
		pBoris->Respawn(1000.0f);
	}
	pBoris->Update(pPlayer);

	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		CollsionCheck(pPlayer->pBullet[i], pBoris, false);
		CollsionCheck(pPlayer->pMissile[i], pBoris, false);
		CollsionCheck(pPlayer->pAimMissile[i], pBoris, false);
	}
	for (int i = 0; i < BORIS_MAX_BULLET; i++)
	{
		CollsionCheck(pPlayer, pBoris->pBullet[i], false);
	}
	for (int j = 0; j < MAX_ADDON; j++)
	{
		for (int k = 0; k < ADDON_BULLET; k++)
		{
			CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pBoris, false);
		}
	}
}

void Stage::CedricUpdate()
{
	if (OBJMANAGER()->GetScore() >= 4000 &&
		!pCedric->GetRespawn() &&
		!pCedric->GetDie())
	{
		pCedric->Respawn(1500.0f);
	}
	pCedric->Update(pPlayer);

	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		CollsionCheck(pPlayer->pBullet[i], pCedric, false);
		CollsionCheck(pPlayer->pMissile[i], pCedric, false);
		CollsionCheck(pPlayer->pAimMissile[i], pCedric, false);
	}
	for (int i = 0; i < CEDRIC_SPLIT_BULLET; i++)
	{
		CollsionCheck(pPlayer, pCedric->pSplitBullet[i], false);
	}
	for (int i = 0; i < CEDRIC_MAX_BULLET; i++)
	{
		CollsionCheck(pPlayer, pCedric->pBullet[i], false);
	}
	for (int j = 0; j < MAX_ADDON; j++)
	{
		for (int k = 0; k < ADDON_BULLET; k++)
		{
			CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pCedric, false);
		}
	}
}


void Stage::JohnRespawn(float fTime)
{
	if (GATIMER()->GetTimer() - fJohnTime > fTime)
	{
		pJohn[nJohnCount]->Respawn(10.0f, 2.0f);

		nJohnCount++;
		fJohnTime = GATIMER()->GetTimer();
	}
	if (nJohnCount >= MAX_ENEMY)
	{
		nJohnCount = 0;
	}
}

void Stage::JohnUpdate()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pJohn[i]->Update(pPlayer);
		for (int j = 0; j < PLAYER_MAX_BULLET; j++)
		{
			CollsionCheck(pPlayer->pBullet[j], pJohn[i], false);
			CollsionCheck(pPlayer->pMissile[j], pJohn[i], false);
			CollsionCheck(pPlayer->pAimMissile[j], pJohn[i], false);
		}
		for (int j = 0; j < JOHN_MAX_BULLET; j++)
		{
			CollsionCheck(pPlayer, pJohn[i]->pBullet[j], false);
		}
		for (int j = 0; j < MAX_ADDON; j++)
		{
			for (int k = 0; k < ADDON_BULLET; k++)
			{
				CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pJohn[i], false);
			}
		}
	}
}


void Stage::ChrisRespawn(float fTime)
{
	if (GATIMER()->GetTimer() - fChrisTime > fTime)
	{
		pChris[nChrisCount]->Respawn(15.0f, 3.0f);

		nChrisCount++;
		fChrisTime = GATIMER()->GetTimer();
	}
	if (nChrisCount >= MAX_ENEMY)
	{
		nChrisCount = 0;
	}
}

void Stage::ChrisUpdate()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pChris[i]->Update(pPlayer);
		for (int j = 0; j < PLAYER_MAX_BULLET; j++)
		{
			CollsionCheck(pPlayer->pBullet[j], pChris[i], false);
			CollsionCheck(pPlayer->pMissile[j], pChris[i], false);
			CollsionCheck(pPlayer->pAimMissile[j], pChris[i], false);
		}
		for (int j = 0; j < CHRIS_MAX_BULLET; j++)
		{
			CollsionCheck(pPlayer, pChris[i]->pBullet[j], false);
		}
		for (int j = 0; j < MAX_ADDON; j++)
		{
			for (int k = 0; k < ADDON_BULLET; k++)
			{
				CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pChris[i], false);
			}
		}
	}
}

void Stage::RichardUpdate()
{
	if (OBJMANAGER()->GetScore() >= 6000 &&
		!pRichard->GetRespawn() &&
		!pRichard->GetDie())
	{
		pRichard->Respawn(1000.0f);
	}
	pRichard->Update(pPlayer);

	CollsionCheck(pPlayer, pRichard->pLazer, false);
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		CollsionCheck(pPlayer->pBullet[i], pRichard, false);
		CollsionCheck(pPlayer->pMissile[i], pRichard, false);
		CollsionCheck(pPlayer->pAimMissile[i], pRichard, false);
	}
	for (int j = 0; j < MAX_ADDON; j++)
	{
		for (int k = 0; k < ADDON_BULLET; k++)
		{
			CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pRichard, false);
		}
	}
}


void Stage::HerraldUpdate()
{
	if (OBJMANAGER()->GetScore() >= 8000 &&
		!pHerrald->GetRespawn() &&
		!pHerrald->GetDie())
	{
		pHerrald->Respawn(1500.0f);
	}
	pHerrald->Update(pPlayer);

	for (int i = 0; i < HERRALD_MAX_BULLET; i++)
	{
		CollsionCheck(pPlayer, pHerrald->pBullet1[i], false);
		CollsionCheck(pPlayer, pHerrald->pBullet2[i], false);
	}
	for (int i = 0; i < PLAYER_MAX_BULLET; i++)
	{
		CollsionCheck(pPlayer->pBullet[i], pHerrald, false);
		CollsionCheck(pPlayer->pMissile[i], pHerrald, false);
		CollsionCheck(pPlayer->pAimMissile[i], pHerrald, false);
	}
	for (int j = 0; j < MAX_ADDON; j++)
	{
		for (int k = 0; k < ADDON_BULLET; k++)
		{
			CollsionCheck(pPlayer->pAddon[j]->pBullet[k], pHerrald, false);
		}
	}
}