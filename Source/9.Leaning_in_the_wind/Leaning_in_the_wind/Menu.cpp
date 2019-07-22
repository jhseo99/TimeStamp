#include "DXUT.h"
#include "GaBase.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}



void Menu::Create(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pMenu = new RenderObject;
	pMenu->CreateTexture(pd3dDevice, L"texture\\menu.png");
	pMenu->SetRect(0, 800, 0, 600);
	pMenu->SetTranslate(0, 0);
	pMenu->SetPosition(0, 0, 0);
	pMenu->SetVisible(true);
}

void Menu::Update()
{
	POINT pt;
	GetCursorPos(&pt);

	if (SCENEMANAGER()->bCurrentClick)
	{
		if (pt.x > 526 && pt.x < 769
			&& pt.y > 210 && pt.y < 271)
		{
			SCENEMANAGER()->SetCurrentScene(SceneManager::SceneState::STAGE);
			GATIMER()->InitTimer();
		}
		if (pt.x > 526 && pt.x < 769
			&& pt.y > 476 && pt.y < 537)
		{
			exit(0);
		}
	}
}

void Menu::Render()
{
	pMenu->Render();
}