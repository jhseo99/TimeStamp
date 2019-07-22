#pragma once
#include "GaBase.h"

typedef hash_map <DWORD, LPDIRECT3DTEXTURE9> TEXMAP;
typedef TEXMAP::iterator TEXMAP_ITER;
typedef pair <DWORD, LPDIRECT3DTEXTURE9> TEXMAP_PAIR;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager* Instance() { return &singleton; }

	enum SceneState{INTRO, MENU, STAGE1, STAGE2, END};

	int FirstScore;
	int SecondScore;
	int ThirdScore;

	char FirstPlayer[5];
	char SecondPlayer[5];
	char ThirdPlayer[5];

	char CurrentPlayer[5];

private:
	static ObjectManager singleton;

	LPDIRECT3DDEVICE9 pd3dDevice;
	LPD3DXSPRITE pSprite;
	LPDIRECT3DTEXTURE9 pTexture;

	LPD3DXFONT pFontTime;
	LPD3DXFONT pFontStr;

	TEXMAP TextureMap;

	SceneState currentScene;

	int Score;

public:
	void Create(LPDIRECT3DDEVICE9 pd3dDevice);
	void LoadTexture(TCHAR* filename, DWORD id);
	LPDIRECT3DTEXTURE9 GetTexture(DWORD id);

public:
	LPDIRECT3DDEVICE9 GetDevice() { return pd3dDevice; }
	LPD3DXSPRITE GetSprite() { return pSprite; }

	SceneState GetScene() { return currentScene; }
	void SetScene(SceneState scene) { currentScene = scene; }

	LPD3DXFONT GetFontTime() { return pFontTime; }
	LPD3DXFONT GetFontStr() { return pFontStr; }

	int GetScore() { return Score; }
	void SetScore(int score) { Score = score; }
};

#define OBJMANAGER() ObjectManager::Instance()