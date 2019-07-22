#include "DXUT.h"
#include "Intro.h"


Intro::Intro()
{
}


Intro::~Intro()
{
}

void Intro::CreateScene(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pIntro = new Background;
	pIntro->Create(pd3dDevice, L"texture\\Intro.png");
	pIntro->SetVisible(true);
}

void Intro::Render(LPD3DXSPRITE pSprite)
{
	pIntro->Render(pSprite);
}