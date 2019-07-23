#include "DXUT.h"
#include "GaBase.h"

SceneManager SceneManager::singleton;

SceneManager::SceneManager()
{
	Create();
}


SceneManager::~SceneManager()
{
}

void SceneManager::Create()
{
	CurrentScene = SceneState::INTRO;
	bSceneChange = false;
	fSceneAlpha = 1.0f;

	bCurrentClick = false;
	bBeforeClick = false;
}