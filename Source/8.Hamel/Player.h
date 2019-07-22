#pragma once
class Player
	:public MoveObject
{
public:
	Player();
	~Player();

public:
	int m_nPlayerX;
	int m_nPlayerY;

	int m_nGoalX;
	int m_nGoalY;

	float m_fFoodGauge;
	float m_fWaterGauge;
	float m_fSleepGauge;
public:
	void Init();
	void Process(TileMap* pTileMap);

	void GetMouseClick();
	void SetDirection();
};

