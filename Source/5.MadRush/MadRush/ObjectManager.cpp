#include "stdafx.h"

ObjectManager ObjectManager::singleton;

ObjectManager::ObjectManager(void)
{
}

ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::Create()
{
	fGameTime = 0.0f;
	Score = 0;

	GunLevel = 0;

	PlayerHp = 5;
	fRespawnTime = 0.0f;

	nGaugeCount = 5;

	nRiderCount = 10;
	nCurrentRider = 0;
	fRiderTime = 0;

	nSoldierCount = 10;
	nCurrentSoldier = 0;
	fSoldierTime = 0;

	nBomberCount = 5;
	nCurrentBomber = 0;
	fBomberTime = 0;

	nWheelCount = 5;
	nCurrentWheel = 0;
	fWheelTime = 0;
	
	nBuzzardCount = 5;
	nCurrentBuzzard = 0;
	fBuzzardTime = 0;

	nTankCount = 5;
	nCurrentTank = 0;
	fTankTime = 0;

	nTruckCount = 5;
	nCurrentTruck = 0;
	fTruckTime = 0;

	nGunCount = 5;
	nCurrentGun = 0;
	fGunTime = 0;

	nHpUpCount = 5;
	nCurrentHpUp = 0;
	fHpUpTime = 0;

	bCheat = false;

	vDirection = { 1, 1, 1 };

	LoadFile();
}

void ObjectManager::ProcessAll()
{
	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		break;
	case GaApp::GameMode::GAME1:
		ShowCursor(false);
		Stage1Update();

		pBg_Stage1_1->GetPosition()->y += 10.0f;
		pBg_Stage1_2->GetPosition()->y += 10.0f;

		if (pBg_Stage1_1->GetPosition()->y >= 768)
		{
			pBg_Stage1_1->SetPosition(0, -768, 0);
		}
		if (pBg_Stage1_2->GetPosition()->y >= 768)
		{
			pBg_Stage1_2->SetPosition(0, -768, 0);
		}

		pStorm_1->GetPosition()->x -= 4.0f;
		pStorm_2->GetPosition()->x -= 4.0f;

		if (pStorm_1->GetPosition()->x <= -1024)
		{
			pStorm_1->SetPosition(1024, 0, 0);
		}
		if (pStorm_2->GetPosition()->x <= -1024)
		{
			pStorm_2->SetPosition(1024, 0, 0);
		}

		pPlayer1->SetCollison(20, 56, 5, 5);
		pPlayer2->SetCollison(20, 59, 5, 5);
	
		for (int i = 0; i < 150; i++)
		{
			pPlayer1->vecMissile[i]->SetCollison(0, 0, 10, 20);
			pPlayer2->vecMissile[i]->SetCollison(0, 0, 10, 20);
			

			pPlayer1->vecMissile[i]->Move(vDirection);
			pPlayer2->vecMissile[i]->Move(vDirection);
		}
		break;
	case GaApp::GameMode::GAME2:
		ShowCursor(false);
		Stage2Update();

		pBg_Stage2_1->GetPosition()->y += 10.0f;
		pBg_Stage2_2->GetPosition()->y += 10.0f;

		if (pBg_Stage2_1->GetPosition()->y >= 768)
		{
			pBg_Stage2_1->SetPosition(0, -768, 0);
		}
		if (pBg_Stage2_2->GetPosition()->y >= 768)
		{
			pBg_Stage2_2->SetPosition(0, -768, 0);
		}

		pStorm_1->GetPosition()->x -= 4.0f;
		pStorm_2->GetPosition()->x -= 4.0f;

		if (pStorm_1->GetPosition()->x <= -1024)
		{
			pStorm_1->SetPosition(1024, 0, 0);
		}
		if (pStorm_2->GetPosition()->x <= -1024)
		{
			pStorm_2->SetPosition(1024, 0, 0);
		}

		pPlayer1->SetCollison(20, 56, 5, 5);
		pPlayer2->SetCollison(20, 59, 5, 5);

		for (int i = 0; i < 150; i++)
		{
			pPlayer1->vecMissile[i]->SetCollison(0, 0, 10, 20);
			pPlayer2->vecMissile[i]->SetCollison(0, 0, 10, 20);


			pPlayer1->vecMissile[i]->Move(vDirection);
			pPlayer2->vecMissile[i]->Move(vDirection);
		}
		break;
	case GaApp::GameMode::DIE:
		break;
	}
}

void ObjectManager::LoadFile()
{
	AddTexture(GaBase::TextureID::INTRO, TEXT("Texture\\Intro.png"));
	AddTexture(GaBase::TextureID::BG_STAGE1_1, TEXT("Texture\\Bg_stage1_1.png"));
	AddTexture(GaBase::TextureID::BG_STAGE1_2, TEXT("Texture\\Bg_stage1_2.png"));
	AddTexture(GaBase::TextureID::BG_STAGE2_1, TEXT("Texture\\Bg_stage2_1.png"));
	AddTexture(GaBase::TextureID::BG_STAGE2_2, TEXT("Texture\\Bg_stage2_2.png"));
	AddTexture(GaBase::TextureID::STORM_1, TEXT("Texture\\Storm_1.png"));
	AddTexture(GaBase::TextureID::STORM_2, TEXT("Texture\\Storm_2.png"));
	AddTexture(GaBase::TextureID::PLAYER1, TEXT("Texture\\Player1.png"));
	AddTexture(GaBase::TextureID::PLAYER2, TEXT("Texture\\Player2.png"));
	AddTexture(GaBase::TextureID::MISSILE, TEXT("Texture\\Missile.png"));
	AddTexture(GaBase::TextureID::RIDER, TEXT("Texture\\Rider.png"));
	AddTexture(GaBase::TextureID::SOLDIER, TEXT("Texture\\Soldier.png"));
	AddTexture(GaBase::TextureID::BOMBER, TEXT("Texture\\Bomber.png"));
	AddTexture(GaBase::TextureID::WHEEL, TEXT("Texture\\Wheel.png"));
	AddTexture(GaBase::TextureID::BUZZARD, TEXT("Texture\\Buzzard.png"));
	AddTexture(GaBase::TextureID::TANK, TEXT("Texture\\Tank.png"));
	AddTexture(GaBase::TextureID::TRUCK, TEXT("Texture\\Truck.png"));
	AddTexture(GaBase::TextureID::BOSS, TEXT("Texture\\Boss.png"));
	AddTexture(GaBase::TextureID::DIRECTBULLET, TEXT("Texture\\DirectBullet.png"));
	AddTexture(GaBase::TextureID::AIMBULLET, TEXT("Texture\\AimBullet.png"));
	AddTexture(GaBase::TextureID::AIMBULLET2, TEXT("Texture\\AimBullet2.png"));
	AddTexture(GaBase::TextureID::NWAYBULLET, TEXT("Texture\\nWayBullet.png"));
	AddTexture(GaBase::TextureID::CIRCLEBULLET, TEXT("Texture\\CircleBullet.png"));
	AddTexture(GaBase::TextureID::BOSSBULLET, TEXT("Texture\\BossBullet.png"));
	AddTexture(GaBase::TextureID::HITEFFECT, TEXT("Texture\\HitEffect.png"));
	AddTexture(GaBase::TextureID::EXPLOSION, TEXT("Texture\\Explosion.png"));
	AddTexture(GaBase::TextureID::BOMBEFFECT, TEXT("Texture\\BombEffect.png"));
	AddTexture(GaBase::TextureID::BOSSEFFECT, TEXT("Texture\\BossEffect.png"));
	AddTexture(GaBase::TextureID::GAUGEBAR, TEXT("Texture\\GaugeBar.png"));
	AddTexture(GaBase::TextureID::GAUGE, TEXT("Texture\\Gauge.png"));
	AddTexture(GaBase::TextureID::HPUP, TEXT("Texture\\HpUp.png"));
	AddTexture(GaBase::TextureID::GUN, TEXT("Texture\\Gun.png"));
	AddTexture(GaBase::TextureID::UI, TEXT("Texture\\UI.png"));
	AddTexture(GaBase::TextureID::DIE, TEXT("Texture\\Die.png"));
	AddTexture(GaBase::TextureID::ENDING, TEXT("Texture\\Ending.png"));

	AddObject();
}

void ObjectManager::AddObject()
{
	pIntro = new Screen(GetTexture(GaBase::TextureID::INTRO), 0, 0);
	pDie = new Screen(GetTexture(GaBase::TextureID::DIE), 0, 0);
	pEnding = new Screen(GetTexture(GaBase::TextureID::ENDING), 0, 0);

	pBg_Stage1_1 = new Screen(GetTexture(GaBase::TextureID::BG_STAGE1_1), 0, 0);
	pBg_Stage1_2 = new Screen(GetTexture(GaBase::TextureID::BG_STAGE1_2), 0, -768);

	pBg_Stage2_1 = new Screen(GetTexture(GaBase::TextureID::BG_STAGE2_1), 0, 0);
	pBg_Stage2_2 = new Screen(GetTexture(GaBase::TextureID::BG_STAGE2_2), 0, -768);

	pStorm_1 = new Screen(GetTexture(GaBase::TextureID::STORM_1), 0, 0);
	pStorm_2 = new Screen(GetTexture(GaBase::TextureID::STORM_2), 1024, 0);

	pUI = new Screen(GetTexture(GaBase::TextureID::UI), 0, 0);

	pPlayer1 = new Player(GetTexture(GaBase::TextureID::PLAYER1), 700, 500);
	pPlayer2 = new Player(GetTexture(GaBase::TextureID::PLAYER2), 200, 500);

	pGaugeBar = new GaugeBar(GetTexture(GaBase::TextureID::GAUGEBAR));

	pBoss = new Boss(GetTexture(GaBase::TextureID::BOSS), 200, 300);

	vecGauge.reserve(nGaugeCount);
	Gauge* gauge = NULL;
	for (int i = 0; i < nGaugeCount; i++)
	{
		gauge = new Gauge(GetTexture(GaBase::TextureID::GAUGE));
		vecGauge.push_back(gauge);
		vecGauge[i]->SetPosition(20, 690 - (i * 31), 0);
	}

	vecRider.reserve(nRiderCount);
	Rider* rider = NULL;
	for (int i = 0; i < nRiderCount; i++)
	{
		rider = new Rider(GetTexture(GaBase::TextureID::RIDER), 70, 100);
		vecRider.push_back(rider);
	}

	vecSoldier.reserve(nSoldierCount);
	Soldier* soldier = NULL;
	for (int i = 0; i < nSoldierCount; i++)
	{
		soldier = new Soldier(GetTexture(GaBase::TextureID::SOLDIER), 90, 100);
		vecSoldier.push_back(soldier);
	}

	vecBomber.reserve(nSoldierCount);
	Bomber* bomber = NULL;
	for (int i = 0; i < nSoldierCount; i++)
	{
		bomber = new Bomber(GetTexture(GaBase::TextureID::BOMBER), 60, 60);
		vecBomber.push_back(bomber);
	}

	vecWheel.reserve(nWheelCount);
	Wheel* wheel= NULL;
	for (int i = 0; i < nWheelCount; i++)
	{
		wheel = new Wheel(GetTexture(GaBase::TextureID::WHEEL), 40, 70);
		vecWheel.push_back(wheel);
	}

	vecBuzzard.reserve(nBuzzardCount);
	Buzzard* buzzard= NULL;
	for (int i = 0; i < nBuzzardCount; i++)
	{
		buzzard = new Buzzard(GetTexture(GaBase::TextureID::BUZZARD), 100, 150);
		vecBuzzard.push_back(buzzard);
	}

	vecTank.reserve(nTankCount);
	Tank* tank = NULL;
	for (int i = 0; i < nTankCount; i++)
	{
		tank = new Tank(GetTexture(GaBase::TextureID::TANK), 150, 200);
		vecTank.push_back(tank);
	}

	vecTruck.reserve(nTruckCount);
	Truck* truck= NULL;
	for (int i = 0; i < nTruckCount; i++)
	{
		truck = new Truck(GetTexture(GaBase::TextureID::TRUCK), 120, 170);
		vecTruck.push_back(truck);
	}

	vecHpUp.reserve(nHpUpCount);
	Item* hpup = NULL;
	for (int i = 0; i < nHpUpCount; i++)
	{
		hpup = new Item(GetTexture(GaBase::TextureID::HPUP));
		vecHpUp.push_back(hpup);
	}
	
	vecGun.reserve(nGunCount);
	Item* gun = NULL;
	for (int i = 0; i < nGunCount; i++)
	{
		gun = new Item(GetTexture(GaBase::TextureID::GUN));
		vecGun.push_back(gun);
	}
}

HRESULT ObjectManager::AddTexture(DWORD id, TCHAR* filename)
{
	BOOL hRet = S_OK;
	LPDIRECT3DTEXTURE9 texture;

	hRet = D3DXCreateTextureFromFileEx(GAAPP()->GetDevice(),
		filename,
		D3DX_DEFAULT, D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		0,
		NULL, NULL,
		&texture);

	if (FAILED(hRet))
	{
		return E_FAIL;
	}

	TextureMap.insert(TEXMAP_PAIR(id, texture));

	return S_OK;
}

LPDIRECT3DTEXTURE9 ObjectManager::GetTexture(DWORD id)
{
	TEXMAP_ITER iter;

	iter = TextureMap.find(id);

	if (iter == TextureMap.end())
	{
		return NULL;
	}

	return iter->second;
}

void ObjectManager::IntroRender(LPD3DXSPRITE sprite)
{
	pIntro->Render(sprite);
}

void ObjectManager::Stage1Render(LPD3DXSPRITE sprite)
{
	pBg_Stage1_1->Render(sprite);
	pBg_Stage1_2->Render(sprite);

	for (int i = 0; i < nBomberCount; i++)
	{
		vecBomber[i]->Render(sprite);
		vecBomber[i]->pEffectHit->Render(sprite);
		vecBomber[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nWheelCount; i++)
	{
		vecWheel[i]->Render(sprite);
		vecWheel[i]->pEffectHit->Render(sprite);
		vecWheel[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nRiderCount; i++)
	{
		vecRider[i]->Render(sprite);
		vecRider[i]->pEffectHit->Render(sprite);
		vecRider[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nSoldierCount; i++)
	{
		vecSoldier[i]->Render(sprite);
		vecSoldier[i]->pEffectHit->Render(sprite);
		vecSoldier[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nBuzzardCount; i++)
	{
		vecBuzzard[i]->Render(sprite);
		vecBuzzard[i]->pEffectHit->Render(sprite);
		vecBuzzard[i]->pEffectBomb->Render(sprite);
	}

	for (int i = 0; i < nTankCount; i++)
	{
		vecTank[i]->Render(sprite);
		vecTank[i]->pEffectHit->Render(sprite);
		vecTank[i]->pEffectBomb->Render(sprite);
	}

	for (int i = 0; i < nTankCount; i++)
	{
		vecTruck[i]->Render(sprite);
		vecTruck[i]->pEffectHit->Render(sprite);
		vecTruck[i]->pEffectBomb->Render(sprite);
	}

	pBoss->Render(sprite);

	for (int i = 0; i < 150; i++)
	{
		pPlayer1->vecMissile[i]->Render(sprite);
		pPlayer2->vecMissile[i]->Render(sprite);
	}

	pPlayer1->Render(sprite);
	pPlayer2->Render(sprite);

	for (int i = 0; i < nHpUpCount; i++)
	{
		vecHpUp[i]->Render(sprite);
	}

	for (int i = 0; i < nGunCount; i++)
	{
		vecGun[i]->Render(sprite);
	}

	for (int i = 0; i < 640; i++)
	{
		pBoss->vecBullet[i]->Render(sprite);
	}

	for (int i = 0; i < nRiderCount; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			vecRider[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nSoldierCount; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			vecSoldier[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nBuzzardCount; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			vecBuzzard[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nTankCount; i++)
	{
		for (int j = 0; j < 72; j++)
		{
			vecTank[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nTruckCount; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			vecTruck[i]->vecBullet[j]->Render(sprite);
		}
	}

	pBoss->pEffectBoss->Render(sprite);

	pStorm_1->Render(sprite);
	pStorm_2->Render(sprite);

	pGaugeBar->Render(sprite);
	for (int i = 0; i < PlayerHp; i++)
	{
		vecGauge[i]->Render(sprite);
	}

	pUI->Render(sprite);

	sprintf_s(Timestr, "%0.0f\n", fGameTime);
	RECT TimeRect = { 493, 15, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), Timestr, -1, &TimeRect, DT_NOCLIP, D3DCOLOR_XRGB(246, 246, 246));

	sprintf_s(Scorestr, "%d\n", Score);
	RECT ScoreRect = { 60, 15, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), Scorestr, -1, &ScoreRect, DT_NOCLIP, D3DCOLOR_XRGB(76, 76, 76));
}

void ObjectManager::Stage2Render(LPD3DXSPRITE sprite)
{
	pBg_Stage2_1->Render(sprite);
	pBg_Stage2_2->Render(sprite);

	for (int i = 0; i < nBomberCount; i++)
	{
		vecBomber[i]->Render(sprite);
		vecBomber[i]->pEffectHit->Render(sprite);
		vecBomber[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nWheelCount; i++)
	{
		vecWheel[i]->Render(sprite);
		vecWheel[i]->pEffectHit->Render(sprite);
		vecWheel[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nRiderCount; i++)
	{
		vecRider[i]->Render(sprite);
		vecRider[i]->pEffectHit->Render(sprite);
		vecRider[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nSoldierCount; i++)
	{
		vecSoldier[i]->Render(sprite);
		vecSoldier[i]->pEffectHit->Render(sprite);
		vecSoldier[i]->pExplosion->Render(sprite);
	}

	for (int i = 0; i < nBuzzardCount; i++)
	{
		vecBuzzard[i]->Render(sprite);
		vecBuzzard[i]->pEffectHit->Render(sprite);
		vecBuzzard[i]->pEffectBomb->Render(sprite);
	}

	for (int i = 0; i < nTankCount; i++)
	{
		vecTank[i]->Render(sprite);
		vecTank[i]->pEffectHit->Render(sprite);
		vecTank[i]->pEffectBomb->Render(sprite);
	}

	for (int i = 0; i < nTankCount; i++)
	{
		vecTruck[i]->Render(sprite);
		vecTruck[i]->pEffectHit->Render(sprite);
		vecTruck[i]->pEffectBomb->Render(sprite);
	}

	pBoss->Render(sprite);

	for (int i = 0; i < 150; i++)
	{
		pPlayer1->vecMissile[i]->Render(sprite);
		pPlayer2->vecMissile[i]->Render(sprite);
	}

	pPlayer1->Render(sprite);
	pPlayer2->Render(sprite);

	for (int i = 0; i < nHpUpCount; i++)
	{
		vecHpUp[i]->Render(sprite);
	}

	for (int i = 0; i < nGunCount; i++)
	{
		vecGun[i]->Render(sprite);
	}

	for (int i = 0; i < 640; i++)
	{
		pBoss->vecBullet[i]->Render(sprite);
	}

	for (int i = 0; i < nRiderCount; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			vecRider[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nSoldierCount; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			vecSoldier[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nBuzzardCount; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			vecBuzzard[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nTankCount; i++)
	{
		for (int j = 0; j < 72; j++)
		{
			vecTank[i]->vecBullet[j]->Render(sprite);
		}
	}

	for (int i = 0; i < nTruckCount; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			vecTruck[i]->vecBullet[j]->Render(sprite);
		}
	}

	pBoss->pEffectBoss->Render(sprite);

	pStorm_1->Render(sprite);
	pStorm_2->Render(sprite);

	pGaugeBar->Render(sprite);
	for (int i = 0; i < PlayerHp; i++)
	{
		vecGauge[i]->Render(sprite);
	}

	pUI->Render(sprite);

	sprintf_s(Timestr, "%0.0f\n", fGameTime);
	RECT TimeRect = { 493, 15, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), Timestr, -1, &TimeRect, DT_NOCLIP, D3DCOLOR_XRGB(246, 246, 246));

	sprintf_s(Scorestr, "%d\n", Score);
	RECT ScoreRect = { 60, 15, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), Scorestr, -1, &ScoreRect, DT_NOCLIP, D3DCOLOR_XRGB(76, 76, 76));
}

void ObjectManager::DieRender(LPD3DXSPRITE sprite)
{
	pDie->Render(sprite);
}

void ObjectManager::EndingRender(LPD3DXSPRITE sprite)
{
	pEnding->Render(sprite);
}

void ObjectManager::Stage1Update()
{
	fGameTime = GATIMER()->GetGameTime();

	GunUpdate();

	RiderUpdate();
	SoldierUpdate();
	WheelUpdate();
	BomberUpdate();
	BuzzardUpdate();
	TankUpdate();

	ItemUpdate();
	HpUpdate();

	if (fGameTime > 58)
	{
		for (int i = 0; i < nRiderCount; i++)
		{
			vecRider[i]->SetVisible(false);
			vecRider[i]->pEffectHit->SetVisible(false);
			vecRider[i]->pExplosion->SetVisible(false);
			for (int j = 0; j < 10; j++)
			{
				vecRider[i]->vecBullet[j]->SetVisible(false);
			}
		}
		for (int i = 0; i < nSoldierCount; i++)
		{
			vecSoldier[i]->SetVisible(false);
			vecSoldier[i]->pEffectHit->SetVisible(false);
			vecSoldier[i]->pExplosion->SetVisible(false);

			for (int j = 0; j < 10; j++)
			{
				vecSoldier[i]->vecBullet[j]->SetVisible(false);
			}
		}
		for (int i = 0; i < nBomberCount; i++)
		{
			vecBomber[i]->SetVisible(false);
			vecBomber[i]->pEffectHit->SetVisible(false);
			vecBomber[i]->pExplosion->SetVisible(false);
		}
		for (int i = 0; i < nWheelCount; i++)
		{
			vecWheel[i]->SetVisible(false);
			vecWheel[i]->pEffectHit->SetVisible(false);
			vecWheel[i]->pExplosion->SetVisible(false);
		}
		for (int i = 0; i < nBuzzardCount; i++)
		{
			vecBuzzard[i]->SetVisible(false);
			vecBuzzard[i]->pEffectHit->SetVisible(false);
			vecBuzzard[i]->pEffectBomb->SetVisible(false);
			for (int j = 0; j < 30; j++)
			{
				vecBuzzard[i]->vecBullet[j]->SetVisible(false);
			}
		}
		for (int i = 0; i < nTankCount; i++)
		{
			vecTank[i]->SetVisible(false);
			vecTank[i]->pEffectHit->SetVisible(false);
			vecTank[i]->pEffectBomb->SetVisible(false);
			for (int j = 0; j < 72; j++)
			{
				vecTank[i]->vecBullet[j]->SetVisible(false);
			}
		}
		for (int i = 0; i < 5; i++)
		{
			vecHpUp[i]->SetVisible(false);
			vecGun[i]->SetVisible(false);
		}
	}

	if (fGameTime > 60)
	{
		GAAPP()->SetGameMode(GaApp::GameMode::GAME2);
	}
}

void ObjectManager::Stage2Update()
{
	fGameTime = GATIMER()->GetGameTime();

	GunUpdate();

	RiderUpdate();
	SoldierUpdate();
	WheelUpdate();
	BomberUpdate();
	BuzzardUpdate();
	TankUpdate();
	TruckUpdate();

	ItemUpdate();
	HpUpdate();

	if (fGameTime >= 130 && fGameTime < 131)
	{
		pBoss->SetPosition(400, -300, 0);
		pBoss->SetVisible(true);
	}

	pBoss->SetCollison(20, 0, 160, 300);
	pBoss->Shoot(GATIMER()->GetAbsoluteFrame());
	pBoss->Move();

	for (int i = 0; i < 640; i++)
	{
		pBoss->vecBullet[i]->SetCollison(7, 7, 22, 22);
		pBoss->vecBullet[i]->CollisonCheck(pPlayer1);
		pBoss->vecBullet[i]->CollisonCheck(pPlayer2);
		pBoss->vecBullet[i]->Move(pBoss->vecBullet[i]->GetDirectVec());
	}
	for (int k = 0; k < 150; k++)
	{
		pBoss->CollisonCheck(pPlayer1->vecMissile[k]);
		pBoss->CollisonCheck(pPlayer2->vecMissile[k]);
	}

	if (pBoss->bDie)
	{
		GAAPP()->SetGameMode(GaApp::GameMode::ENDING);
	}
}

void ObjectManager::RiderUpdate()
{
	if (GATIMER()->GetAbsoluteFrame() - fRiderTime > 70)
	{
		vecRider[nCurrentRider]->Respawn();
		vecRider[nCurrentRider]->SetVisible(true);

		nCurrentRider++;
		if (nCurrentRider > nRiderCount - 1)
		{
			nCurrentRider = 0;
		}
		fRiderTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nRiderCount; i++)
	{
		vecRider[i]->SetCollison(9, 8, 50, 82);

		vecRider[i]->Shoot(GATIMER()->GetAbsoluteFrame());
		vecRider[i]->Move();
		for (int j = 0; j < 10; j++)
		{
			vecRider[i]->vecBullet[j]->SetCollison(3, 3, 14, 14);

			vecRider[i]->vecBullet[j]->CollisonCheck(pPlayer1);
			vecRider[i]->vecBullet[j]->CollisonCheck(pPlayer2);
			vecRider[i]->vecBullet[j]->Move(vecRider[i]->vecBullet[j]->GetDirectVec());
		}
		for (int k = 0; k < 150; k++)
		{
			vecRider[i]->CollisonCheck(pPlayer1->vecMissile[k]);
			vecRider[i]->CollisonCheck(pPlayer2->vecMissile[k]);
		}
	}
}

void ObjectManager::SoldierUpdate()
{
	if (GATIMER()->GetAbsoluteFrame() - fSoldierTime > 150)
	{
		vecSoldier[nCurrentSoldier]->Respawn();
		vecSoldier[nCurrentSoldier]->SetVisible(true);

		nCurrentSoldier++;
		if (nCurrentSoldier > nSoldierCount - 1)
		{
			nCurrentSoldier = 0;
		}
		fSoldierTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nSoldierCount; i++)
	{
		vecSoldier[i]->SetCollison(20, 0, 45, 100);

		vecSoldier[i]->Shoot(GATIMER()->GetAbsoluteFrame());
		vecSoldier[i]->Move();
		for (int j = 0; j < 10; j++)
		{
			vecSoldier[i]->vecBullet[j]->SetCollison(3, 3, 19, 19);

			vecSoldier[i]->vecBullet[j]->CollisonCheck(pPlayer1);
			vecSoldier[i]->vecBullet[j]->CollisonCheck(pPlayer2);
			vecSoldier[i]->vecBullet[j]->Move(vecSoldier[i]->vecBullet[j]->GetDirectVec());
		}
		for (int k = 0; k < 150; k++)
		{
			vecSoldier[i]->CollisonCheck(pPlayer1->vecMissile[k]);
			vecSoldier[i]->CollisonCheck(pPlayer2->vecMissile[k]);
		}
	}

}

void ObjectManager::BomberUpdate()
{
	if (GATIMER()->GetAbsoluteFrame() - fBomberTime > 200)
	{
		vecBomber[nCurrentBomber]->Respawn();
		vecBomber[nCurrentBomber]->SetVisible(true);

		nCurrentBomber++;
		if (nCurrentBomber > nBomberCount - 1)
		{
			nCurrentBomber = 0;
		}
		fBomberTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nBomberCount; i++)
	{
		vecBomber[i]->SetCollison(7, 7, 45, 45);

		vecBomber[i]->Move();
		vecBomber[i]->Hit(1.0f);
		vecBomber[i]->CollisonCheck(pPlayer1);
		vecBomber[i]->CollisonCheck(pPlayer2);
		for (int k = 0; k < 150; k++)
		{
			vecBomber[i]->CollisonCheck(pPlayer1->vecMissile[k]);
			vecBomber[i]->CollisonCheck(pPlayer2->vecMissile[k]);
		}
	}
}

void ObjectManager::WheelUpdate()
{
	if (GATIMER()->GetAbsoluteFrame() - fWheelTime > 150)
	{
		vecWheel[nCurrentWheel]->Respawn();
		vecWheel[nCurrentWheel]->SetVisible(true);

		nCurrentWheel++;
		if (nCurrentWheel > nWheelCount - 1)
		{
			nCurrentWheel = 0;
		}
		fWheelTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nWheelCount; i++)
	{
		vecWheel[i]->SetCollison(0, 0, 40, 70);

		vecWheel[i]->Move();
		vecWheel[i]->Hit(1.0f);
		vecWheel[i]->CollisonCheck(pPlayer1);
		vecWheel[i]->CollisonCheck(pPlayer2);
		for (int k = 0; k < 150; k++)
		{
			vecWheel[i]->CollisonCheck(pPlayer1->vecMissile[k]);
			vecWheel[i]->CollisonCheck(pPlayer2->vecMissile[k]);
		}
	}

}

void ObjectManager::BuzzardUpdate()
{
	if (GATIMER()->GetAbsoluteFrame() - fBuzzardTime > 400)
	{
		vecBuzzard[nCurrentBuzzard]->Respawn();
		vecBuzzard[nCurrentBuzzard]->SetVisible(true);

		nCurrentBuzzard++;
		if (nCurrentBuzzard > nBuzzardCount - 1)
		{
			nCurrentBuzzard = 0;
		}
		fBuzzardTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nBuzzardCount; i++)
	{
		vecBuzzard[i]->SetCollison(18, 13, 65, 120);

		vecBuzzard[i]->Shoot(GATIMER()->GetAbsoluteFrame());
		vecBuzzard[i]->Move();
		for (int j = 0; j < 30; j++)
		{
			vecBuzzard[i]->vecBullet[j]->SetCollison(4, 4, 20, 20);

			vecBuzzard[i]->vecBullet[j]->CollisonCheck(pPlayer1);
			vecBuzzard[i]->vecBullet[j]->CollisonCheck(pPlayer2);
			vecBuzzard[i]->vecBullet[j]->Move(vecBuzzard[i]->vecBullet[j]->GetDirectVec());
		}
		for (int k = 0; k < 150; k++)
		{
			vecBuzzard[i]->CollisonCheck(pPlayer1->vecMissile[k]);
			vecBuzzard[i]->CollisonCheck(pPlayer2->vecMissile[k]);
		}
	}
}

void ObjectManager::TankUpdate()
{
	if (!pBoss->GetVisible())
	{
		if (GATIMER()->GetAbsoluteFrame() - fTankTime > 1000)
		{
			vecTank[nCurrentTank]->Respawn();
			vecTank[nCurrentTank]->SetVisible(true);

			nCurrentTank++;
			if (nCurrentTank > nTankCount - 1)
			{
				nCurrentTank = 0;
			}
			fTankTime = GATIMER()->GetAbsoluteFrame();
		}
	}

	for (int i = 0; i < nTankCount; i++)
	{
		vecTank[i]->SetCollison(10, 10, 135, 185);

		vecTank[i]->Shoot(GATIMER()->GetAbsoluteFrame());
		vecTank[i]->Move();
		for (int j = 0; j < 72; j++)
		{
			vecTank[i]->vecBullet[j]->SetCollison(6, 6, 33, 33);

			vecTank[i]->vecBullet[j]->CollisonCheck(pPlayer1);
			vecTank[i]->vecBullet[j]->CollisonCheck(pPlayer2);
			vecTank[i]->vecBullet[j]->Move(vecTank[i]->vecBullet[j]->GetDirectVec());
		}
		for (int k = 0; k < 150; k++)
		{
			vecTank[i]->CollisonCheck(pPlayer1->vecMissile[k]);
			vecTank[i]->CollisonCheck(pPlayer2->vecMissile[k]);
		}
	}
}

void ObjectManager::TruckUpdate()
{
	if (GATIMER()->GetAbsoluteFrame() - fTruckTime > 650)
	{
		vecTruck[nCurrentTruck]->Respawn();
		vecTruck[nCurrentTruck]->SetVisible(true);

		nCurrentTruck++;
		if (nCurrentTruck > nTruckCount - 1)
		{
			nCurrentTruck = 0;
		}
		fTruckTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nTankCount; i++)
	{
		vecTruck[i]->SetCollison(27, 0, 67, 170);

		vecTruck[i]->Shoot(GATIMER()->GetAbsoluteFrame());
		vecTruck[i]->Move();
		for (int j = 0; j < 50; j++)
		{
			vecTruck[i]->vecBullet[j]->SetCollison(0, 0, 20, 20);

			vecTruck[i]->vecBullet[j]->CollisonCheck(pPlayer1);
			vecTruck[i]->vecBullet[j]->CollisonCheck(pPlayer2);
			vecTruck[i]->vecBullet[j]->Move(vecTruck[i]->vecBullet[j]->GetDirectVec());
		}
		for (int k = 0; k < 150; k++)
		{
			vecTruck[i]->CollisonCheck(pPlayer1->vecMissile[k]);
			vecTruck[i]->CollisonCheck(pPlayer2->vecMissile[k]);
		}
	}
}

void ObjectManager::ItemUpdate()
{
	if (GATIMER()->GetAbsoluteFrame() - fHpUpTime > 1000)
	{
		vecHpUp[nCurrentHpUp]->Respawn();
		vecHpUp[nCurrentHpUp]->SetVisible(true);

		nCurrentHpUp++;
		if (nCurrentHpUp > nHpUpCount - 1)
		{
			nCurrentHpUp = 0;
		}
		fHpUpTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nHpUpCount; i++)
	{
		vecHpUp[i]->SetCollison(0, 0, 60, 60);
		vecHpUp[i]->Move();
		vecHpUp[i]->ItemCollisonCheck(pPlayer1);
		vecHpUp[i]->ItemCollisonCheck(pPlayer2);
		vecHpUp[i]->HitHp();
	}

	if (GATIMER()->GetAbsoluteFrame() - fGunTime > 500)
	{
		vecGun[nCurrentGun]->Respawn();
		vecGun[nCurrentGun]->SetVisible(true);

		nCurrentGun++;
		if (nCurrentGun > nGunCount - 1)
		{
			nCurrentGun = 0;
		}
		fGunTime = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nGunCount; i++)
	{
		vecGun[i]->SetCollison(0, 0, 60, 60);
		vecGun[i]->Move();
		vecGun[i]->ItemCollisonCheck(pPlayer1);
		vecGun[i]->ItemCollisonCheck(pPlayer2);
		vecGun[i]->HitGun();
	}
}

void ObjectManager::HpUpdate()
{
	if (GetAsyncKeyState(VK_F2))
	{
		bCheat = true;
	}

	if (PlayerHp >= 5)
	{
		PlayerHp = 5;
	}
	if (pPlayer1->GetHit() || pPlayer2->GetHit())
	{
		if (GATIMER()->GetAbsoluteFrame() - fRespawnTime > 50)
		{
			if (bCheat == false)
			{
				PlayerHp--;
			}
			pPlayer1->SetHit(false);
			pPlayer2->SetHit(false);
			
			fRespawnTime = GATIMER()->GetAbsoluteFrame();
		}
	}
	if (PlayerHp <= 0)
	{
		GAAPP()->SetGameMode(GaApp::GameMode::DIE);
	}
}

void ObjectManager::GunUpdate()
{
	if (GunLevel >= 2)
	{
		GunLevel = 2;
	}

	switch (GunLevel)
	{
	case 0:
		pPlayer1->gunstate = Player::GunState::ONE;
		pPlayer2->gunstate = Player::GunState::ONE;
		break;
	case 1:
		pPlayer1->gunstate = Player::GunState::TWO;
		pPlayer2->gunstate = Player::GunState::TWO;
		break;
	case 2:
		pPlayer1->gunstate = Player::GunState::THREE;
		pPlayer2->gunstate = Player::GunState::THREE;
		break;
	}
}

void ObjectManager::SetHP(float _hp)
{
	PlayerHp += _hp;
}

void ObjectManager::KeyProc()
{
	GAINPUT()->GetKeyboard()->Update();

	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		if (GAINPUT()->GetKeyboard()->IsAnyButtonDown())
		{
			Reset();
			GAAPP()->SetGameMode(GaApp::GameMode::GAME1);
			GATIMER()->SetAbsoliteFrame(0.0);
			GATIMER()->SetGameTime(0.0);
		}
		break;
	case GaApp::GameMode::GAME1:
	case GaApp::GameMode::GAME2:
		// P1
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_LEFT))
		{
			pPlayer1->SetMove(Player::MoveDirection::LEFT);
			pPlayer1->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_RIGHT))
		{
			pPlayer1->SetMove(Player::MoveDirection::RIGHT);
			pPlayer1->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_UP))
		{
			pPlayer1->SetMove(Player::MoveDirection::UP);
			pPlayer1->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_DOWN))
		{
			pPlayer1->SetMove(Player::MoveDirection::DOWN);
			pPlayer1->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_RSHIFT))
		{
			pPlayer1->SetSpeed(1.5f);
		}
		else if (!GAINPUT()->GetKeyboard()->IsButtonDown(DIK_RSHIFT))
		{
			pPlayer1->SetSpeed(5.0f);
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_RCONTROL))
		{
			pPlayer1->Shoot(GATIMER()->GetAbsoluteFrame());
		}
		// P2 
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_A))
		{
			pPlayer2->SetMove(Player::MoveDirection::LEFT);
			pPlayer2->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_D))
		{
			pPlayer2->SetMove(Player::MoveDirection::RIGHT);
			pPlayer2->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_W))
		{
			pPlayer2->SetMove(Player::MoveDirection::UP);
			pPlayer2->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_S))
		{
			pPlayer2->SetMove(Player::MoveDirection::DOWN);
			pPlayer2->Move();
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_LSHIFT))
		{
			pPlayer2->SetSpeed(1.5f);
		}
		else if (!GAINPUT()->GetKeyboard()->IsButtonDown(DIK_LSHIFT))
		{
			pPlayer2->SetSpeed(5.0f);
		}
		if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_LCONTROL))
		{
			pPlayer2->Shoot(GATIMER()->GetAbsoluteFrame());
		}
		break;
	case GaApp::GameMode::DIE:
		break;
	case GaApp::GameMode::ENDING:
		break;
	}
	if (GAINPUT()->GetKeyboard()->IsButtonDown(DIK_R))
	{
		GAAPP()->SetGameMode(GaApp::GameMode::INTRO);
	}
}

void ObjectManager::MouseProc()
{

}

void ObjectManager::Reset()
{
	Create();
	pPlayer1->Reset();
	pPlayer2->Reset();
	for (int i = 0; i < nRiderCount; i++)
	{
		vecRider[i]->SetVisible(false);
		vecRider[i]->pEffectHit->SetVisible(false);
		vecRider[i]->pExplosion->SetVisible(false);
		for (int j = 0; j < 10; j++)
		{
			vecRider[i]->vecBullet[j]->SetVisible(false);
		}
	}
	for (int i = 0; i < nSoldierCount; i++)
	{
		vecSoldier[i]->SetVisible(false);
		vecSoldier[i]->pEffectHit->SetVisible(false);
		vecSoldier[i]->pExplosion->SetVisible(false);

		for (int j = 0; j < 10; j++)
		{
			vecSoldier[i]->vecBullet[j]->SetVisible(false);
		}
	}
	for (int i = 0; i < nBomberCount; i++)
	{
		vecBomber[i]->SetVisible(false);
		vecBomber[i]->pEffectHit->SetVisible(false);
		vecBomber[i]->pExplosion->SetVisible(false);
	}
	for (int i = 0; i < nWheelCount; i++)
	{
		vecWheel[i]->SetVisible(false);
		vecWheel[i]->pEffectHit->SetVisible(false);
		vecWheel[i]->pExplosion->SetVisible(false);
	}
	for (int i = 0; i < nBuzzardCount; i++)
	{
		vecBuzzard[i]->SetVisible(false);
		vecBuzzard[i]->pEffectHit->SetVisible(false);
		vecBuzzard[i]->pEffectBomb->SetVisible(false);
		for (int j = 0; j < 30; j++)
		{
			vecBuzzard[i]->vecBullet[j]->SetVisible(false);
		}
	}
	for (int i = 0; i < nTankCount; i++)
	{
		vecTank[i]->SetVisible(false);
		vecTank[i]->pEffectHit->SetVisible(false);
		vecTank[i]->pEffectBomb->SetVisible(false);
		for (int j = 0; j < 72; j++)
		{
			vecTank[i]->vecBullet[j]->SetVisible(false);
		}
	}
	for (int i = 0; i < nTruckCount; i++)
	{
		vecTruck[i]->SetVisible(false);
		vecTruck[i]->pEffectHit->SetVisible(false);
		vecTruck[i]->pEffectBomb->SetVisible(false);
		for (int j = 0; j < 50; j++)
		{
			vecTruck[i]->vecBullet[j]->SetVisible(false);
		}
	}
	pBoss->SetVisible(false);
	pBoss->pEffectHit->SetVisible(false);
	pBoss->pEffectBoss->SetVisible(false);
	pBoss->bDie = false;
	for (int i = 0; i < 640; i++)
	{
		pBoss->vecBullet[i]->SetVisible(false);
	}
	for (int i = 0; i < 5; i++)
	{
		vecHpUp[i]->SetVisible(false);
		vecGun[i]->SetVisible(false);
	}
}