#pragma once
#include "Stage.h"
#include "Boss.h"

class Stage1
	:public Stage
{
public:
	Stage1();
	~Stage1();

private:
	Boss* pBoss1;

	bool bBoss1;

public:
	void CreateScene(LPDIRECT3DDEVICE9 pd3dDevice);
	void Update();
	void Render(LPD3DXSPRITE pSprite);

public:
	void InitBoss();
	void RespawnBoss1();
};

