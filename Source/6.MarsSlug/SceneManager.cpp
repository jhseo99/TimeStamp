#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	srand((unsigned int)time(NULL));
}


SceneManager::~SceneManager()
{
}

void SceneManager::Create(LPDIRECT3DDEVICE9 pd3dDevice)
{
	D3DXCreateSprite(pd3dDevice, &pSprite);
	AddScene();

	gameScene = GameScene::INTRO;

	pIntro->CreateScene(pd3dDevice);
	pStage1->CreateScene(pd3dDevice);
}

void SceneManager::Update()
{
	KeyProc();

	switch (gameScene)
	{
	case GameScene::INTRO:
		break;
	case GameScene::MENU:
		break;
	case GameScene::GAME1:
		pStage1->Update();
		break;
	case GameScene::GAME2:
		break;
	default:
		break;
	}

	if (pIntro->bSceneEnd)
	{
		gameScene = GameScene::GAME1;
		pIntro->bSceneEnd = false;
	}
}

void SceneManager::Render()
{
	switch (gameScene)
	{
	case GameScene::INTRO:
		pIntro->Render(pSprite);
		break;
	case GameScene::MENU:
		break;
	case GameScene::GAME1:
		pStage1->Render(pSprite);
		break;
	case GameScene::GAME2:
		break;
	default:
		break;
	}
}

void SceneManager::KeyProc()
{
	switch (gameScene)
	{
	case SceneManager::INTRO:
		pIntro->KeyProc();
		break;
	case GameScene::MENU:
		break;
	case GameScene::GAME1:
		pStage1->KeyProc();
		break;
	case GameScene::GAME2:
		break;
	default:
		break;
	}
}

void SceneManager::MouseProc(UINT nMsg)
{
	
}

void SceneManager::AddScene()
{
	pIntro = new Intro;
	pStage1 = new Stage1;
}