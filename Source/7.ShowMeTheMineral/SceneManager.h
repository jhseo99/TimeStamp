#pragma once
#include "Stage.h"
#include "Ending.h"
#include "Intro.h"
#include "Menu.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* Instance() { return &singleton; }

private:
	static SceneManager singleton;

	Stage* pStage;
	Ending* pEnding;
	Intro* pIntro;
	Menu* pMenu;

public:
	void Create();
	void Update();
	void Render();
	void MouseProc(UINT uMsg);
};

#define SCENE() SceneManager::Instance()