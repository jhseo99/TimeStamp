#pragma once

class Player
	: public Object
{
public:
	Player(void);
	Player(LPDIRECT3DTEXTURE9 texture, int x, int y);
	~Player(void);

	enum MoveDirection{LEFT, RIGHT, UP, DOWN};
	enum GunState{ ONE, TWO, THREE};

public:
	MoveDirection move;
	GunState gunstate;

	vector<Missile*> vecMissile;
	int nMissileCount;
	int nCurrentShot;

public:
	void Move();
	void CreateMissile();
	void Shoot(DWORD absoluteFrame);
	void Hit();

public:
	void SetMove(MoveDirection _move) { move = _move; }
	void Reset();

private:
	virtual void Create();
	virtual void Process();
};