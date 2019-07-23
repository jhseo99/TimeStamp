#pragma once

typedef hash_map <DWORD, LPDIRECT3DTEXTURE9> TEXMAP;
typedef TEXMAP::iterator TEXMAP_ITER;
typedef pair <DWORD, LPDIRECT3DTEXTURE9> TEXMAP_PAIR;

#define GRAPH_MAX 132

class ObjectManager
{
public:
	~ObjectManager();

	static ObjectManager* Instance() { return &singleton; }

private:
	ObjectManager();

	static ObjectManager singleton;

	TEXMAP TextureMap;

	int PlayerHP;
	int HumanHP;

	float fGameTime;

	GameObject* m_pIntro;
	GameObject* m_pGraph[132];
	GameObject* m_pSmoke;
	GameObject* m_pButton[4];
	GameObject* m_pTitle;

	GameObject* m_pUI;
	GameObject* m_pHeart;
	GameObject* m_pHP[5];

	GameObject* m_pStage1;
	GameObject* m_pStage2;

	GameObject* m_pDie;
	GameObject* m_pEnding;

	Player* m_pPlayer;

	RedEnemy* m_pRedEnemy[10];
	int nRedCount;
	int nCurrentRed;
	float fRedTimer;

	Virus* m_pVirus[20];
	int nVirusCount;
	int nCurrentVirus;
	float fVirusTimer;

	WhiteEnemy* m_pWhite[20];
	int nWhiteCount;
	int nCurrentWhite;
	float fWhiteTimer;

	Bacteria* m_pBacteria[20];
	int nBacteriaCount;
	int nCurrentBacteria;
	float fBacteriaTimer;
	
	Cancer* m_pCancer1;
	Cancer* m_pCancer2;

public:
	char HumanHPstr[100];

private:
	float fGraphTime;
	float fGameSpeed;

public:
	void Create();
	void ProcessAll();
	void LoadFile();
	void AddObject();
	
	HRESULT AddTexture(DWORD id, TCHAR* filename);
	LPDIRECT3DTEXTURE9 GetTexture(DWORD id);

	void KeyProc();
	void MouseProc();

	int GetPlayerHP() { return PlayerHP; }
	void SetPlayerHP(int hp) { PlayerHP -= hp; }

	int GetHumanHP() { return HumanHP; }
	void SetHumanHP(int hp) { HumanHP -= hp; }

public:
	void IntroUpdate();
	void Stage1Update();
	void Stage2Update();

public:
	void RedUpdate();
	void VirusUpdate();
	void WhiteUpdate();
	void BacteriaUpdate();

public:
	void MainRender(LPD3DXSPRITE sprite);
	void Stage1Render(LPD3DXSPRITE sprite);
	void Stage2Render(LPD3DXSPRITE sprite);
	void DieRender(LPD3DXSPRITE sprite);
	void EndingRender(LPD3DXSPRITE sprite);

public:
	void Reset();
};

#define OBJMANAGER() ObjectManager::Instance()
