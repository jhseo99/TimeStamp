#include "DXUT.h"
#include "GaBase.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}


void Stage::Create(LPDIRECT3DDEVICE9 pd3dDevice)
{
	this->pd3dDevice = pd3dDevice;
	currentStage = StageState::SELECT;

	D3DXCreateSprite(pd3dDevice, &pFontSprite);
	D3DXCreateFont(pd3dDevice, 50, 0, FW_BOLD, 1, TRUE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"comic sans MS", &pFont);

	pSelectHorse = new RenderObject;
	pSelectHorse->CreateTexture(pd3dDevice, L"texture\\HorseSelect.png");
	pSelectHorse->SetRect(0, 800, 0, 600);
	pSelectHorse->SetTranslate(0, 0);
	pSelectHorse->SetPosition(0, 0, 0);
	pSelectHorse->SetVisible(true);

	pShop = new RenderObject;
	pShop->CreateTexture(pd3dDevice, L"texture\\shop.png");
	pShop->SetRect(0, 800, 0, 600);
	pShop->SetTranslate(0, 0);
	pShop->SetPosition(0, 0, 0);
	pShop->SetVisible(true);

	pLight = new RenderObject;
	pLight->CreateTexture(pd3dDevice, L"texture\\light.png");
	pLight->SetRect(0, 800, 0, 600);
	pLight->SetTranslate(0, 0);
	pLight->SetPosition(0, 0, 0);
	pLight->SetVisible(true);

	pCountDown = new CountDown(pd3dDevice);
	pCountDown->SetStartTime(GATIMER()->GetTimer());

	pUI = new RenderObject;
	pUI->CreateTexture(pd3dDevice, L"texture\\ui.png");
	pUI->SetRect(0, 800, 0, 600);
	pUI->SetTranslate(0, 0);
	pUI->SetPosition(0, 0, 0);
	pUI->SetVisible(true);

	for (int i = 0; i < 200; i++)
	{
		pStamina[i] = new RenderObject;
		pStamina[i]->CreateTexture(pd3dDevice, L"texture\\stamina.png");
		pStamina[i]->SetRect(0, 1, 0, 22);
		pStamina[i]->SetTranslate(0, 0);
		pStamina[i]->SetPosition(171 + i, 505, 0);
		pStamina[i]->SetVisible(true);
	}

	pHorseName = new RenderObject;
	pHorseName->CreateTexture(pd3dDevice, L"texture\\HorseName.png");
	pHorseName->SetRect(0, 140, 0, 145);
	pHorseName->SetTranslate(0, 0);
	pHorseName->SetPosition(10, 430, 0);
	pHorseName->SetVisible(true);

	InitStage1();
}

void Stage::InitStage1()
{
	pVecRenderObject.clear();

	pTrack = new Track(pd3dDevice, L"texture\\track.png");
	pTrack->SetRect(0, 12200, 0, 5328);
	pTrack->SetTranslate(0, 0);
	pTrack->SetPosition(-7592, -4382, 0);
	pTrack->SetVisible(true);
	pVecRenderObject.push_back(pTrack);

	pStartPoint = new RenderObject;
	pStartPoint->CreateTexture(pd3dDevice, L"texture\\startpoint.png");
	pStartPoint->SetRect(0, 213, 0, 499);
	pStartPoint->SetTranslate(0, 0);
	pStartPoint->SetPosition(300, 30, 0);
	pStartPoint->SetVisible(true);
	pVecRenderObject.push_back(pStartPoint);

	pPlayer = new PlayerHorse(pd3dDevice, L"texture\\horse.png");
	pPlayer->SetPosition(300, 200, 0);
	pPlayer->SetHorseID(Horse::HorseID::JEJU);

	pHorseAI[0] = new HorseAI(pd3dDevice, L"texture\\horse1.png");
	pHorseAI[0]->SetPosition(300, 0, 0);
	pHorseAI[0]->SetGamePos(0, -200);
	pHorseAI[0]->SetHorseID(Horse::HorseID::BUSAN);
	pVecRenderObject.push_back(pHorseAI[0]);

	pHorseAI[1] = new HorseAI(pd3dDevice, L"texture\\horse2.png");
	pHorseAI[1]->SetPosition(300, 100, 0);
	pHorseAI[1]->SetGamePos(0, -100);
	pHorseAI[1]->SetHorseID(Horse::HorseID::SEOUL);
	pVecRenderObject.push_back(pHorseAI[1]);

	pHorseAI[2] = new HorseAI(pd3dDevice, L"texture\\horse3.png");
	pHorseAI[2]->SetPosition(300, 300, 0);
	pHorseAI[2]->SetGamePos(0, 100);
	pHorseAI[2]->SetHorseID(Horse::HorseID::KWANGJU);
	pVecRenderObject.push_back(pHorseAI[2]);

	pItem[0] = new Item(pd3dDevice, L"texture\\item1.png");
	pItem[0]->SetPosition(-4577, -3700, 0);
	pItem[0]->SetGamePos(-4877, -3900);
	pItem[0]->SetID(Item::ItemID::MONEY);
	pVecRenderObject.push_back(pItem[0]);

	pItem[1] = new Item(pd3dDevice, L"texture\\item4.png");
	pItem[1]->SetPosition(-4577, -3900, 0);
	pItem[1]->SetGamePos(-4877, -4100);
	pItem[1]->SetID(Item::ItemID::SHEILD);
	pVecRenderObject.push_back(pItem[1]);

	pItem[2] = new Item(pd3dDevice, L"texture\\item3.png");
	pItem[2]->SetPosition(1557, 100, 0);
	pItem[2]->SetGamePos(1257, -100);
	pItem[2]->SetID(Item::ItemID::WIND);
	pVecRenderObject.push_back(pItem[2]);

	pItem[3] = new Item(pd3dDevice, L"texture\\item2.png");
	pItem[3]->SetPosition(1557, 300, 0);
	pItem[3]->SetGamePos(1257, 100);
	pItem[3]->SetID(Item::ItemID::BOOST);
	pVecRenderObject.push_back(pItem[3]);

	pItemIcon = new RenderObject;
	pItemIcon->CreateTexture(pd3dDevice, L"texture\\ItemIcon.png");
	pItemIcon->SetRect(0, 80, 0, 80);
	pItemIcon->SetTranslate(0, 0);
	pItemIcon->SetPosition(700, 505, 0);
	pItemIcon->SetVisible(true);
	pVecHorses.clear();

	pVecHorses.push_back(pPlayer);
	pVecHorses.push_back(pHorseAI[0]);
	pVecHorses.push_back(pHorseAI[1]);
	pVecHorses.push_back(pHorseAI[2]);

	pMinimap = new RenderObject;
	pMinimap->CreateTexture(pd3dDevice, L"texture\\minimap.png");
	pMinimap->SetRect(0, 336, 0, 140);
	pMinimap->SetTranslate(0, 0);
	pMinimap->SetPosition(450, 20, 0);
	pMinimap->SetVisible(true);

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pIcon[i] = new RenderObject;
		switch (i)
		{
		case 0:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon.png");
			break;
		case 1:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon1.png");
			break;
		case 2:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon2.png");
			break;
		case 3:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon3.png");
			break;
		default:
			break;
		}
		pIcon[i]->SetRect(0, 4, 0, 4);
		pIcon[i]->SetTranslate(0, 0);
		pIcon[i]->SetPosition(450 + 221, 150 + (4 * i), 0);
		pIcon[i]->SetVisible(true);
	}

	bStart = false;

	fStartLineX = 7892.0f;
	fStartLineY = 4682.0f;

	pVecHorseRank.clear();
}

void Stage::InitStage2()
{
	pVecRenderObject.clear();

	pBeach = new Beach(pd3dDevice, L"texture\\beach.png");
	pBeach->SetRect(0, 10000, 0, 7000);
	pBeach->SetTranslate(0, 0);
	pBeach->SetPosition(-1841, -634, 0);
	pBeach->SetVisible(true);
	pVecRenderObject.push_back(pBeach);

	pStartPoint->SetTranslate(0, 0);
	pStartPoint->SetPosition(300, 30, 0);
	pStartPoint->SetVisible(true);
	pVecRenderObject.push_back(pStartPoint);

	pPlayer->SetPosition(300, 200, 0);
	pPlayer->SetGamePos(0, 0);

	pHorseAI[0]->SetPosition(300, 0, 0);
	pHorseAI[0]->SetGamePos(0, -200);
	pVecRenderObject.push_back(pHorseAI[0]);

	pHorseAI[1]->SetPosition(300, 100, 0);
	pHorseAI[1]->SetGamePos(0, -100);
	pVecRenderObject.push_back(pHorseAI[1]);

	pHorseAI[2]->SetPosition(300, 300, 0);
	pHorseAI[2]->SetGamePos(0, 100);
	pVecRenderObject.push_back(pHorseAI[2]);

	pItem[0]->SetPosition(-4577, -3700, 0);
	pItem[0]->SetGamePos(-4877, -3900);
	pItem[0]->SetVisible(true);
	pVecRenderObject.push_back(pItem[0]);

	pItem[1]->SetPosition(-4577, -3900, 0);
	pItem[1]->SetGamePos(-4877, -4100);
	pItem[1]->SetVisible(true);
	pVecRenderObject.push_back(pItem[1]);

	pItem[2]->SetPosition(1557, 100, 0);
	pItem[2]->SetGamePos(1257, -100);
	pItem[2]->SetVisible(true);
	pVecRenderObject.push_back(pItem[2]);

	pItem[3]->SetPosition(1557, 300, 0);
	pItem[3]->SetGamePos(1257, 100);
	pItem[3]->SetVisible(true);
	pVecRenderObject.push_back(pItem[3]);

	pVecHorses.clear();

	pVecHorses.push_back(pPlayer);
	pVecHorses.push_back(pHorseAI[0]);
	pVecHorses.push_back(pHorseAI[1]);
	pVecHorses.push_back(pHorseAI[2]);

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pVecHorses[i]->Clear();
	}

	pCountDown->SetStartTime(GATIMER()->GetTimer());
	pCountDown->SetVisible(true);

	pMinimap->CreateTexture(pd3dDevice, L"texture\\minimap2.png");
	pMinimap->SetRect(0, 261, 0, 171);
	pMinimap->SetTranslate(0, 0);
	pMinimap->SetPosition(440, 20, 0);
	pMinimap->SetVisible(true);

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pIcon[i] = new RenderObject;
		switch (i)
		{
		case 0:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon.png");
			break;
		case 1:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon1.png");
			break;
		case 2:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon2.png");
			break;
		case 3:
			pIcon[i]->CreateTexture(pd3dDevice, L"texture\\icon3.png");
			break;
		default:
			break;
		}
		pIcon[i]->SetRect(0, 4, 0, 4);
		pIcon[i]->SetTranslate(0, 0);
		pIcon[i]->SetPosition(440 + 35, 20 + (4 * i), 0);
		pIcon[i]->SetVisible(true);
	}

	bStart = false;

	fStartLineX = 2141.0f;
	fStartLineY = 934.0f;

	pVecHorseRank.clear();
}

void Stage::Update()
{
	switch (currentStage)
	{
	case StageState::SELECT:
		SelectUpdate();
		break;
	case StageState::STAGE1:
		Stage1Update();
		break;
	case StageState::SHOP:
		ShopUpdate();
		break;
	case StageState::STAGE2:
		Stage2Update();
		break;
	default:
		break;
	}
}


void Stage::SelectUpdate()
{
	POINT pt;
	GetCursorPos(&pt);

	if (SCENEMANAGER()->bCurrentClick)
	{
		if (pt.x > 63 && pt.x < 225
			&& pt.y > 186 && pt.y < 349)
		{
			pPlayer->SetHorseID(Horse::HorseID::BUSAN);
			pHorseName->SetRect(140, 280, 0, 145);
			CallStage();
		}
		else if (pt.x > 233 && pt.x < 393
			&& pt.y > 186 && pt.y < 349)
		{
			pPlayer->SetHorseID(Horse::HorseID::SEOUL);
			pHorseName->SetRect(420, 560, 0, 145);
			CallStage();
		}
		else if (pt.x > 403 && pt.x < 565
			&& pt.y > 186 && pt.y < 349)
		{
			pPlayer->SetHorseID(Horse::HorseID::KWANGJU);
			pHorseName->SetRect(280, 420, 0, 145);
			CallStage();
		}
		else if (pt.x > 574 && pt.x < 733
			&& pt.y > 186 && pt.y < 349)
		{
			pPlayer->SetHorseID(Horse::HorseID::JEJU);
			pHorseName->SetRect(0, 140, 0, 145);
			CallStage();
		}
	}
}

void Stage::CallStage()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		if (i != 0)
		{
			int nRand = rand() % 4;
			switch (nRand)
			{
			case 0:
				pVecHorses[i]->SetHorseID(Horse::HorseID::BUSAN);
				break;
			case 1:
				pVecHorses[i]->SetHorseID(Horse::HorseID::SEOUL);
				break;
			case 2:
				pVecHorses[i]->SetHorseID(Horse::HorseID::KWANGJU);
				break;
			case 3:
				pVecHorses[i]->SetHorseID(Horse::HorseID::JEJU);
				break;
			default:
				break;
			}
		}
		for (int j = 0; j < i; j++)
		{
			if (pVecHorses[i]->GetHorseID() == pVecHorses[j]->GetHorseID())
			{
				i = i - 1;
				break;
			}
		}
		if (i >= 3)
		{
			SCENEMANAGER()->SceneChange();
			currentStage = StageState::STAGE1;
		}
	}
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pVecHorses[i]->SetHorseStat(pd3dDevice);
	}
}

void Stage::ShopUpdate()
{
	POINT pt;
	GetCursorPos(&pt);

	if (SCENEMANAGER()->bCurrentClick)
	{
		if (pt.x > 567 && pt.x < 659
			&& pt.y > 189 && pt.y < 227
			&& pPlayer->GetMoney() >= 70)
		{
			pPlayer->SetMoney(pPlayer->GetMoney() - 70);
			pPlayer->SetMaxStamina(pPlayer->GetMaxStamina() + 5);
		}
		else if (pt.x > 567 && pt.x < 659
			&& pt.y > 303 && pt.y < 344
			&& pPlayer->GetMoney() >= 65)
		{
			pPlayer->SetMoney(pPlayer->GetMoney() - 65);
			pPlayer->SetAccel(pPlayer->GetAccel() + 0.002f);
		}
		else if (pt.x > 567 && pt.x < 659
			&& pt.y > 422 && pt.y < 462
			&& pPlayer->GetMoney() >= 80)
		{
			pPlayer->SetMoney(pPlayer->GetMoney() - 80);
			pPlayer->SetMaxSpeed(pPlayer->GetMaxSpeed() + 0.1f);
		}
		else if (pt.x > 574 && pt.x < 751
			&& pt.y > 526 && pt.y < 557)
		{
			InitStage2();
			SCENEMANAGER()->SceneChange();
			currentStage = StageState::STAGE2;
		}
	}
}


void Stage::Stage1Update()
{
	if (!SCENEMANAGER()->bSceneChange)
	{
		pCountDown->Process();
	}
	else
	{
		pCountDown->SetStartTime(GATIMER()->GetTimer());
	}

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pVecHorses[i]->SetTextureRect();
		pVecHorses[i]->Animation();

		if (!pCountDown->GetVisible() && !bStart)
		{
			pVecHorses[i]->SetState(Horse::State::RUN);
			if (i == pVecHorses.size() - 1)
			{
				bStart = true;
			}
		}
	}

	if (bStart)
	{
		for (int i = 0; i < pVecHorses.size(); i++)
		{
			pVecHorses[i]->Process();
		}
	}

	for (int i = 0; i < 4; i++)
	{
		pItem[i]->Process();
	}

	SetHorseDirection1();
	SetHorseDistance1();
	CollisionCheck1();
	SetItemIcon();
	SetRanking();
	
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pIcon[i]->SetPosition(450 + 221 + pVecHorses[i]->GetGamePos()->x / 33, 150 + pVecHorses[i]->GetGamePos()->y / 33, 0);
	}
	for (int i = 0; i < pVecRenderObject.size(); i++)
	{
		if (pPlayer->fDistance < 1800)
		{
			CAMERA()->SetCameraPos(*(pPlayer->GetGamePos()));
			pVecRenderObject[i]->SetTranslate(CAMERA()->GetCameraPos()->x, CAMERA()->GetCameraPos()->y);
		}
	}
	if (pPlayer->fDistance >= 1800)
	{
		pPlayer->SetPosition(pPlayer->GetGamePos()->x + 300, pPlayer->GetGamePos()->y + 200, 0);
		pPlayer->SetTranslate(CAMERA()->GetCameraPos()->x, CAMERA()->GetCameraPos()->y);
	}

	for (int i = 0; i < pVecHorseRank.size(); i++)
	{
		if (pVecHorses[i]->fDistance >= 1800 && pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pTrack->GetSection(0)->x))
		{
			pVecHorses[i]->SetVisible(false);
			pIcon[i]->SetVisible(false);
			if (i >= 3)
			{
				SCENEMANAGER()->SceneChange();
				currentStage = StageState::SHOP;
				if (pVecHorseRank[0] == pPlayer)
				{
					pPlayer->SetMoney(pPlayer->GetMoney() + 100);
				}
			}
		}
	}
}

void Stage::Stage2Update()
{
	if (!SCENEMANAGER()->bSceneChange)
	{
		pCountDown->Process();
	}
	else
	{
		pCountDown->SetStartTime(GATIMER()->GetTimer());
	}

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pVecHorses[i]->SetTextureRect();
		pVecHorses[i]->Animation();

		if (!pCountDown->GetVisible() && !bStart)
		{
			pVecHorses[i]->SetState(Horse::State::RUN);
			if (i == pVecHorses.size() - 1)
			{
				bStart = true;
			}
		}
	}

	if (bStart)
	{
		for (int i = 0; i < pVecHorses.size(); i++)
		{
			pVecHorses[i]->Process();
		}
	}

	for (int i = 0; i < 4; i++)
	{
		pItem[i]->Process();
	}

	SetHorseDirection2();
	SetHorseDistance2();
	CollisionCheck2();
	SetItemIcon();
	SetRanking();

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pIcon[i]->SetPosition(450 + 35 + pVecHorses[i]->GetGamePos()->x / 33, 25 + pVecHorses[i]->GetGamePos()->y / 33, 0);
	}
	for (int i = 0; i < pVecRenderObject.size(); i++)
	{
		if (pPlayer->fDistance < 1800)
		{
			CAMERA()->SetCameraPos(*(pPlayer->GetGamePos()));
			pVecRenderObject[i]->SetTranslate(CAMERA()->GetCameraPos()->x, CAMERA()->GetCameraPos()->y);
		}
	}
	if (pPlayer->fDistance >= 1800)
	{
		pPlayer->SetPosition(pPlayer->GetGamePos()->x + 300, pPlayer->GetGamePos()->y + 200, 0);
		pPlayer->SetTranslate(CAMERA()->GetCameraPos()->x, CAMERA()->GetCameraPos()->y);
	}

	for (int i = 0; i < pVecHorseRank.size(); i++)
	{
		if (pVecHorses[i]->fDistance >= 1800 && pVecHorses[i]->GetGamePos()->x + 200 >= -(fStartLineX - pBeach->GetSection(1)->x))
		{
			pVecHorses[i]->SetVisible(false);
			pIcon[i]->SetVisible(false);
			if (i >= 3)
			{
				SCENEMANAGER()->SceneChange();
				SCENEMANAGER()->SetCurrentScene(SceneManager::SceneState::ENDING);
				if (pVecHorseRank[0] == pPlayer)
				{
					pPlayer->SetMoney(pPlayer->GetMoney() + 100);
				}
			}
		}
	}
}

void Stage::Render()
{
	switch (currentStage)
	{
	case StageState::SELECT:
		pSelectHorse->Render();
		break;
	case StageState::STAGE1:
		Stage1Render();
		break;
	case StageState::SHOP:
		ShopRender();
		break;
	case StageState::STAGE2:
		Stage2Render();
		break;
	default:
		break;
	}
	
}

void Stage::Stage1Render()
{
	SetRenderSequence();

	pTrack->Render();

	for (int i = 0; i < 4; i++)
	{
		pItem[i]->Render();
	}

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pVecHorses[i]->Render();
		pVecHorses[i]->pSheild.Render();
		pVecHorses[i]->pFire.Render();
	}

	pStartPoint->Render();

	pLight->Render();

	pCountDown->Render();
	pUI->Render();
	pItemIcon->Render();
	pMinimap->Render();
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pIcon[i]->Render();
	}
	for (int i = 0; i < (200 / pPlayer->GetMaxStamina()) * pPlayer->GetStamina(); i++)
	{
		pStamina[i]->Render();
	}
	pHorseName->Render();


	CDXUTTextHelper txtStr(pFont, pFontSprite, 50);
	txtStr.Begin();
	txtStr.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	for (int i = 0; i < pVecHorseRank.size(); i++)
	{
		switch (pVecHorseRank[i]->GetHorseID())
		{
		case Horse::HorseID::JEJU:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 제주", i + 1);
			break;
		case Horse::HorseID::BUSAN:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 부산", i + 1);
			break;
		case Horse::HorseID::SEOUL:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 서울", i + 1);
			break;
		case Horse::HorseID::KWANGJU:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 광주", i + 1);
			break;
		default:
			break;
		}
	}
	txtStr.SetInsertionPos(180, 440);
	txtStr.DrawFormattedTextLine(L"%0.f Km/h", pPlayer->GetSpeed() * 10);
	txtStr.SetInsertionPos(550, 60);
	txtStr.DrawFormattedTextLine(L"%0.f m", pPlayer->fDistance);
	txtStr.SetInsertionPos(50, 0);
	txtStr.DrawFormattedTextLine(L"%0.f 만원", pPlayer->GetMoney());
	txtStr.End();
}

void Stage::ShopRender()
{
	pShop->Render();

	CDXUTTextHelper txtStr(pFont, pFontSprite, 50);
	txtStr.Begin();
	txtStr.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	txtStr.SetInsertionPos(183, 500);
	txtStr.DrawFormattedTextLine(L"%0.f 만원", pPlayer->GetMoney());
	txtStr.End();
}

void Stage::Stage2Render()
{
	SetRenderSequence();

	pBeach->Render();

	for (int i = 0; i < 4; i++)
	{
		pItem[i]->Render();
	}

	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pVecHorses[i]->Render();
		pVecHorses[i]->pSheild.Render();
		pVecHorses[i]->pFire.Render();
	}

	pStartPoint->Render();

	pLight->Render();

	pCountDown->Render();
	pUI->Render();
	pItemIcon->Render();
	pMinimap->Render();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		pIcon[i]->Render();
	}
	for (int i = 0; i < (200 / pPlayer->GetMaxStamina()) * pPlayer->GetStamina(); i++)
	{
		pStamina[i]->Render();
	}
	pHorseName->Render();


	CDXUTTextHelper txtStr(pFont, pFontSprite, 50);
	txtStr.Begin();
	txtStr.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	for (int i = 0; i < pVecHorseRank.size(); i++)
	{
		switch (pVecHorseRank[i]->GetHorseID())
		{
		case Horse::HorseID::JEJU:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 제주", i + 1);
			break;
		case Horse::HorseID::BUSAN:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 부산", i + 1);
			break;
		case Horse::HorseID::SEOUL:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 서울", i + 1);
			break;
		case Horse::HorseID::KWANGJU:
			txtStr.SetInsertionPos(200, 100 + 70 * i);
			txtStr.DrawFormattedTextLine(L"%d위 - 광주", i + 1);
			break;
		default:
			break;
		}
	}
	txtStr.SetInsertionPos(180, 440);
	txtStr.DrawFormattedTextLine(L"%0.f Km/h", pPlayer->GetSpeed() * 10);
	txtStr.SetInsertionPos(550, 60);
	txtStr.DrawFormattedTextLine(L"%0.f m", pPlayer->fDistance);
	txtStr.SetInsertionPos(50, 0);
	txtStr.DrawFormattedTextLine(L"%0.f 만원", pPlayer->GetMoney());
	txtStr.End();
}

void Stage::SetHorseDirection1()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		if (pVecHorses[i]->GetGamePos()->x > -(fStartLineX - pTrack->GetSection(0)->x)
			&& pVecHorses[i]->GetGamePos()->x <= 0)
		{
			pVecHorses[i]->SetDirection(Horse::Direction::LEFT);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(7)->x), -(fStartLineY - pTrack->GetSection(7)->y),
				-(fStartLineX - pTrack->GetSection(0)->x), -(fStartLineY - pTrack->GetSection(0)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pTrack->GetSection(0)->x))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::LUP);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(0)->x), -(fStartLineY - pTrack->GetSection(0)->y),
				-(fStartLineX - pTrack->GetSection(1)->x), -(fStartLineY - pTrack->GetSection(1)->y));
			pStartPoint->SetVisible(false);
		}

		if (pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pTrack->GetSection(1)->y))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::UP);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(1)->x), -(fStartLineY - pTrack->GetSection(1)->y),
				-(fStartLineX - pTrack->GetSection(2)->x), -(fStartLineY - pTrack->GetSection(2)->y));
		}

		if (pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pTrack->GetSection(2)->y))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::RUP);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(2)->x), -(fStartLineY - pTrack->GetSection(2)->y),
				-(fStartLineX - pTrack->GetSection(3)->x), -(fStartLineY - pTrack->GetSection(3)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pTrack->GetSection(3)->x)
			&& pVecHorses[i]->GetGamePos()->y <= -1295)
		{
			pVecHorses[i]->SetDirection(Horse::Direction::RIGHT);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(3)->x), -(fStartLineY - pTrack->GetSection(3)->y),
				-(fStartLineX - pTrack->GetSection(4)->x), -(fStartLineY - pTrack->GetSection(4)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pTrack->GetSection(4)->x)
			&& pVecHorses[i]->GetGamePos()->y <= -1295)
		{
			pVecHorses[i]->SetDirection(Horse::Direction::RDOWN);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(4)->x), -(fStartLineY - pTrack->GetSection(4)->y),
				-(fStartLineX - pTrack->GetSection(5)->x), -(fStartLineY - pTrack->GetSection(5)->y));
		}

		if (pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pTrack->GetSection(5)->y)
			&& pVecHorses[i]->GetGamePos()->x >= 1555)
		{
			pVecHorses[i]->SetDirection(Horse::Direction::DOWN);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(5)->x), -(fStartLineY - pTrack->GetSection(5)->y),
				-(fStartLineX - pTrack->GetSection(6)->x), -(fStartLineY - pTrack->GetSection(6)->y));
		}

		if (pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pTrack->GetSection(6)->y)
			&& pVecHorses[i]->GetGamePos()->x >= 1555)
		{
			pVecHorses[i]->SetDirection(Horse::Direction::LDOWN);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(6)->x), -(fStartLineY - pTrack->GetSection(6)->y),
				-(fStartLineX - pTrack->GetSection(7)->x), -(fStartLineY - pTrack->GetSection(7)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pTrack->GetSection(7)->x)
			&& pVecHorses[i]->GetGamePos()->y >= -1295
			&& pVecHorses[i]->GetGamePos()->x >= 0)
		{
			pVecHorses[i]->SetDirection(Horse::Direction::LEFT);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pTrack->GetSection(7)->x), -(fStartLineY - pTrack->GetSection(7)->y),
				-(fStartLineX - pTrack->GetSection(0)->x), -(fStartLineY - pTrack->GetSection(0)->y));
		}
	}
}

void Stage::SetHorseDistance1()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - - 2664)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - 6198)
			&& pVecHorses[i]->fDistance == 0)
		{
			pVecHorses[i]->fDistance = 100.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - 4618)
			&& pVecHorses[i]->fDistance == 100)
		{
			pVecHorses[i]->fDistance = 190.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - 2058)
			&& pVecHorses[i]->fDistance == 190)
		{
			pVecHorses[i]->fDistance = 400.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 2653)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - 2058)
			&& pVecHorses[i]->fDistance == 400)
		{
			pVecHorses[i]->fDistance = 500;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x > -(fStartLineX - 2058)
			&& pVecHorses[i]->fDistance == 500)
		{
			pVecHorses[i]->fDistance = 600.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x + 200 > -(fStartLineX - 4548)
			&& pVecHorses[i]->fDistance == 600)
		{
			pVecHorses[i]->fDistance = 800.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x + 200 > -(fStartLineX - 6198)
			&& pVecHorses[i]->fDistance == 800)
		{
			pVecHorses[i]->fDistance = 900.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x + 200 > -(fStartLineX - 7890)
			&& pVecHorses[i]->fDistance == 900)
		{
			pVecHorses[i]->fDistance = 1000.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x + 200 > -(fStartLineX - 10139)
			&& pVecHorses[i]->fDistance == 1000)
		{
			pVecHorses[i]->fDistance = 1200.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y + 200 > -(fStartLineY - 2653)
			&& pVecHorses[i]->GetGamePos()->x + 200 > -(fStartLineX - 10139)
			&& pVecHorses[i]->fDistance == 1200)
		{
			pVecHorses[i]->fDistance = 1300.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 2653)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - 10139)
			&& pVecHorses[i]->fDistance == 1300)
		{
			pVecHorses[i]->fDistance = 1400.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - 7891)
			&& pVecHorses[i]->fDistance == 1400)
		{
			pVecHorses[i]->fDistance = 1600.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - 6198)
			&& pVecHorses[i]->fDistance == 1600)
		{
			pVecHorses[i]->fDistance = 1700.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 2664)
			&& pVecHorses[i]->GetGamePos()->x  < -(fStartLineX - 4560)
			&& pVecHorses[i]->fDistance == 1700)
		{
			pVecHorses[i]->fDistance = 1800.0f;
			pVecHorses[i]->bGoal = true;
		}
	}
}

void Stage::CollisionCheck1()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		// Horse Collision
		for (int j = 0; j < pVecHorses.size(); j++)
		{
			if (i != j)
			{
				if (IsRectCollision(pVecHorses[i]->GetCollisionRect(), pVecHorses[j]->GetCollisionRect()))
				{
					D3DXVECTOR2 vec;
					vec.x = pVecHorses[j]->GetGamePos()->x - pVecHorses[i]->GetGamePos()->x;
					vec.y = pVecHorses[j]->GetGamePos()->y - pVecHorses[i]->GetGamePos()->y;

					D3DXVec2Normalize(&vec, &vec);

					pVecHorses[i]->GetGamePos()->x -= vec.x * pVecHorses[i]->GetSpeed() / 1.5;
					pVecHorses[i]->GetGamePos()->y -= vec.y * pVecHorses[i]->GetSpeed() / 1.5;
				}
			}
		}
		for (int j = 0; j < 4; j++)
		{
			if (pItem[j]->GetVisible() && IsRectCollision(pVecHorses[i]->GetCollisionRect(), pItem[j]->GetCollisionRect()))
			{
				pItem[j]->SetHit(true);
				pVecHorses[i]->SetItem(pItem[j]);
			}
		}
		for (int j = 0; j < pVecHorses.size(); j++)
		{
			if (IsRectCollision(pVecHorses[i]->pFire.GetCollisionRect()->left, pVecHorses[i]->pFire.GetCollisionRect()->right, pVecHorses[i]->pFire.GetCollisionRect()->top, pVecHorses[i]->pFire.GetCollisionRect()->bottom,
				pVecHorses[j]->GetGamePos()->x, pVecHorses[j]->GetGamePos()->x + 200, pVecHorses[j]->GetGamePos()->y, pVecHorses[j]->GetGamePos()->y + 200)
				&& pVecHorses[i]->pFire.GetVisible() && i != j)
			{
				pVecHorses[j]->SetHit(true);
				pVecHorses[j]->fHitTime = GATIMER()->GetTimer();
			}
		}
		// straight line
		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pTrack->GetSection(0)->x) && pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pTrack->GetSection(7)->x))
		{
			if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 2664))
			{
				// line - 100
				if (pVecHorses[i]->GetCollisionCircleCenterY() <= -(fStartLineY - 4564))
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 4564) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR();
				}
				if (pVecHorses[i]->GetCollisionCircleCenterY() >= -(fStartLineY - 5006) - pVecHorses[i]->GetCollisionCircleR())
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 5006) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR() * 2;
				}
			}
			if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 2664))
			{
				// line - 100
				if (pVecHorses[i]->GetCollisionCircleCenterY() <= -(fStartLineY - 487))
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 487) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR();
				}
				if (pVecHorses[i]->GetCollisionCircleCenterY() >= -(fStartLineY - 926) - pVecHorses[i]->GetCollisionCircleR())
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 926) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR() * 2;
				}
			}
		}

		// left circle
		if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pTrack->GetSection(0)->x))
		{
			if (IsCircleCollision(-(fStartLineX - 2899), -(fStartLineY - 2757), 1810,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 2899), -(fStartLineY - 2757), 1810, pVecHorses[i], CircleID::INSIDE);
			}

			if (!IsCircleCollision(-(fStartLineX - 2899), -(fStartLineY - 2757), 2269 - pVecHorses[i]->GetCollisionCircleR() * 2,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 2899), -(fStartLineY - 2757), 2269, pVecHorses[i], CircleID::OUTSIDE);
			}
		}

		// right circle
		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pTrack->GetSection(7)->x))
		{
			if (IsCircleCollision(-(fStartLineX - 9300), -(fStartLineY - 2757), 1810,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 9300), -(fStartLineY - 2757), 1810, pVecHorses[i], CircleID::INSIDE);
			}

			if (!IsCircleCollision(-(fStartLineX - 9300), -(fStartLineY - 2757), 2269 - pVecHorses[i]->GetCollisionCircleR() * 2,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 9300), -(fStartLineY - 2757), 2269, pVecHorses[i], CircleID::OUTSIDE);
			}
		}
	}
}

void Stage::SetHorseDirection2()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		if (pVecHorses[i]->GetGamePos()->x > -(fStartLineX - pBeach->GetSection(0)->x)
			&& pVecHorses[i]->GetGamePos()->x >= 0
			&& pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pBeach->GetSection(6)->y))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::RIGHT);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(0)->x), -(fStartLineY - pBeach->GetSection(0)->y),
				-(fStartLineX - pBeach->GetSection(1)->x), -(fStartLineY - pBeach->GetSection(1)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x > -(fStartLineX - pBeach->GetSection(1)->x)
			&& pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pBeach->GetSection(2)->y))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::RDOWN);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(1)->x), -(fStartLineY - pBeach->GetSection(1)->y),
				-(fStartLineX - pBeach->GetSection(2)->x), -(fStartLineY - pBeach->GetSection(2)->y));
			pStartPoint->SetVisible(false);
		}

		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - pBeach->GetSection(2)->y)
			&& pVecHorses[i]->GetGamePos()->x + 200 > -(fStartLineX - pBeach->GetSection(1)->x))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::DOWN);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(2)->x), -(fStartLineY - pBeach->GetSection(2)->y),
				-(fStartLineX - pBeach->GetSection(3)->x), -(fStartLineY - pBeach->GetSection(3)->y));
		}

		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - pBeach->GetSection(3)->y)
			&& pVecHorses[i]->GetGamePos()->x + 200 > -(fStartLineX - pBeach->GetSection(1)->x))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::LDOWN);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(3)->x), -(fStartLineY - pBeach->GetSection(3)->y),
				-(fStartLineX - pBeach->GetSection(4)->x), -(fStartLineY - pBeach->GetSection(4)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x < -(fStartLineX - pBeach->GetSection(4)->x)
			&& pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pBeach->GetSection(3)->y))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::LEFT);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(4)->x), -(fStartLineY - pBeach->GetSection(4)->y),
				-(fStartLineX - pBeach->GetSection(5)->x), -(fStartLineY - pBeach->GetSection(5)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x < -(fStartLineX - pBeach->GetSection(5)->x)
			&& pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pBeach->GetSection(3)->y))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::LUP);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(5)->x), -(fStartLineY - pBeach->GetSection(5)->y),
				-(fStartLineX - pBeach->GetSection(6)->x), -(fStartLineY - pBeach->GetSection(6)->y));
		}

		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - pBeach->GetSection(6)->y)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - pBeach->GetSection(0)->x))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::UP);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(6)->x), -(fStartLineY - pBeach->GetSection(6)->y),
				-(fStartLineX - pBeach->GetSection(7)->x), -(fStartLineY - pBeach->GetSection(7)->y));
		}

		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - pBeach->GetSection(7)->y)
			&& pVecHorses[i]->GetGamePos()->x < -(fStartLineX - pBeach->GetSection(0)->x))
		{
			pVecHorses[i]->SetDirection(Horse::Direction::RUP);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(7)->x), -(fStartLineY - pBeach->GetSection(7)->y),
				-(fStartLineX - pBeach->GetSection(0)->x), -(fStartLineY - pBeach->GetSection(0)->y));
		}

		if (pVecHorses[i]->GetGamePos()->x > -(fStartLineX - pBeach->GetSection(0)->x)
			&& pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pBeach->GetSection(6)->y)
			&& pVecHorses[i]->GetGamePos()->x <= 0)
		{
			pVecHorses[i]->SetDirection(Horse::Direction::RIGHT);
			pVecHorses[i]->SetDirectVec(-(fStartLineX - pBeach->GetSection(0)->x), -(fStartLineY - pBeach->GetSection(0)->y),
				-(fStartLineX - pBeach->GetSection(1)->x), -(fStartLineY - pBeach->GetSection(1)->y));
		}
	}
}

void Stage::SetHorseDistance2()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x + 100 >= -(fStartLineX - 3616)
			&& pVecHorses[i]->fDistance == 0)
		{
			pVecHorses[i]->fDistance = 100.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x + 100 >= -(fStartLineX - 5375)
			&& pVecHorses[i]->fDistance == 100)
		{
			pVecHorses[i]->fDistance = 200.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - 7052)
			&& pVecHorses[i]->fDistance == 200)
		{
			pVecHorses[i]->fDistance = 300.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - 3030)
			&& pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - 7052)
			&& pVecHorses[i]->fDistance == 300)
		{
			pVecHorses[i]->fDistance = 500;
		}
		if (pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - 3030)
			&& pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - 8674)
			&& pVecHorses[i]->fDistance == 500)
		{
			pVecHorses[i]->fDistance = 700.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - 6290)
			&& pVecHorses[i]->fDistance == 700)
		{
			pVecHorses[i]->fDistance = 900.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - 3938)
			&& pVecHorses[i]->fDistance == 900)
		{
			pVecHorses[i]->fDistance = 1100.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y > -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x > -(fStartLineX - 1976)
			&& pVecHorses[i]->fDistance == 1100)
		{
			pVecHorses[i]->fDistance = 1300.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x + 100 >= -(fStartLineX - 3616)
			&& pVecHorses[i]->fDistance == 1300)
		{
			pVecHorses[i]->fDistance = 1600.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x + 100 >= -(fStartLineX - 5375)
			&& pVecHorses[i]->fDistance == 1600)
		{
			pVecHorses[i]->fDistance = 1700.0f;
		}
		if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 3500)
			&& pVecHorses[i]->GetGamePos()->x + 100 >= -(fStartLineX - 7052)
			&& pVecHorses[i]->fDistance == 1700)
		{
			pVecHorses[i]->fDistance = 1800.0f;
			pVecHorses[i]->bGoal = true;
		}
	}
}

void Stage::CollisionCheck2()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		// Horse Collision
		for (int j = 0; j < pVecHorses.size(); j++)
		{
			if (i != j)
			{
				if (IsRectCollision(pVecHorses[i]->GetCollisionRect(), pVecHorses[j]->GetCollisionRect()))
				{
					D3DXVECTOR2 vec;
					vec.x = pVecHorses[j]->GetGamePos()->x - pVecHorses[i]->GetGamePos()->x;
					vec.y = pVecHorses[j]->GetGamePos()->y - pVecHorses[i]->GetGamePos()->y;

					D3DXVec2Normalize(&vec, &vec);

					pVecHorses[i]->GetGamePos()->x -= vec.x * pVecHorses[i]->GetSpeed() / 1.5;
					pVecHorses[i]->GetGamePos()->y -= vec.y * pVecHorses[i]->GetSpeed() / 1.5;
				}
			}
		}
		for (int j = 0; j < 4; j++)
		{
			if (pItem[j]->GetVisible() && IsRectCollision(pVecHorses[i]->GetCollisionRect(), pItem[j]->GetCollisionRect()))
			{
				pItem[j]->SetHit(true);
				pVecHorses[i]->SetItem(pItem[j]);
			}
		}
		for (int j = 0; j < pVecHorses.size(); j++)
		{
			if (IsRectCollision(pVecHorses[i]->pFire.GetCollisionRect()->left, pVecHorses[i]->pFire.GetCollisionRect()->right, pVecHorses[i]->pFire.GetCollisionRect()->top, pVecHorses[i]->pFire.GetCollisionRect()->bottom,
				pVecHorses[j]->GetGamePos()->x, pVecHorses[j]->GetGamePos()->x + 200, pVecHorses[j]->GetGamePos()->y, pVecHorses[j]->GetGamePos()->y + 200)
				&& pVecHorses[i]->pFire.GetVisible() && i != j)
			{
				pVecHorses[j]->SetHit(true);
				pVecHorses[j]->fHitTime = GATIMER()->GetTimer();
			}
		}
		// straight line top
		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pBeach->GetSection(0)->x)
			&& pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pBeach->GetSection(1)->x))
		{
			if (pVecHorses[i]->GetGamePos()->y < -(fStartLineY - 1243))
			{
				// line - 100
				if (pVecHorses[i]->GetCollisionCircleCenterY() >= -(fStartLineY - 1243))
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 1243) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR();
				}
				if (pVecHorses[i]->GetCollisionCircleCenterY() <= -(fStartLineY - 816) - pVecHorses[i]->GetCollisionCircleR())
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 816) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR() * 2;
				}
			}
		}
		// straight line bottom
		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pBeach->GetSection(5)->x) 
			&& pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pBeach->GetSection(4)->x))
		{
			if (pVecHorses[i]->GetGamePos()->y >= 3500)
			{
				// line - 100
				if (pVecHorses[i]->GetCollisionCircleCenterY() <= -(fStartLineY - 6002))
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 6002) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR();
				}
				if (pVecHorses[i]->GetCollisionCircleCenterY() >= -(fStartLineY - 6428) - pVecHorses[i]->GetCollisionCircleR())
				{
					pVecHorses[i]->GetGamePos()->y = -(fStartLineY - 6428) - pVecHorses[i]->GetCollisionCircleY() - pVecHorses[i]->GetCollisionCircleR() * 2;
				}
			}
		}
		// straight line right
		if (pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pBeach->GetSection(2)->y)
			&& pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pBeach->GetSection(3)->y))
		{
			if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pBeach->GetSection(1)->x))
			{
				// line - 100
				if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - 8845) - 100)
				{
					pVecHorses[i]->GetGamePos()->x = -(fStartLineX - 8845) - 100;
				}
				if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - 9272) - 100)
				{
					pVecHorses[i]->GetGamePos()->x = -(fStartLineX - 9272) - 100;
				}
			}
		}
		// straight line left
		if (pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pBeach->GetSection(7)->y + 100)
			&& pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pBeach->GetSection(6)->y) + 100)
		{
			if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pBeach->GetSection(0)->x))
			{
				if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - 676) - 100)
				{
					pVecHorses[i]->GetGamePos()->x = -(fStartLineX - 676) - 100;
				}
				if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - 1103) - 100)
				{
					pVecHorses[i]->GetGamePos()->x = -(fStartLineX - 1103) - 100;
				}
			}
		}
		
		// rightup circle
		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pBeach->GetSection(1)->x) &&
			pVecHorses[i]->GetGamePos()->y <= -(fStartLineY - pBeach->GetSection(2)->y))
		{
			if (IsCircleCollision(-(fStartLineX - 8027), -(fStartLineY - 2062), 818,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 8027), -(fStartLineY - 2062), 818, pVecHorses[i], CircleID::INSIDE);
			}

			if (!IsCircleCollision(-(fStartLineX - 8027), -(fStartLineY - 2062), 1246 - pVecHorses[i]->GetCollisionCircleR() * 2,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 8027), -(fStartLineY - 2062), 1246, pVecHorses[i], CircleID::OUTSIDE);
			}
		}

		// rightDown circle
		if (pVecHorses[i]->GetGamePos()->x >= -(fStartLineX - pBeach->GetSection(4)->x) &&
			pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pBeach->GetSection(3)->y))
		{
			if (IsCircleCollision(-(fStartLineX - 8027), -(fStartLineY - 5183), 818,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 8027), -(fStartLineY - 5183), 818, pVecHorses[i], CircleID::INSIDE);
			}

			if (!IsCircleCollision(-(fStartLineX - 8027), -(fStartLineY - 5183), 1246 - pVecHorses[i]->GetCollisionCircleR() * 2,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 8027), -(fStartLineY - 5183), 1246, pVecHorses[i], CircleID::OUTSIDE);
			}
		}

		// leftUp circle
		if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pBeach->GetSection(0)->x) &&
			pVecHorses[i]->GetGamePos()->y + 100 <= -(fStartLineY - pBeach->GetSection(7)->y))
		{
			if (IsCircleCollision(-(fStartLineX - 1922), -(fStartLineY - 2062), 818,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 1922), -(fStartLineY - 2062), 818, pVecHorses[i], CircleID::INSIDE);
			}

			if (!IsCircleCollision(-(fStartLineX - 1922), -(fStartLineY - 2062), 1246 - pVecHorses[i]->GetCollisionCircleR() * 2,
				pVecHorses[i]->GetCollisionCircleCenterX(), pVecHorses[i]->GetCollisionCircleCenterY(), pVecHorses[i]->GetCollisionCircleR()))
			{
				SetLimitPos(-(fStartLineX - 1922), -(fStartLineY - 2062), 1246, pVecHorses[i], CircleID::OUTSIDE);
			}
		}

		// leftUp circle
		if (pVecHorses[i]->GetGamePos()->x <= -(fStartLineX - pBeach->GetSection(5)->x) &&
			pVecHorses[i]->GetGamePos()->y >= -(fStartLineY - pBeach->GetSection(6)->y))
		{
			D3DXVECTOR2 vec1_1;
			D3DXVECTOR2 vec1_2;
			D3DXVECTOR2 vec2_1;
			D3DXVECTOR2 vec2_2;
			D3DXVECTOR2 vPlayer_1;
			D3DXVECTOR2 vPlayer_2;
			D3DXVECTOR2 pOut;

			vec1_1.x = -(fStartLineX - 776);
			vec1_1.y = -(fStartLineY - 3401);
			vec1_2.x = -(fStartLineX - 4681);
			vec1_2.y = -(fStartLineY - 6228);

			vec2_1.x = -(fStartLineX - 1203);
			vec2_1.y = -(fStartLineY - 3187);
			vec2_2.x = -(fStartLineX - 4820);
			vec2_2.y = -(fStartLineY - 5802);

			vPlayer_1.x = pVecHorses[i]->GetGamePos()->x;
			vPlayer_1.y = pVecHorses[i]->GetGamePos()->y;
			vPlayer_2.x = pVecHorses[i]->GetGamePos()->x + 200.0f;
			vPlayer_2.y = pVecHorses[i]->GetGamePos()->y;

			pOut.x = 0;
			pOut.y = 0;

			if (IsTriangleCollision(vec1_1, vec1_2, vPlayer_1, vPlayer_2, &pOut))
			{
				if (pVecHorses[i]->GetGamePos()->x < pOut.x)
				{
					pVecHorses[i]->GetGamePos()->x = pOut.x;
				}
			}
			if (IsTriangleCollision(vPlayer_2, vPlayer_1, vec2_1, vec2_2, &pOut))
			{
				if (pVecHorses[i]->GetGamePos()->x > pOut.x - 200)
				{
					pVecHorses[i]->GetGamePos()->x = pOut.x - 200;
				}
			}
		}

	}
}

void Stage::SetRenderSequence()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		for (int j = 1; j < pVecHorses.size() - i; j++)
		{
			if (pVecHorses[j - 1]->GetGamePos()->y > pVecHorses[j]->GetGamePos()->y)
			{
				Horse* pTemp = pVecHorses[j - 1];
				RenderObject* pTempIcon = pIcon[j - 1];

				pVecHorses[j - 1] = pVecHorses[j];
				pVecHorses[j] = pTemp;

				pIcon[j - 1] = pIcon[j];
				pIcon[j] = pTempIcon;

			}
		}
	}
}

bool Stage::IsCircleCollision(float fCircle1X, float fCircle1Y, float fCircle1Radius, float fCircle2X, float fCircle2Y, float fCircle2Radius)
{
	float fDeltaX = fCircle1X - fCircle2X;
	float fDeltaY = fCircle1Y - fCircle2Y;

	float fLength = sqrt(fDeltaX * fDeltaX + fDeltaY * fDeltaY);

	if (fLength >= (fCircle1Radius + fCircle2Radius))
	{
		return false;
	}

	return true;
}

void Stage::SetLimitPos(float fCircleX, float fCircleY, float fCircleRadius, Horse* pPlayer, CircleID id)
{
	D3DXVECTOR2 vDirect;

	vDirect.x = pPlayer->GetCollisionCircleCenterX() - fCircleX;
	vDirect.y = pPlayer->GetCollisionCircleCenterY() - fCircleY;

	D3DXVec2Normalize(&vDirect, &vDirect);

	switch (id)
	{
	case CircleID::INSIDE:
		pPlayer->GetGamePos()->x = fCircleX + (vDirect.x * (fCircleRadius + pPlayer->GetCollisionCircleR())) - pPlayer->GetCollisionCircleX();
		pPlayer->GetGamePos()->y = fCircleY + (vDirect.y * (fCircleRadius + pPlayer->GetCollisionCircleR())) - pPlayer->GetCollisionCircleY() - pPlayer->GetCollisionCircleR();
		break;
	case CircleID::OUTSIDE:
		pPlayer->GetGamePos()->x = fCircleX + (vDirect.x * (fCircleRadius - pPlayer->GetCollisionCircleR())) - pPlayer->GetCollisionCircleX();
		pPlayer->GetGamePos()->y = fCircleY + (vDirect.y * (fCircleRadius - pPlayer->GetCollisionCircleR())) - pPlayer->GetCollisionCircleY() - pPlayer->GetCollisionCircleR();
		break;
	default:
		break;
	}
}

bool Stage::IsRectCollision(RECT* rtCollision1, RECT* rtCollision2)
{
	if (rtCollision1->left < rtCollision2->right && rtCollision1->right > rtCollision2->left &&
		rtCollision1->top < rtCollision2->bottom && rtCollision1->bottom > rtCollision2->top)
	{
		return true;
	}

	return false;
}

bool Stage::IsRectCollision(float left1, float right1, float top1, float bottom1, float left2, float right2, float top2, float bottom2)
{
	if (left1 < right2 && right1 > left2 &&
		top1 < bottom2 && bottom1 > top2)
	{
		return true;
	}

	return false;
}

bool Stage::IsTriangleCollision(D3DXVECTOR2 vec1_1, D3DXVECTOR2 vec1_2, D3DXVECTOR2 vec2_1, D3DXVECTOR2 vec2_2, D3DXVECTOR2* pOut)
{
	float t;
	float s;

	float under = (vec2_2.y - vec2_1.y) * (vec1_2.x - vec1_1.x) - (vec2_2.x - vec2_1.x) * (vec1_2.y - vec1_1.y);
	if (under == 0) return false;

	float t_ = (vec2_2.x - vec2_1.x) * (vec1_1.y - vec2_1.y) - (vec2_2.y - vec2_1.y) * (vec1_1.x - vec2_1.x);
	float s_ = (vec1_2.x - vec1_1.x) * (vec1_1.y - vec2_1.y) - (vec1_2.y - vec1_1.y) * (vec1_1.x - vec2_1.x);

	t = t_ / under;
	s = s_ / under;

	if (t < 0 || t > 1 || s < 0 || s > 1)
	{
		return false;
	}
	if (t_ == 0 && s_ == 0)
	{
		return false;
	}

	pOut->x = vec1_1.x + t * (vec1_2.x - vec1_1.x);
	pOut->y = vec1_1.y + t * (vec1_2.y - vec1_1.y);

	return true;
}

void Stage::SetItemIcon()
{
	if (pPlayer->bShelidItem)
	{
		pItemIcon->SetRect(160, 240, 0, 80);
	}
	else if (pPlayer->bBoostItem)
	{
		pItemIcon->SetRect(80, 160, 0, 80);
	}
	else if (pPlayer->bFireItem)
	{
		pItemIcon->SetRect(240, 320, 0, 80);
	}
	else
	{
		pItemIcon->SetRect(0, 80, 0, 80);
	}
}

void Stage::SetRanking()
{
	for (int i = 0; i < pVecHorses.size(); i++)
	{
		if (pVecHorses[i]->fDistance == 1800
			&& pVecHorses[i]->bGoal)
		{
			if (pVecHorseRank.size() < 4)
			{
				pVecHorseRank.push_back(pVecHorses[i]);
				pVecHorses[i]->bGoal = false;
			}
		}
	}
}