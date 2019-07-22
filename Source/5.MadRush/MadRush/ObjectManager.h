#pragma once

typedef hash_map <DWORD, LPDIRECT3DTEXTURE9> TEXMAP;
typedef TEXMAP::iterator TEXMAP_ITER;
typedef pair <DWORD, LPDIRECT3DTEXTURE9> TEXMAP_PAIR;

class ObjectManager
{
public:
	~ObjectManager(void);

	static ObjectManager* Instance() { return &singleton; }

private:
	ObjectManager(void);

	static ObjectManager singleton;

	TEXMAP TextureMap;

	float PlayerHp;
	float fGameTime;
	int Score;
	int GunLevel;

	Screen* pIntro;
	Screen* pDie;
	Screen* pEnding;

	Screen* pBg_Stage1_1;
	Screen* pBg_Stage1_2;

	Screen* pBg_Stage2_1;
	Screen* pBg_Stage2_2;

	Screen* pStorm_1;
	Screen* pStorm_2;

	Screen* pUI;

	Player* pPlayer1;
	Player* pPlayer2;

	Boss* pBoss;

	GaugeBar* pGaugeBar;
	vector<Gauge*> vecGauge;
	int nGaugeCount;

	float fRespawnTime;
	D3DXVECTOR3 vDirection;

	vector<Rider*> vecRider;
	int nRiderCount;
	int nCurrentRider;
	float fRiderTime;

	vector<Soldier*> vecSoldier;
	int nSoldierCount;
	int nCurrentSoldier;
	float fSoldierTime;

	vector<Bomber*> vecBomber;
	int nBomberCount;
	int nCurrentBomber;
	float fBomberTime;

	vector<Wheel*> vecWheel;
	int nWheelCount;
	int nCurrentWheel;
	float fWheelTime;

	vector<Buzzard*> vecBuzzard;
	int nBuzzardCount;
	int nCurrentBuzzard;
	float fBuzzardTime;

	vector<Tank*> vecTank;
	int nTankCount;
	int nCurrentTank;
	float fTankTime;

	vector<Truck*> vecTruck;
	int nTruckCount;
	int nCurrentTruck;
	float fTruckTime;

	vector<Item*> vecGun;
	int nGunCount;
	int nCurrentGun;
	float fGunTime;

	vector<Item*> vecHpUp;
	int nHpUpCount;
	int nCurrentHpUp;
	float fHpUpTime;

	char Timestr[1000];
	char Scorestr[1000];

	bool bCheat;

public:
	void Create();
	void ProcessAll();
	BOOL CollisonCheck( int aLeft, int aRight, int aTop, int aBottom,
						int bLeft, int bRight, int bTop, int bBottom);
	void LoadFile();
	void AddObject();

	HRESULT AddTexture(DWORD id, TCHAR* filename);
	LPDIRECT3DTEXTURE9 GetTexture(DWORD id);

	void KeyProc();
	void MouseProc();

public:
	void IntroRender(LPD3DXSPRITE sprite);
	void Stage1Render(LPD3DXSPRITE sprite);
	void Stage2Render(LPD3DXSPRITE sprite);
	void DieRender(LPD3DXSPRITE sprite);
	void EndingRender(LPD3DXSPRITE sprite);

public:
	void Stage1Update();
	void Stage2Update();

public:
	void RiderUpdate();
	void SoldierUpdate();
	void BomberUpdate();
	void WheelUpdate();
	void BuzzardUpdate();
	void TankUpdate();
	void TruckUpdate();

	void ItemUpdate();

	void HpUpdate();
	void GunUpdate();

	void Reset();

public:
	Player* GetPlayer1() { return pPlayer1; }
	Player* GetPlayer2() { return pPlayer2; }

	void SetScore(int _score) { Score += _score; }
	void SetHP(float _hp);
	void SetGun(int _gun) { GunLevel += _gun; }
};

#define OBJMANAGER() ObjectManager::Instance()