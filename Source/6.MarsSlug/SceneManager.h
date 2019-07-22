#pragma once
#include <time.h>
#include "Object.h"
#include "Intro.h"
#include "Stage1.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	enum GameScene{INTRO, MENU, GAME1, GAME2};

private:
	LPD3DXSPRITE pSprite;
 
	Intro* pIntro;
	Stage1* pStage1;

	GameScene gameScene;

public:
	void Create(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	void Render();
	void KeyProc();
	void MouseProc(UINT nMsg);

private:
	void AddScene();
};

