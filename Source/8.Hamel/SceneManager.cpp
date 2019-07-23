#include "DXUT.h"
#include "GaBase.h"

SceneManager SceneManager::singleton;

SceneManager::SceneManager()
{
	Init();
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_enCurrentScene = Scene::STAGE;
}