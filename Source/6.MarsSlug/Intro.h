#pragma once
#include "Scene.h"
#include "Background.h"

class Intro
	:public Scene
{
public:
	Intro();
	~Intro();

protected:
	Background* pIntro;

public:
	void CreateScene(LPDIRECT3DDEVICE9 pd3dDevice);
	void Render(LPD3DXSPRITE pSprite);
};
