#include "stdafx.h"

ObjectManager ObjectManager::singleton;

int ObjectManager::Coin = 0;

ObjectManager::ObjectManager()
{
	ZeroMemory(&matScale, sizeof(matScale));
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Create()
{
	x = -3;
	y = -3;
	z = -3;

	nCarCount = 50;

	nCurrentCar1 = 0;
	nCurrentCar2 = 0;

	fCar1Time = 0.0f;
	fCar2Time = 0.0f;

	fGameTimer = 0.0f;

	fFinishTime = 0.0f;

	fWindTime = 0.0f;
	WindCount = 0;

	lastFrame = 0;

	LoadFile();
}

void ObjectManager::PrcessAll()
{
	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		if (x <= 3)
		{
			x += 0.05;
			y += 0.05;
			z += 0.05;
		}

		D3DXMatrixScaling(&matScale, x, y, z);
		break;
	case GaApp::GameMode::MENU:
		break;
	case GaApp::GameMode::CHOOSE:
		break;
	case GaApp::GameMode::STAGE1:
		Stage1Update();
		break;
	case GaApp::GameMode::STAGE2:
		Stage2Update();
		break;
	case GaApp::GameMode::STAGE3:
		Stage3Update();
		break;
	default:
		break;
	}
}

void ObjectManager::LoadFile()
{
	AddTexture(GaBase::TextureID::INTRO, L"Texture\\Intro.png");
	AddTexture(GaBase::TextureID::MENU, L"Texture\\Menu.png");
	AddTexture(GaBase::TextureID::CHOOSE, L"Texture\\Choose.png");
	AddTexture(GaBase::TextureID::STAGE1_BACK, L"Texture\\Stage1.png");
	AddTexture(GaBase::TextureID::STAGE2_BACK, L"Texture\\Stage2.png");
	AddTexture(GaBase::TextureID::STAGE3_BACK, L"Texture\\Stage3.png");
	AddTexture(GaBase::TextureID::LANDROVER, L"Texture\\LandRover.png");
	AddTexture(GaBase::TextureID::ENEMY, L"Texture\\Enemy.png");
	AddTexture(GaBase::TextureID::CAR1, L"Texture\\Car1.png");
	AddTexture(GaBase::TextureID::CAR2, L"Texture\\Car2.png");
	AddTexture(GaBase::TextureID::UI, L"Texture\\Ui.png");
	AddTexture(GaBase::TextureID::GOAL, L"Texture\\Goal.png");
	AddTexture(GaBase::TextureID::WIN, L"Texture\\Win.png");
	AddTexture(GaBase::TextureID::LOSE, L"Texture\\Lose.png");
	AddTexture(GaBase::TextureID::MINI_PLAYER, L"Texture\\MiniPlayer.png");
	AddTexture(GaBase::TextureID::MINI_ENEMY, L"Texture\\MiniEnemy.png");
	AddTexture(GaBase::TextureID::ENDING, L"Texture\\Ending.png");
	AddTexture(GaBase::TextureID::WIND, L"Texture\\Wind.png");

	AddObject();
}

void ObjectManager::AddObject()
{
	pIntro = new GameObject(GetTexture(GaBase::TextureID::INTRO), 1024, 768);
	pMenu = new GameObject(GetTexture(GaBase::TextureID::MENU), 1024, 768);
	pChoose = new GameObject(GetTexture(GaBase::TextureID::CHOOSE), 1024, 768);

	pUI = new GameObject(GetTexture(GaBase::TextureID::UI), 1024, 768);
	pGoal = new GameObject(GetTexture(GaBase::TextureID::GOAL), 401, 84);
	pGoal->SetPosition(-325, 84, 0);

	pWin = new GameObject(GetTexture(GaBase::TextureID::WIN), 530, 245);
	pWin->SetVisible(false);
	pWin->SetPosition(-250, -300, 0);

	pLose = new GameObject(GetTexture(GaBase::TextureID::LOSE), 530, 245);
	pLose->SetVisible(false);
	pLose->SetPosition(-250, -300, 0);

	pEnding = new GameObject(GetTexture(GaBase::TextureID::ENDING), 1024, 768);

	pWind = new GameObject(GetTexture(GaBase::TextureID::WIND), 120, 220);

	for (int i = 0; i < 3; i++)
	{
		rtWind[i].left = i * 120;
		rtWind[i].right = rtWind[i].left + 120;
		rtWind[i].top = 0;
		rtWind[i].bottom = 220;
	}

	//Stage1
	pStage1_Back1 = new GameObject(GetTexture(GaBase::TextureID::STAGE1_BACK), 1024, 768);
	
	RECT rtStage1_1;
	rtStage1_1.left = 0;
	rtStage1_1.right = 1024;
	rtStage1_1.top = 0;
	rtStage1_1.bottom = 768;
	pStage1_Back1->SetRect(rtStage1_1);
	pStage1_Back1->SetPosition(0, 0, 0);

	pStage1_Back2 = new GameObject(GetTexture(GaBase::TextureID::STAGE1_BACK), 1024, 768);

	RECT rtStage1_2;
	rtStage1_2.left = 0;
	rtStage1_2.right = 1024;
	rtStage1_2.top = 768;
	rtStage1_2.bottom = rtStage1_2.top + 768;
	pStage1_Back2->SetRect(rtStage1_2);
	pStage1_Back2->SetPosition(0, 768, 0);

	pStage1_Back3 = new GameObject(GetTexture(GaBase::TextureID::STAGE1_BACK), 1024, 768);

	RECT rtStage1_3;
	rtStage1_3.left = 0;
	rtStage1_3.right = 1024;
	rtStage1_3.top = 768 + 768;
	rtStage1_3.bottom = rtStage1_3.top + 768;
	pStage1_Back3->SetRect(rtStage1_3);
	pStage1_Back3->SetPosition(0, 768 * 2, 0);

	// Stage2
	pStage2_Back1 = new GameObject(GetTexture(GaBase::TextureID::STAGE2_BACK), 1024, 768);

	RECT rtStage2_1;
	rtStage2_1.left = 0;
	rtStage2_1.right = 1024;
	rtStage2_1.top = 0;
	rtStage2_1.bottom = 768;
	pStage2_Back1->SetRect(rtStage2_1);
	pStage2_Back1->SetPosition(0, 0, 0);

	pStage2_Back2 = new GameObject(GetTexture(GaBase::TextureID::STAGE2_BACK), 1024, 768);

	RECT rtStage2_2;
	rtStage2_2.left = 0;
	rtStage2_2.right = 1024;
	rtStage2_2.top = 768;
	rtStage2_2.bottom = rtStage2_2.top + 768;
	pStage2_Back2->SetRect(rtStage2_2);
	pStage2_Back2->SetPosition(0, 768, 0);

	pStage2_Back3 = new GameObject(GetTexture(GaBase::TextureID::STAGE2_BACK), 1024, 768);

	RECT rtStage2_3;
	rtStage2_3.left = 0;
	rtStage2_3.right = 1024;
	rtStage2_3.top = 768 + 768;
	rtStage2_3.bottom = rtStage2_3.top + 768;
	pStage2_Back3->SetRect(rtStage2_3);
	pStage2_Back3->SetPosition(0, 768 * 2, 0);

	// Stage3
	pStage3_Back1 = new GameObject(GetTexture(GaBase::TextureID::STAGE3_BACK), 1024, 768);

	RECT rtStage3_1;
	rtStage3_1.left = 0;
	rtStage3_1.right = 1024;
	rtStage3_1.top = 0;
	rtStage3_1.bottom = 768;
	pStage3_Back1->SetRect(rtStage3_1);
	pStage3_Back1->SetPosition(0, 0, 0);

	pStage3_Back2 = new GameObject(GetTexture(GaBase::TextureID::STAGE3_BACK), 1024, 768);

	RECT rtStage3_2;
	rtStage3_2.left = 0;
	rtStage3_2.right = 1024;
	rtStage3_2.top = 768;
	rtStage3_2.bottom = rtStage3_2.top + 768;
	pStage3_Back2->SetRect(rtStage3_2);
	pStage3_Back2->SetPosition(0, 768, 0);

	pStage3_Back3 = new GameObject(GetTexture(GaBase::TextureID::STAGE3_BACK), 1024, 768);

	RECT rtStage3_3;
	rtStage3_3.left = 0;
	rtStage3_3.right = 1024;
	rtStage3_3.top = 768 + 768;
	rtStage3_3.bottom = rtStage3_3.top + 768;
	pStage3_Back3->SetRect(rtStage3_3);
	pStage3_Back3->SetPosition(0, 768 * 2, 0);

	pPlayer = new LandRover(GetTexture(GaBase::TextureID::LANDROVER));
	pEnemy = new Enemy(GetTexture(GaBase::TextureID::ENEMY));

	pMiniPlayer = new GameObject(GetTexture(GaBase::TextureID::MINI_PLAYER), 10, 10);
	pMiniEnemy = new GameObject(GetTexture(GaBase::TextureID::MINI_ENEMY), 10, 10);

	pMiniPlayer->SetPosition(-870, -480, 0);
	pMiniEnemy->SetPosition(-885, -480, 0);

	for (int i = 0; i < nCarCount; i++)
	{
		pCar1[i] = new Car(GetTexture(GaBase::TextureID::CAR1), 120, 220);
	}
	for (int i = 0; i < nCarCount; i++)
	{
		pCar2[i] = new Car(GetTexture(GaBase::TextureID::CAR2), 120, 220);
	}
}

HRESULT ObjectManager::AddTexture(DWORD id, TCHAR* filename)
{
	HRESULT hRet = S_OK;
	LPDIRECT3DTEXTURE9 texture;

	hRet = D3DXCreateTextureFromFileEx(GAAPP()->GetDevice(),
		filename,
		D3DX_DEFAULT, D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		0, NULL, NULL, &texture);

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

void ObjectManager::Car1Update()
{
	if (GATIMER()->GetAbsoluteFrame() - fCar1Time >= 200)
	{
		pCar1[nCurrentCar1]->Respawn();

		nCurrentCar1++;
		if (nCurrentCar1 > nCarCount - 1)
		{
			nCurrentCar1 = 0;
		}

		fCar1Time = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nCarCount; i++)
	{
		pCar1[i]->Move();
		pCar1[i]->HitProcess();
		pCar1[i]->SetCollisionRect(10, 10, 100, 200);

		pCar1[i]->CollisionCheck(pPlayer);
		pCar1[i]->CollisionCheck(pEnemy);
		for (int j = 0; j < nCarCount; j++)
		{
			pCar1[i]->CollisionCheck(pCar2[j]);
			pCar1[i]->CollisionCheck(pCar1[i + 1]);
		}
	}
}

void ObjectManager::Car2Update()
{
	if (GATIMER()->GetAbsoluteFrame() - fCar2Time >= 350)
	{
		pCar2[nCurrentCar2]->Respawn();

		nCurrentCar2++;
		if (nCurrentCar2 > nCarCount - 1)
		{
			nCurrentCar2 = 0;
		}

		fCar2Time = GATIMER()->GetAbsoluteFrame();
	}

	for (int i = 0; i < nCarCount; i++)
	{
		pCar2[i]->Move();
		pCar2[i]->HitProcess();
		pCar2[i]->SetCollisionRect(10, 10, 100, 200);

		pCar2[i]->CollisionCheck(pPlayer);
		pCar2[i]->CollisionCheck(pEnemy);
		for (int j = 0; j < nCarCount; j++)
		{
			pCar2[i]->CollisionCheck(pCar1[j]);
			pCar2[i]->CollisionCheck(pCar2[i + 1]);
		}
	}
}

void ObjectManager::GoalUpdate()
{
	fGameTimer += 0.1f;

	printf("%f\n", fGameTimer);

	if (fGameTimer > 400)
	{
		pGoal->MoveY(-(pPlayer->GetSpeed()));
	}

	if (pGoal->GetPosition()->y <= -400)
	{
		if (pPlayer->GetDistance() >= pEnemy->GetDistance())
		{
			fFinishTime += 0.1f;
			if (fFinishTime > 10)
			{
				fFinishTime = 0.0f;
				Coin += 100;
				if (Coin >= 300)
				{
					GAAPP()->SetGameMode(GaApp::GameMode::ENDING);
				}
				else
				{
					GAAPP()->SetGameMode(GaApp::GameMode::MENU);
				}
			}
			pWin->SetVisible(true);
		}
		else if (pPlayer->GetDistance() < pEnemy->GetDistance())
		{
			fFinishTime += 0.1f;
			if (fFinishTime > 10)
			{
				fFinishTime = 0.0f;
				GAAPP()->SetGameMode(GaApp::GameMode::MENU);
			}
			pLose->SetVisible(true);
		}
	}	

	if (pPlayer->GetSpeed() >= 15)
	{
		pWind->SetVisible(true);

		if (lastFrame != GATIMER()->GetAbsoluteFrame() / 10)
		{
			pWind->SetRect(rtWind[WindCount++]);
			lastFrame = GATIMER()->GetAbsoluteFrame() / 10;
		}
		if (WindCount > 2)
		{
			WindCount = 0;
		}
	}
	else if (pPlayer->GetSpeed() < 15)
	{
		pWind->SetVisible(false);
	}
	pWind->SetPosition(pPlayer->GetPosition()->x, pPlayer->GetPosition()->y, 0);

	pMiniPlayer->MoveY((pPlayer->GetSpeed() * 0.002));
	pMiniEnemy->MoveY((pEnemy->GetSpeed() * 0.002));
}

void ObjectManager::Stage1Update()
{
	pStage1_Back1->MoveY(-(pPlayer->GetSpeed()));
	pStage1_Back2->MoveY(-(pPlayer->GetSpeed()));
	pStage1_Back3->MoveY(-(pPlayer->GetSpeed()));

	if (pStage1_Back1->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage1_Back1->GetPosition()->y;
		pStage1_Back1->SetPosition(0, (768 * 2) - posY, 0);
	}
	if (pStage1_Back2->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage1_Back2->GetPosition()->y;
		pStage1_Back2->SetPosition(0, (768 * 2) - posY, 0);
	}
	if (pStage1_Back3->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage1_Back3->GetPosition()->y;
		pStage1_Back3->SetPosition(0, (768 * 2) - posY, 0);
	}

	Car1Update();
	Car2Update();

	pPlayer->SetCollisionRect(10, 10, 100, 200);
	pPlayer->CollisionCheck(pEnemy);
	pPlayer->Process();

	pEnemy->SetCollisionRect(10, 10, 100, 200);
	pEnemy->Move(GATIMER()->GetAbsoluteFrame());

	GoalUpdate();
}

void ObjectManager::Stage2Update()
{
	pStage2_Back1->MoveY(-(pPlayer->GetSpeed()));
	pStage2_Back2->MoveY(-(pPlayer->GetSpeed()));
	pStage2_Back3->MoveY(-(pPlayer->GetSpeed()));

	if (pStage2_Back1->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage2_Back1->GetPosition()->y;
		pStage2_Back1->SetPosition(0, (768 * 2) - posY, 0);
	}
	if (pStage2_Back2->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage2_Back2->GetPosition()->y;
		pStage2_Back2->SetPosition(0, (768 * 2) - posY, 0);
	}
	if (pStage2_Back3->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage2_Back3->GetPosition()->y;
		pStage2_Back3->SetPosition(0, (768 * 2) - posY, 0);
	}

	Car1Update();
	Car2Update();

	pPlayer->SetCollisionRect(10, 10, 100, 200);
	pPlayer->CollisionCheck(pEnemy);
	pPlayer->Process();

	pEnemy->SetCollisionRect(10, 10, 120, 200);
	pEnemy->Move(GATIMER()->GetAbsoluteFrame());

	GoalUpdate();
}

void ObjectManager::Stage3Update()
{
	pStage3_Back1->MoveY(-(pPlayer->GetSpeed()));
	pStage3_Back2->MoveY(-(pPlayer->GetSpeed()));
	pStage3_Back3->MoveY(-(pPlayer->GetSpeed()));

	if (pStage3_Back1->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage3_Back1->GetPosition()->y;
		pStage3_Back1->SetPosition(0, (768 * 2) - posY, 0);
	}
	if (pStage3_Back2->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage3_Back2->GetPosition()->y;
		pStage3_Back2->SetPosition(0, (768 * 2) - posY, 0);
	}
	if (pStage3_Back3->GetPosition()->y <= -768)
	{
		float posY;

		posY = -768 - pStage3_Back3->GetPosition()->y;
		pStage3_Back3->SetPosition(0, (768 * 2) - posY, 0);
	}

	Car1Update();
	Car2Update();

	pPlayer->SetCollisionRect(10, 10, 100, 200);
	pPlayer->CollisionCheck(pEnemy);
	pPlayer->Process();

	pEnemy->SetCollisionRect(10, 10, 100, 200);
	pEnemy->Move(GATIMER()->GetAbsoluteFrame());

	GoalUpdate();
}

void ObjectManager::IntroRender(LPD3DXSPRITE sprite)
{
	sprite->SetTransform(&matScale);

	pIntro->Render(sprite);	
}

void ObjectManager::MenuRender(LPD3DXSPRITE sprite)
{
	sprite->SetTransform(&matScale);

	pMenu->Render(sprite);
}

void ObjectManager::ChooseRender(LPD3DXSPRITE sprite)
{
	pChoose->Render(sprite);
}

void ObjectManager::Stage1Render(LPD3DXSPRITE sprite)
{
	pStage1_Back1->Render(sprite);
	pStage1_Back2->Render(sprite);
	pStage1_Back3->Render(sprite);

	pGoal->Render(sprite);

	pPlayer->Render(sprite);
	pWind->Render(sprite);

	pEnemy->Render(sprite);

	for (int i = 0; i < nCarCount; i++)
	{
		pCar1[i]->Render(sprite);
		pCar2[i]->Render(sprite);
	}
	
	pUI->Render(sprite);

	pMiniPlayer->Render(sprite);
	pMiniEnemy->Render(sprite);

	sprintf_s(SpeedStr, "%0.0f\n", (pPlayer->GetSpeed() * 10));
	RECT SpeedRect = { 100, 598, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), SpeedStr, -1, &SpeedRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 200, 255));

	sprintf_s(CoinStr, "%d\n", Coin);
	RECT CoinRect = { 30, 10, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), CoinStr, -1, &CoinRect, DT_NOCLIP, D3DCOLOR_XRGB(100, 200, 0));

	pWin->Render(sprite);
	pLose->Render(sprite);
}

void ObjectManager::Stage2Render(LPD3DXSPRITE sprite)
{
	pStage2_Back1->Render(sprite);
	pStage2_Back2->Render(sprite);
	pStage2_Back3->Render(sprite);

	pGoal->Render(sprite);

	pPlayer->Render(sprite);
	pWind->Render(sprite);

	pEnemy->Render(sprite);

	for (int i = 0; i < nCarCount; i++)
	{
		pCar1[i]->Render(sprite);
		pCar2[i]->Render(sprite);
	}

	pUI->Render(sprite);

	pMiniPlayer->Render(sprite);
	pMiniEnemy->Render(sprite);

	sprintf_s(SpeedStr, "%0.0f\n", (pPlayer->GetSpeed() * 10));
	RECT SpeedRect = { 100, 598, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), SpeedStr, -1, &SpeedRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 200, 255));

	sprintf_s(CoinStr, "%d\n", Coin);
	RECT CoinRect = { 30, 10, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), CoinStr, -1, &CoinRect, DT_NOCLIP, D3DCOLOR_XRGB(100, 200, 0));

	pWin->Render(sprite);
	pLose->Render(sprite);
}

void ObjectManager::Stage3Render(LPD3DXSPRITE sprite)
{
	pStage3_Back1->Render(sprite);
	pStage3_Back2->Render(sprite);
	pStage3_Back3->Render(sprite);

	pGoal->Render(sprite);

	pPlayer->Render(sprite);
	pWind->Render(sprite);

	pEnemy->Render(sprite);
	
	for (int i = 0; i < nCarCount; i++)
	{
		pCar1[i]->Render(sprite);
		pCar2[i]->Render(sprite);
	}

	pUI->Render(sprite);

	pMiniPlayer->Render(sprite);
	pMiniEnemy->Render(sprite);

	sprintf_s(SpeedStr, "%0.0f\n", (pPlayer->GetSpeed() * 10));
	RECT SpeedRect = { 100, 598, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), SpeedStr, -1, &SpeedRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 200, 255));

	sprintf_s(CoinStr, "%d\n", Coin);
	RECT CoinRect = { 30, 10, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), CoinStr, -1, &CoinRect, DT_NOCLIP, D3DCOLOR_XRGB(100, 200, 0));

	pWin->Render(sprite);
	pLose->Render(sprite);
}

void ObjectManager::EndingRedner(LPD3DXSPRITE sprite)
{
	pEnding->Render(sprite);
}

void ObjectManager::KeyProc()
{
	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_RETURN))
		{
			D3DXMatrixScaling(&matScale, 1, 1, 1);
			GAAPP()->SetGameMode(GaApp::GameMode::MENU);
		}
		break;
	case GaApp::GameMode::MENU:
		break;
	case GaApp::GameMode::CHOOSE:
		break;
	case GaApp::GameMode::STAGE1:
	case GaApp::GameMode::STAGE2:
	case GaApp::GameMode::STAGE3:
		if (GetAsyncKeyState(VK_UP))
		{
			pPlayer->Move(LandRover::MotionState::UP);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			pPlayer->Move(LandRover::MotionState::LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			pPlayer->Move(LandRover::MotionState::RIGHT);
		}
		if (GetAsyncKeyState(VK_LSHIFT))
		{
			pPlayer->Break();
		}
		break;
	default:
		break;
	}
}

void ObjectManager::MouseProc()
{
	POINT MousePos;
	GetCursorPos(&MousePos);

	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		if (GAAPP()->GetClick())
		{
			D3DXMatrixScaling(&matScale, 1, 1, 1);
			GAAPP()->SetGameMode(GaApp::GameMode::MENU);
		}
		break;
	case GaApp::GameMode::MENU:
		// Set Menu Button Pos
		if (MousePos.x >= 537 && MousePos.x <= 902 &&
			MousePos.y >= 11 && MousePos.y <= 116)
		{
			RECT rt;
			rt.left = 1024;
			rt.right = rt.left + 1024;
			rt.top = 0;
			rt.bottom = 768;

			pMenu->SetRect(rt);

			if (GAAPP()->GetClick())
			{
				Reset();
				GAAPP()->SetGameMode(GaApp::GameMode::CHOOSE);
			}
		}
		else if (MousePos.x >= 643 && MousePos.x <= 1009 &&
				MousePos.y >= 236 && MousePos.y <= 341)
		{
			RECT rt;
			rt.left = 1024 + 1024;
			rt.right = rt.left + 1024;
			rt.top = 0;
			rt.bottom = 768;

			pMenu->SetRect(rt);
		}
		else if (MousePos.x >= 567 && MousePos.x <= 933 &&
			MousePos.y >= 488 && MousePos.y <= 596)
		{
			RECT rt;
			rt.left = 1024 + 1024 + 1024;
			rt.right = rt.left + 1024;
			rt.top = 0;
			rt.bottom = 768;

			pMenu->SetRect(rt);
		}
		else if (MousePos.x >= 324 && MousePos.x <= 694 &&
			MousePos.y >= 656 && MousePos.y <= 765)
		{
			RECT rt;
			rt.left = 1024 + 1024 + 1024 + 1024;
			rt.right = rt.left + 1024;
			rt.top = 0;
			rt.bottom = 768;

			pMenu->SetRect(rt);

			if (GAAPP()->GetClick())
			{
				PostQuitMessage(0);
			}
		}
		else
		{
			RECT rt;
			rt.left = 0;
			rt.right = 1024;
			rt.top = 0;
			rt.bottom = 768;

			pMenu->SetRect(rt);
		}
		break;
	case GaApp::GameMode::CHOOSE:
		if (MousePos.x >= 13 && MousePos.x <= 502 &&
			MousePos.y >= 14 && MousePos.y <= 370)
		{
			if (GAAPP()->GetClick())
			{
				GAAPP()->SetGameMode(GaApp::GameMode::STAGE1);
			}
		}
		else if (MousePos.x >= 522 && MousePos.x <= 1013 &&
				MousePos.y >= 14 && MousePos.y <= 370)
		{
			if (GAAPP()->GetClick())
			{
				GAAPP()->SetGameMode(GaApp::GameMode::STAGE2);
			}
		}
		else if (MousePos.x >= 165 && MousePos.x <= 849 &&
				MousePos.y >= 391 && MousePos.y <= 748)
		{
			if (GAAPP()->GetClick())
			{
				GAAPP()->SetGameMode(GaApp::GameMode::STAGE3);
			}
		}
		Reset();
		break;
	default:
		break;
	}
}

void ObjectManager::Reset()
{
	Create();
}