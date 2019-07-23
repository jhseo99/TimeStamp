#include "DXUT.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"

SceneManager SceneManager::singleton;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Create()
{
	pStage = new Stage;
	pEnding = new Ending;
	pIntro = new Intro;
	pMenu = new Menu;
}

void SceneManager::Update()
{
	switch (OBJMANAGER()->GetScene())
	{
	case ObjectManager::SceneState::INTRO:
		ShowCursor(true);
		SOUNDMANAGER()->pSound->Stop();
		pIntro->Update();
		break;
	case ObjectManager::SceneState::MENU:
		ShowCursor(true);
		SOUNDMANAGER()->pSound->Stop();
		pMenu->Update();
		break;
	case ObjectManager::SceneState::STAGE1:
	case ObjectManager::SceneState::STAGE2:
		ShowCursor(false);
		SOUNDMANAGER()->pSound->Play(0, DSBPLAY_LOOPING);
		pStage->Update();
		break;
	case ObjectManager::SceneState::END:
		ShowCursor(true);
		SOUNDMANAGER()->pSound->Stop();
		pEnding->Update();
		break;
	default:
		break;
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::MENU);
		pMenu->Create();
	}
}

void SceneManager::Render()
{
	switch (OBJMANAGER()->GetScene())
	{
	case ObjectManager::SceneState::INTRO:
		pIntro->Render();
		break;
	case ObjectManager::SceneState::MENU:
		pMenu->Render();
		break;
	case ObjectManager::SceneState::STAGE1:
	case ObjectManager::SceneState::STAGE2:
		pStage->Render();
		break;
	case ObjectManager::SceneState::END:
		pEnding->Render();
		break;
	default:
		break;
	}
}

void SceneManager::MouseProc(UINT uMsg)
{
	switch (OBJMANAGER()->GetScene())
	{
	case ObjectManager::SceneState::INTRO:
		break;
	case ObjectManager::SceneState::MENU:
		pMenu->MouseProc(uMsg);
		break;
	case ObjectManager::SceneState::STAGE1:
	case ObjectManager::SceneState::STAGE2:
		break;
	case ObjectManager::SceneState::END:
		break;
	default:
		break;
	}
}