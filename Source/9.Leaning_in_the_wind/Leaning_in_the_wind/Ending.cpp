#include "DXUT.h"
#include "GaBase.h"


Ending::Ending()
{
}


Ending::~Ending()
{
}


void Ending::Create(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pEnding = new RenderObject;
	pEnding->CreateTexture(pd3dDevice, L"texture\\ending.png");
	pEnding->SetRect(0, 800, 0, 600);
	pEnding->SetTranslate(0, 0);
	pEnding->SetPosition(0, 0, 0);
	pEnding->SetVisible(true);

	pStar1 = new RenderObject;
	pStar1->CreateTexture(pd3dDevice, L"texture\\star1.png");
	pStar1->SetRect(0, 800, 0, 600);
	pStar1->SetTranslate(0, 0);
	pStar1->SetPosition(0, 0, 0);
	pStar1->SetVisible(true);

	pStar2 = new RenderObject;
	pStar2->CreateTexture(pd3dDevice, L"texture\\star2.png");
	pStar2->SetRect(0, 800, 0, 600);
	pStar2->SetTranslate(0, 0);
	pStar2->SetPosition(0, 0, 0);
	pStar2->SetVisible(true);

	pMessage = new RenderObject;
	pMessage->CreateTexture(pd3dDevice, L"texture\\message.png");
	pMessage->SetRect(0, 800, 0, 600);
	pMessage->SetTranslate(0, 0);
	pMessage->SetPosition(0, 0, 0);
	pMessage->SetVisible(true);

	fAlpha = 1.0f;
	fAlpha2 = 0.0f;
}

void Ending::Update()
{
	fAlpha -= 0.01f;
	if (fAlpha <= 0)
	{
		fAlpha = 1.0f;
	}
	fAlpha2 += 0.01f;
	if (fAlpha2 >= 1)
	{
		fAlpha2 = 0.0f;
	}

	pStar1->SetColor(1.0f, 1.0f, 1.0f, fAlpha);
	pStar2->SetColor(1.0f, 1.0f, 1.0f, fAlpha2);
}

void Ending::Render()
{
	pEnding->Render();
	pStar1->Render();
	pStar2->Render();
	pMessage->Render();
}