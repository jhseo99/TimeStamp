#pragma once

typedef hash_map <DWORD, LPDIRECT3DTEXTURE9> TEXMAP;
typedef TEXMAP::iterator TEXMAP_ITER;
typedef pair <DWORD, LPDIRECT3DTEXTURE9> TEXMAP_PAIR;

class ObjectManager
{
public:
	~ObjectManager();

	static ObjectManager* Instance() { return &singleton; }

private:
	ObjectManager();

	static ObjectManager singleton;

	TEXMAP TextureMap;;

	GameObject* pIntro;
	D3DXMATRIX matScale;

	float x;
	float y;
	float z;

	GameObject* pMenu;

	GameObject* pChoose;

	GameObject* pUI;
	GameObject* pGoal;
	GameObject* pWin;
	GameObject* pLose;

	GameObject* pStage1_Back1;
	GameObject* pStage1_Back2;
	GameObject* pStage1_Back3;

	GameObject* pStage2_Back1;
	GameObject* pStage2_Back2;
	GameObject* pStage2_Back3;

	GameObject* pStage3_Back1;
	GameObject* pStage3_Back2;
	GameObject* pStage3_Back3;

	GameObject* pMiniPlayer;
	GameObject* pMiniEnemy;

	GameObject* pEnding;

	LandRover* pPlayer;
	Enemy* pEnemy;

	GameObject* pWind;
	float fWindTime;
	int WindCount;
	RECT rtWind[3];

	int nCarCount;

	Car* pCar1[50];
	int nCurrentCar1;
	float fCar1Time;

	Car* pCar2[50];
	int nCurrentCar2;
	float fCar2Time;

	float fGameTimer;

	float fFinishTime;
	static int Coin;

	char SpeedStr[100];
	char CoinStr[1000];

	int lastFrame;

public:
	void Create();
	void PrcessAll();
	void LoadFile();
	void AddObject();

	HRESULT AddTexture(DWORD id, TCHAR* filename);
	LPDIRECT3DTEXTURE9 GetTexture(DWORD id);

	void KeyProc();
	void MouseProc();

public:
	void Stage1Update();
	void Stage2Update();
	void Stage3Update();

	void Car1Update();
	void Car2Update();
	void TruckUpdate();

	void GoalUpdate();

public:
	void IntroRender(LPD3DXSPRITE sprite);
	void MenuRender(LPD3DXSPRITE sprite);
	void ChooseRender(LPD3DXSPRITE sprite);
	void Stage1Render(LPD3DXSPRITE sprite);
	void Stage2Render(LPD3DXSPRITE sprite);
	void Stage3Render(LPD3DXSPRITE sprite);
	void EndingRedner(LPD3DXSPRITE sprite);

public:
	void Reset();

	float GetGameTimer() { return fGameTimer; }
	LandRover* GetPlayer() { return pPlayer; }
};

#define OBJMANAGER() ObjectManager::Instance()