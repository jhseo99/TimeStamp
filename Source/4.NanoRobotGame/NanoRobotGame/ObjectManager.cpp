#include "stdafx.h"

ObjectManager ObjectManager::singleton;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Create()
{
	fGameTime = 0.0f;

	PlayerHP = 5;
	HumanHP = 100;

	fGraphTime = 0.0f;
	fGameSpeed = 0.5f;

	nRedCount = 10;
	nCurrentRed = 0;
	fRedTimer = 0.0f;

	nVirusCount = 20;
	nCurrentVirus = 0;
	fVirusTimer = 0.0f;

	nWhiteCount = 20;
	nCurrentWhite = 0;
	fWhiteTimer = 0.0f;

	nBacteriaCount = 20;
	nCurrentBacteria = 0;
	fBacteriaTimer = 0.0f;

	LoadFile();
}

void ObjectManager::ProcessAll()
{
	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		IntroUpdate();
		break;
	case GaApp::GameMode::MENU:
		IntroUpdate();
		for (int i = 0; i < 4; i++)
		{
			if (i % 2 != 0)
			{
				m_pButton[i]->MoveX(20.0);
				if (m_pButton[i]->GetPosition()->x >= 387)
				{
					m_pButton[i]->GetPosition()->x = 387;
				}
			}
			else
			{
				m_pButton[i]->MoveX(-20.0);
				if (m_pButton[i]->GetPosition()->x <= 387)
				{
					m_pButton[i]->GetPosition()->x = 387;
				}
			}
		}
		m_pTitle->SetVisible(true);
		break;
	case GaApp::GameMode::STAGE1:
		Stage1Update();
		break;
	case GaApp::GameMode::STAGE2:
		Stage2Update();
		break;
	default:
		break;
	}

	if (PlayerHP <= 0 || HumanHP < 0)
	{
		GAAPP()->SetGameMode(GaApp::GameMode::DIE);
	}
}

void ObjectManager::LoadFile()
{
	AddTexture(GaBase::TextureID::INTRO, L"Texture\\Intro.png");
	AddTexture(GaBase::TextureID::GRAPH, L"Texture\\Graph.png");
	AddTexture(GaBase::TextureID::SMOKE, L"Texture\\Smoke.png");
	AddTexture(GaBase::TextureID::BUTTON, L"Texture\\Button.png");
	AddTexture(GaBase::TextureID::TITLE, L"Texture\\Title.png");
	AddTexture(GaBase::TextureID::UI, L"Texture\\UI.png");
	AddTexture(GaBase::TextureID::HEART, L"Texture\\Heart.png");
	AddTexture(GaBase::TextureID::HP, L"Texture\\HP.png");
	AddTexture(GaBase::TextureID::STAGE1, L"Texture\\Stage1.png");
	AddTexture(GaBase::TextureID::STAGE2, L"Texture\\Stage2.png");
	AddTexture(GaBase::TextureID::PLAYER, L"Texture\\Player.png");
	AddTexture(GaBase::TextureID::RED_ENEMY, L"Texture\\RedEnemy.png");
	AddTexture(GaBase::TextureID::VIRUS, L"Texture\\Virus.png");
	AddTexture(GaBase::TextureID::WHITE_ENEMY, L"Texture\\WhiteEnemy.png");
	AddTexture(GaBase::TextureID::BACTERIA, L"Texture\\Bacteria.png");
	AddTexture(GaBase::TextureID::CANCER1, L"Texture\\Cancer1.png");
	AddTexture(GaBase::TextureID::CANCER2, L"Texture\\Cancer2.png");
	AddTexture(GaBase::TextureID::MISSILE, L"Texture\\Missile.png");
	AddTexture(GaBase::TextureID::DIE, L"Texture\\Die.png");
	AddTexture(GaBase::TextureID::ENDING, L"Texture\\Ending.png");

	AddObject();
}

void ObjectManager::AddObject()
{
	m_pIntro = new GameObject(GetTexture(GaBase::TextureID::INTRO), 1024, 768);

	m_pDie = new GameObject(GetTexture(GaBase::TextureID::DIE), 1024, 768);
	m_pEnding = new GameObject(GetTexture(GaBase::TextureID::ENDING), 1024, 768);
	for (int i = 0; i < GRAPH_MAX; i++)
	{
		m_pGraph[i] = new GameObject(GetTexture(GaBase::TextureID::GRAPH), 5, 260);
		
		// Set Board Position --> x = 209, y = 107
		m_pGraph[i]->SetPosition(209 + (5 * i), 107, 0);
	}

	m_pSmoke = new GameObject(GetTexture(GaBase::TextureID::SMOKE), 1024, 768);
	m_pTitle = new GameObject(GetTexture(GaBase::TextureID::TITLE), 1024, 768);
	m_pTitle->SetVisible(false);

	for (int i = 0; i < 4; i++)
	{
		RECT rc;
		rc.left = i * 250;
		rc.right = rc.left + 250;
		rc.top = 0;
		rc.bottom = 60;

		m_pButton[i] = new GameObject(GetTexture(GaBase::TextureID::BUTTON), 250, 60);

		m_pButton[i]->SetRect(rc);
		if (i % 2 != 0)
		{
			m_pButton[i]->SetPosition(-250, (420 + (i * 80)), 0);
		}
		else
		{
			m_pButton[i]->SetPosition(1024, (420 + (i * 80)), 0);
		}
	}

	m_pUI = new GameObject(GetTexture(GaBase::TextureID::UI), 1024, 768);
	m_pHeart = new GameObject(GetTexture(GaBase::TextureID::HEART), 70, 100);
	m_pHeart->SetPosition(950, 10, 0);

	for (int i = 0; i < 5; i++)
	{
		m_pHP[i] = new GameObject(GetTexture(GaBase::TextureID::HP), 50, 40);
		m_pHP[i]->SetPosition(10 + (i * 55), 715, 0);
	}

	m_pStage1 = new GameObject(GetTexture(GaBase::TextureID::STAGE1), 1024, 768);
	m_pStage2 = new GameObject(GetTexture(GaBase::TextureID::STAGE2), 1024, 768);

	m_pPlayer = new Player(GetTexture(GaBase::TextureID::PLAYER));

	for (int i = 0; i < nRedCount; i++)
	{
		m_pRedEnemy[i] = new RedEnemy(GetTexture(GaBase::TextureID::RED_ENEMY));
	}

	for (int i = 0; i < nVirusCount; i++)
	{
		m_pVirus[i] = new Virus(GetTexture(GaBase::TextureID::VIRUS));
	}

	for (int i = 0; i < nWhiteCount; i++)
	{
		m_pWhite[i] = new WhiteEnemy(GetTexture(GaBase::TextureID::WHITE_ENEMY));
	}

	for (int i = 0; i < nBacteriaCount; i++)
	{
		m_pBacteria[i] = new Bacteria(GetTexture(GaBase::TextureID::BACTERIA));
	}

	m_pCancer1 = new Cancer(GetTexture(GaBase::TextureID::CANCER1));
	m_pCancer2 = new Cancer(GetTexture(GaBase::TextureID::CANCER2));
}

HRESULT ObjectManager::AddTexture(DWORD id, TCHAR* filename)
{
	HRESULT hRet = S_OK;
	LPDIRECT3DTEXTURE9 texture;

	hRet = D3DXCreateTextureFromFileEx(
		GAAPP()->GetDevice(),
		filename,
		D3DX_DEFAULT, D3DX_DEFAULT,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
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

void ObjectManager::IntroUpdate()
{
	fGraphTime += fGameSpeed;

	// Process Graph
	if (fGraphTime >= 1 && fGraphTime < 132)
	{
		m_pGraph[(int)fGraphTime]->SetVisible(false);
	}
	if (fGraphTime >= 150 || fGraphTime <= 0)
	{
		fGameSpeed = -fGameSpeed;
		for (int i = 0; i < GRAPH_MAX; i++)
		{
			m_pGraph[i]->SetVisible(true);
		}
	}

	// Process Smoke
	if (fGraphTime >= 100)
	{
		m_pSmoke->SetColorAlpha(1.0f);
	}
	else
	{
		m_pSmoke->SetColorAlpha((fGraphTime * 0.01));
	}
}

void ObjectManager::Stage1Update()
{
	fGameTime += 0.1f;

	RedUpdate();
	VirusUpdate();
	WhiteUpdate();
	BacteriaUpdate();

	m_pPlayer->Update();
	m_pPlayer->SetCollisonRect(0, 30, 125, 25);

	for (int i = 0; i < 100; i++)
	{
		m_pPlayer->GetMissile(i)->Shoot();
		m_pPlayer->GetMissile(i)->SetCollisonRect(0, 0, 80, 15);
	}

	if (fGameTime >= 200 && fGameTime < 201)
	{
		m_pCancer1->SetVisible(true);
		m_pCancer1->SetPosition(1024, 240, 0);
	}

	m_pCancer1->SetCollisonRect(0, 100, 280, 80);
	m_pCancer1->Animation();
	m_pCancer1->Move(Cancer::MotionState::LEFT);
	for (int i = 0; i < 100; i++)
	{
		m_pCancer1->CollisonCheck(m_pPlayer->GetMissile(i));
	}

	if (m_pCancer1->GetClear())
	{
		m_pCancer1->SetClear(false);
		GAAPP()->SetGameMode(GaApp::GameMode::STAGE2);
		Reset();
	}
}

void ObjectManager::Stage2Update()
{
	fGameTime += 0.1f;

	RedUpdate();
	VirusUpdate();
	WhiteUpdate();
	BacteriaUpdate();

	m_pPlayer->Update();
	m_pPlayer->SetCollisonRect(0, 30, 125, 25);

	for (int i = 0; i < 100; i++)
	{
		m_pPlayer->GetMissile(i)->Shoot();
		m_pPlayer->GetMissile(i)->SetCollisonRect(0, 0, 80, 15);
	}

	if (fGameTime >= 100 && fGameTime < 101)
	{
		m_pCancer2->SetVisible(true);
		m_pCancer2->SetPosition(1024, 240, 0);
	}

	m_pCancer2->SetCollisonRect(0, 100, 280, 80);
	m_pCancer2->Animation();
	m_pCancer2->Move(Cancer::MotionState::LEFT);
	for (int i = 0; i < 100; i++)
	{
		m_pCancer2->CollisonCheck(m_pPlayer->GetMissile(i));
	}

	if (m_pCancer2->GetClear())
	{
		m_pCancer2->SetClear(false);
		GAAPP()->SetGameMode(GaApp::GameMode::ENDING);
	}
}

void ObjectManager::RedUpdate()
{
	fRedTimer += 0.1f;

	if (fRedTimer > 70)
	{
		int randYPos = GATIMER()->GetRand(600);
		m_pRedEnemy[nCurrentRed]->SetVisible(true);
		m_pRedEnemy[nCurrentRed]->SetPosition(1024, randYPos, 0);

		nCurrentRed++;

		if (nCurrentRed > nRedCount - 1)
		{
			nCurrentRed = 0;
		}

		fRedTimer = 0.0f;
	}

	for (int i = 0; i < nRedCount; i++)
	{
		m_pRedEnemy[i]->SetCollisonRect(0, 0, 120, 110);
		m_pRedEnemy[i]->Move(RedEnemy::MotionState::LEFT);
		m_pRedEnemy[i]->Animation();
		for (int j = 0; j < 100; j++)
		{
			m_pRedEnemy[i]->CollisonCheck(m_pPlayer->GetMissile(j));
		}
	}
}

void ObjectManager::VirusUpdate()
{
	fVirusTimer += 0.1f;

	if (fVirusTimer > 40)
	{
		int randYPos = GATIMER()->GetRand(600);
		m_pVirus[nCurrentVirus]->SetVisible(true);
		m_pVirus[nCurrentVirus]->SetPosition(1024, randYPos, 0);

		nCurrentVirus++;

		if (nCurrentVirus > nVirusCount - 1)
		{
			nCurrentVirus = 0;
		}

		fVirusTimer = 0.0f;
	}

	for (int i = 0; i < nVirusCount; i++)
	{
		m_pVirus[i]->SetCollisonRect(0, 0, 90, 90);
		
		switch (m_pVirus[i]->GetRandNum())
		{
		case 0:
			m_pVirus[i]->Move(Virus::MotionState::DOWN);
			break;
		case 1:
			m_pVirus[i]->Move(Virus::MotionState::UP);
			break;
		default:
			break;
		}

		m_pVirus[i]->Move(Virus::MotionState::LEFT);
		m_pVirus[i]->Animation();
		m_pPlayer->CollisonCheck(m_pVirus[i]);
		for (int j = 0; j < 100; j++)
		{
			m_pVirus[i]->CollisonCheck(m_pPlayer->GetMissile(j));
		}
	}
}

void ObjectManager::WhiteUpdate()
{
	fWhiteTimer += 0.1f;

	if (fWhiteTimer > 60)
	{
		int randYPos = GATIMER()->GetRand(600);
		m_pWhite[nCurrentWhite]->SetVisible(true);
		m_pWhite[nCurrentWhite]->SetPosition(1024, randYPos, 0);

		nCurrentWhite++;

		if (nCurrentWhite > nWhiteCount - 1)
		{
			nCurrentWhite = 0;
		}

		fWhiteTimer = 0.0f;
	}

	for (int i = 0; i < nWhiteCount; i++)
	{
		m_pWhite[i]->SetCollisonRect(0, 0, 80, 80);

		switch (m_pWhite[i]->GetRandNum())
		{
		case 0:
			m_pWhite[i]->Move(WhiteEnemy::MotionState::DOWN);
			break;
		case 1:
			m_pWhite[i]->Move(WhiteEnemy::MotionState::UP);
			break;
		default:
			break;
		}

		m_pWhite[i]->Move(WhiteEnemy::MotionState::LEFT);
		m_pWhite[i]->Animation();
		for (int j = 0; j < 100; j++)
		{
			m_pWhite[i]->CollisonCheck(m_pPlayer->GetMissile(j));
		}
	}
}

void ObjectManager::BacteriaUpdate()
{
	fBacteriaTimer += 0.1f;

	if (fBacteriaTimer> 20)
	{
		int randYPos = GATIMER()->GetRand(600);
		m_pBacteria[nCurrentBacteria]->SetVisible(true);
		m_pBacteria[nCurrentBacteria]->SetPosition(1024, randYPos, 0);

		nCurrentBacteria++;

		if (nCurrentBacteria > nBacteriaCount - 1)
		{
			nCurrentBacteria = 0;
		}

		fBacteriaTimer = 0.0f;
	}

	for (int i = 0; i < nBacteriaCount; i++)
	{
		m_pBacteria[i]->SetCollisonRect(0, 10, 270, 50);

		switch (m_pBacteria[i]->GetRandNum())
		{
		case 0:
			m_pBacteria[i]->Move(Bacteria::MotionState::DOWN);
			break;
		case 1:
			m_pBacteria[i]->Move(Bacteria::MotionState::UP);
			break;
		default:
			break;
		}

		m_pBacteria[i]->Move(Bacteria::MotionState::LEFT);
		m_pBacteria[i]->Animation();
		for (int j = 0; j < 100; j++)
		{
			m_pBacteria[i]->CollisonCheck(m_pPlayer->GetMissile(j));
		}
	}
}

void ObjectManager::MainRender(LPD3DXSPRITE sprite)
{
	m_pIntro->Render(sprite);

	for (int i = 0; i < GRAPH_MAX; i++)
	{
		m_pGraph[i]->Render(sprite);
	}

	m_pSmoke->Render(sprite);

	for (int i = 0; i < 4; i++)
	{
		m_pButton[i]->Render(sprite);
	}

	m_pTitle->Render(sprite);
}

void ObjectManager::Stage1Render(LPD3DXSPRITE sprite)
{
	m_pStage1->Render(sprite);
	m_pPlayer->Render(sprite);

	for (int i = 0; i < 100; i++)
	{
		m_pPlayer->GetMissile(i)->Render(sprite);
	}

	for (int i = 0; i < nRedCount; i++)
	{
		m_pRedEnemy[i]->Render(sprite);
	}

	for (int i = 0; i < nVirusCount; i++)
	{
		m_pVirus[i]->Render(sprite);
	}

	for (int i = 0; i < nWhiteCount; i++)
	{
		m_pWhite[i]->Render(sprite);
	}

	for (int i = 0; i < nBacteriaCount; i++)
	{
		m_pBacteria[i]->Render(sprite);
	}

	m_pCancer1->Render(sprite);

	m_pUI->Render(sprite);
	m_pHeart->Render(sprite);

	for (int i = 0; i < PlayerHP; i++)
	{
		m_pHP[i]->Render(sprite);
	}

	sprintf_s(HumanHPstr, "%d\n", HumanHP);
	RECT HumanRect = { 800, 15, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), HumanHPstr, -1, &HumanRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 150, 0));
}

void ObjectManager::Stage2Render(LPD3DXSPRITE sprite)
{
	m_pStage2->Render(sprite);
	m_pPlayer->Render(sprite);

	for (int i = 0; i < 100; i++)
	{
		m_pPlayer->GetMissile(i)->Render(sprite);
	}

	for (int i = 0; i < nRedCount; i++)
	{
		m_pRedEnemy[i]->Render(sprite);
	}

	for (int i = 0; i < nVirusCount; i++)
	{
		m_pVirus[i]->Render(sprite);
	}

	for (int i = 0; i < nWhiteCount; i++)
	{
		m_pWhite[i]->Render(sprite);
	}

	for (int i = 0; i < nBacteriaCount; i++)
	{
		m_pBacteria[i]->Render(sprite);
	}

	m_pCancer2->Render(sprite);

	m_pUI->Render(sprite);
	m_pHeart->Render(sprite);

	for (int i = 0; i < PlayerHP; i++)
	{
		m_pHP[i]->Render(sprite);
	}

	sprintf_s(HumanHPstr, "%d\n", HumanHP);
	RECT HumanRect = { 800, 15, 0, 0 };
	GAAPP()->GetFont()->DrawTextA(GAAPP()->GetSprite(), HumanHPstr, -1, &HumanRect, DT_NOCLIP, D3DCOLOR_XRGB(0, 150, 0));
}

void ObjectManager::DieRender(LPD3DXSPRITE sprite)
{
	m_pDie->Render(sprite);
}

void ObjectManager::EndingRender(LPD3DXSPRITE sprite)
{
	m_pEnding->Render(sprite);
}

void ObjectManager::KeyProc()
{
	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE))
		{
			GAAPP()->SetGameMode(GaApp::GameMode::MENU);
		}
		break;
	case GaApp::GameMode::MENU:
		break;
	case GaApp::GameMode::STAGE1:
	case GaApp::GameMode::STAGE2:
		if (GetAsyncKeyState(VK_UP))
		{
			m_pPlayer->Move(Player::MotionState::UP);
			m_pPlayer->SetMotion(Player::MotionState::UP);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_pPlayer->Move(Player::MotionState::DOWN);
			m_pPlayer->SetMotion(Player::MotionState::DOWN);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_pPlayer->Move(Player::MotionState::RIGHT);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_pPlayer->Move(Player::MotionState::LEFT);
		}
		if (!(GetAsyncKeyState(VK_DOWN)) && !(GetAsyncKeyState(VK_UP)))
		{
			m_pPlayer->SetMotion(Player::MotionState::NORMAL);
		}
		if (GetAsyncKeyState(VK_LCONTROL))
		{
			m_pPlayer->Shot(GATIMER()->GetAbsoluteFrame());
		}
		break;
	case GaApp::GameMode::DIE:
	case GaApp::GameMode::ENDING:
		if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE))
		{
			GAAPP()->SetGameMode(GaApp::GameMode::MENU);
			Reset();
		}
		break;
	default:
		break;
	}
}

void ObjectManager::MouseProc()
{
	POINT pos;
	GetCursorPos(&pos);

	switch (GAAPP()->GetGameMode())
	{
	case GaApp::GameMode::INTRO:
		break;
	case GaApp::GameMode::MENU:
		if (pos.x > m_pButton[0]->GetPosition()->x &&
			pos.x < m_pButton[0]->GetPosition()->x + 250 &&
			pos.y > m_pButton[0]->GetPosition()->y &&
			pos.y < m_pButton[0]->GetPosition()->y + 60)
		{
			if (GAAPP()->GetClick())
			{
				GAAPP()->SetGameMode(GaApp::GameMode::STAGE1);
			}
		}
		else if (pos.x > m_pButton[1]->GetPosition()->x &&
				pos.x < m_pButton[1]->GetPosition()->x + 250 &&
				pos.y > m_pButton[1]->GetPosition()->y &&
				pos.y < m_pButton[1]->GetPosition()->y + 60)
		{
		
		}
		else if (pos.x > m_pButton[2]->GetPosition()->x &&
				pos.x < m_pButton[2]->GetPosition()->x + 250 &&
				pos.y > m_pButton[2]->GetPosition()->y &&
				pos.y < m_pButton[2]->GetPosition()->y + 60)
		{
		
		}
		else if (pos.x > m_pButton[3]->GetPosition()->x &&
				pos.x < m_pButton[3]->GetPosition()->x + 250 &&
				pos.y > m_pButton[3]->GetPosition()->y &&
				pos.y < m_pButton[3]->GetPosition()->y + 60)
		{
		}
		break;
	case GaApp::GameMode::STAGE1:
	case GaApp::GameMode::STAGE2:
		break;
	default:
		break;
	}
}

void ObjectManager::Reset()
{
	this->Create();

	for (int i = 0; i < 100; i++)
	{
		m_pPlayer->GetMissile(i)->SetVisible(false);
	}

	for (int i = 0; i < nRedCount; i++)
	{
		m_pRedEnemy[i]->SetVisible(false);
	}

	for (int i = 0; i < nWhiteCount; i++)
	{
		m_pVirus[i]->SetVisible(false);
		m_pWhite[i]->SetVisible(false);
		m_pBacteria[i]->SetVisible(false);
	}

	m_pCancer1->SetVisible(false);
	m_pCancer2->SetVisible(false);
}