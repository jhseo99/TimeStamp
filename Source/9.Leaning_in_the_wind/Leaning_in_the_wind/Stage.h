#pragma once
class Stage
{
public:
	Stage();
	~Stage();

	enum StageState{SELECT, STAGE1, SHOP, STAGE2,};
	enum CircleID{ INSIDE, OUTSIDE };

private:
	LPDIRECT3DDEVICE9 pd3dDevice;

	StageState currentStage;
	RenderObject* pSelectHorse;
	RenderObject* pShop;

	Track* pTrack;
	Beach* pBeach;

	RenderObject* pStartPoint;
	RenderObject* pLight;

	PlayerHorse* pPlayer;
	HorseAI* pHorseAI[3];

	Item* pItem[4];
	RenderObject* pItemIcon;

	CountDown* pCountDown;
	RenderObject* pUI;
	RenderObject* pMinimap;
	RenderObject* pIcon[4];
	RenderObject* pStamina[200];
	RenderObject* pHorseName;

	LPD3DXSPRITE pFontSprite;
	LPD3DXFONT pFont;

	bool bStart;

	float fStartLineX;
	float fStartLineY;

	std::vector<RenderObject*> pVecRenderObject;
	std::vector<Horse*> pVecHorses;

	std::vector<Horse*> pVecHorseRank;

public:
	void Create(LPDIRECT3DDEVICE9 pd3dDevice);

	void InitStage1();
	void InitStage2();

public:
	void Update();

	void SelectUpdate();
	void CallStage();
	void Stage1Update();
	void ShopUpdate();
	void Stage2Update();

public:
	void Render();
	void Stage1Render();
	void ShopRender();
	void Stage2Render();

public:
	void SetHorseDirection1();
	void SetHorseDistance1();
	void SetHorseDirection2();
	void SetHorseDistance2();

	void CollisionCheck1();
	void CollisionCheck2();

	void SetRenderSequence();
	bool IsCircleCollision(float fCircle1X, float fCircle1Y, float fCircle1Radius, float fCircle2X, float fCircle2Y, float fCircle2Radius);
	void SetLimitPos(float fCircleX, float fCircleY, float fCircleRadius, Horse* pPlayer, CircleID id);
	bool IsRectCollision(RECT* rtCollision1, RECT* rtCollision2);
	bool IsRectCollision(float left1, float right1, float top1, float bottom1, float left2, float right2, float top2, float bottom2);
	bool IsTriangleCollision(D3DXVECTOR2 vec1_1, D3DXVECTOR2 vec1_2, D3DXVECTOR2 vec2_1, D3DXVECTOR2 vec2_2, D3DXVECTOR2* pOut);

public:
	void SetItemIcon();
	void SetRanking();
};

