#include "DXUT.h"
#include "GaBase.h"


Intro::Intro()
{
}


Intro::~Intro()
{
}

void Intro::Create(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pBeach = new RenderObject;
	pBeach->CreateTexture(pd3dDevice, L"texture\\intro.png");
	pBeach->SetRect(0, 800, 0, 600);
	pBeach->SetTranslate(0, 0);
	pBeach->SetPosition(0, 0, 0);
	pBeach->SetVisible(true);

	pCloud1 = new RenderObject;
	pCloud1->CreateTexture(pd3dDevice, L"texture\\cloud.png");
	pCloud1->SetRect(0, 800, 0, 600);
	pCloud1->SetTranslate(0, 0);
	pCloud1->SetPosition(0, 0, 0);
	pCloud1->SetVisible(true);

	pCloud2 = new RenderObject;
	pCloud2->CreateTexture(pd3dDevice, L"texture\\cloud.png");
	pCloud2->SetRect(800, 1600, 0, 600);
	pCloud2->SetTranslate(0, 0);
	pCloud2->SetPosition(800, 0, 0);
	pCloud2->SetVisible(true);

	pTitle = new RenderObject;
	pTitle->CreateTexture(pd3dDevice, L"texture\\title.png");
	pTitle->SetRect(0, 800, 0, 600);
	pTitle->SetTranslate(0, 0);
	pTitle->SetPosition(0, 0, 0);
	pTitle->SetVisible(false);
}

void Intro::Update()
{
	pCloud1->GetPosition()->x -= 1.0f;
	pCloud2->GetPosition()->x -= 1.0f;

	if (pCloud1->GetPosition()->x <= -800)
	{
		pCloud1->SetPosition(800, 0, 0);
	}
	if (pCloud2->GetPosition()->x <= -800)
	{
		pCloud2->SetPosition(800, 0, 0);
	}

	if (GetAsyncKeyState(VK_RETURN) && pTitle->GetVisible())
	{
		SCENEMANAGER()->SetCurrentScene(SceneManager::SceneState::MENU);
		GATIMER()->InitTimer();
	}
	if (GetAsyncKeyState(VK_SPACE) && !pTitle->GetVisible())
	{
		pTitle->SetVisible(true);
	}
}

void Intro::Render()
{
	pBeach->Render();
	pCloud1->Render();
	pCloud2->Render();
	pTitle->Render();
}