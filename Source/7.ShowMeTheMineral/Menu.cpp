#include "DXUT.h"
#include "SDKmisc.h"
#include "Menu.h"
#include "ObjectManager.h"

Menu::Menu()
{
	Create();
}


Menu::~Menu()
{
}

void Menu::Create()
{
	pMenu = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::MENU), 1024, 768, 0, 0);
	bClick = false;
	ShowCursor(true);
}

void Menu::Update()
{
	POINT pos;
	GetCursorPos(&pos);

	if (bClick)
	{
		if (pos.x >= 385 && pos.y >= 311 &&
			pos.x <= 644 && pos.y <= 368)
		{
			OBJMANAGER()->SetScore(0);
			OBJMANAGER()->SetScene(ObjectManager::SceneState::STAGE1);
			bClick = false;
		}
		if (pos.x >= 373 && pos.y >= 395 &&
			pos.x <= 651 && pos.y <= 451)
		{
			pMenu->SetRect(1024, 1024 * 2, 0, 768);
		}
		if (pos.x >= 373 && pos.y >= 475 &&
			pos.x <= 651 && pos.y <= 534)
		{
			pMenu->SetRect(1024 * 2, 1024 * 3, 0, 768);
		}
		if (pos.x >= 425 && pos.y >= 556 &&
			pos.x <= 605 && pos.y <= 601)
		{
			pMenu->SetRect(1024 * 3, 1024 * 4, 0, 768);
		}
		if (pos.x >= 445 && pos.y >= 628 &&
			pos.x <= 587 && pos.y <= 679)
		{
			pMenu->SetRect(1024 * 4, 1024 * 5, 0, 768);
		}
		if (pos.x >= 471 && pos.y >= 706 &&
			pos.x <= 564 && pos.y <= 762)
		{
			exit(0);
		}
	}
}

void Menu::Render()
{
	pMenu->Render(OBJMANAGER()->GetSprite());

	if (pMenu->GetRect()->left == 1024 * 3)
	{
		CDXUTTextHelper txtTimer(OBJMANAGER()->GetFontTime(), OBJMANAGER()->GetSprite(), 75);
		txtTimer.Begin();
		txtTimer.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		for (int i = 0; i < 3; i++)
		{
			txtTimer.SetInsertionPos(386 +i*50, 247);
			txtTimer.DrawFormattedTextLine(L"%c", OBJMANAGER()->FirstPlayer[i]);
			txtTimer.SetInsertionPos(386 +i*50, 395);
			txtTimer.DrawFormattedTextLine(L"%c", OBJMANAGER()->SecondPlayer[i]);
			txtTimer.SetInsertionPos(386 +i*50, 545);
			txtTimer.DrawFormattedTextLine(L"%c", OBJMANAGER()->ThirdPlayer[i]);
		}
		txtTimer.SetInsertionPos(550, 247);
		txtTimer.DrawFormattedTextLine(L"%d", OBJMANAGER()->FirstScore);
		txtTimer.SetInsertionPos(550, 395);
		txtTimer.DrawFormattedTextLine(L"%d", OBJMANAGER()->SecondScore);
		txtTimer.SetInsertionPos(550, 545);
		txtTimer.DrawFormattedTextLine(L"%d", OBJMANAGER()->ThirdScore);
		txtTimer.End();
	}
}

void Menu::MouseProc(UINT uMsg)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		bClick = true;
		break;
	case WM_LBUTTONUP:
		bClick = false;
		break;
	default:
		break;
	}
}