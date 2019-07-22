#pragma once

#define ANI_RUN 5

class Horse
	:public CollisionObject
{
public:
	Horse();
	~Horse();

	enum State{IDLE, RUN, JUMP};
	enum Direction{LEFT, RIGHT, UP, DOWN, LUP, RUP, LDOWN, RDOWN};
	enum HorseID{JEJU, BUSAN, SEOUL, KWANGJU};

	RenderObject pSheild;
	Fire pFire;

protected:
	int SpriteHeight;

	float fSpeed;
	float fMaxSpeed;
	float fAccel;
	float fStamina;
	float fMaxStamina;

	D3DXVECTOR2 vGamePos;
	D3DXVECTOR3 vDirectVec;
	D3DXVECTOR3 vCrossVec;

	State state;
	Direction direction;
	HorseID id;

	float fRunFrameTime;
	int nCurrentRunFrame;

	int nCollisionLeft;
	int nCollisionRight;
	int nCollisionTop;
	int nCollisionBottom;

	float fCollisionCircleX;
	float fCollisionCircleY;
	float fCollisionCircleR;

	float fCollisionCircleCenterX;
	float fCollisionCircleCenterY;

	bool bSpeedUp;

	float fMoney;

public:
	bool bShelidItem;
	bool bBoostItem;
	bool bFireItem;

	bool bSheild;

	float fBoostTime;
	bool bBoost;

	bool bFire;
	float fFireTime;

	float fDistance;

	float fHitTime;

	bool bGoal;
	
public:
	virtual void Init();
	virtual void Process();

	void Advance();

	void SetDirectVec(float x1, float y1, float x2, float y2);
	void SetTextureRect();
	void SetCollisionRect();
	void SetCollisionCircle();

	void SetHorseStat(LPDIRECT3DDEVICE9 pd3dDevice);

	void Animation();
	void AniRun();

	void SpeedUp();
	void SpeedDown();
	void MoveLeft();
	void MoveRight();

	void SetItem(Item* pItem);
	void Fire();
	void Boost();

	void HitSystem();

	void Clear();

public:
	D3DXVECTOR2* GetGamePos() { return &vGamePos; }
	void SetGamePos(D3DXVECTOR2 pos) { vGamePos = pos; }
	void SetGamePos(float x, float y) { vGamePos.x = x; vGamePos.y = y; }

	float GetSpeed() { return fSpeed; }
	void SetSpeed(float speed) { fSpeed = speed; }

	float GetMaxSpeed() { return fMaxSpeed; }
	void SetMaxSpeed(float max) { fMaxSpeed = max; }

	float GetAccel() { return fAccel; }
	void SetAccel(float accel) { fAccel = accel; }

	float GetStamina() { return fStamina; }
	void SetStamina(float stamina) { fStamina = stamina; }

	float GetMaxStamina() { return fMaxStamina; }
	void SetMaxStamina(float max) { fMaxStamina = max; }

	int GetCollisionLeft() { return nCollisionLeft; }
	int GetCollisionRight() { return nCollisionRight; }
	int GetCollisionTop() { return nCollisionTop; }
	int GetCollisionBottom() { return nCollisionBottom; }

	float GetCollisionCircleX() { return fCollisionCircleX; }
	float GetCollisionCircleY() { return fCollisionCircleY; }
	float GetCollisionCircleR() { return fCollisionCircleR; }

	float GetCollisionCircleCenterX() { return fCollisionCircleCenterX; }
	float GetCollisionCircleCenterY() { return fCollisionCircleCenterY; }

	Direction GetDirection() { return direction; }
	void SetDirection(Direction direction_) { direction = direction_; }

	HorseID GetHorseID() { return id; }
	void SetHorseID(HorseID id_) { id = id_; }

	State GetState() { return state; }
	void SetState(State state_) { state = state_; }
};

