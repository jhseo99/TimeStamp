#include "DXUT.h"
#include "Intro.h"
#include "ObjectManager.h"

Intro::Intro()
{
	Create();
}


Intro::~Intro()
{
}

void Intro::Create()
{
	pIntro = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::INTRO), 1024, 768, 0, 0);
}

void Intro::Update()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::MENU);
	}
}

void Intro::Render()
{
	pIntro->Render(OBJMANAGER()->GetSprite());
}