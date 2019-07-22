#pragma once
#include "Object.h"
#include "Player.h"

class Obstacle
	:public Object
{
public:
	Obstacle();
	Obstacle(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Obstacle();

	enum ObstacleType{ROCK, SEAWEED};

private:
	ObstacleType type;

public:
	void Create(int width, int height);
	void Respawn();
	void Update(Player* pPlayer);

	ObstacleType GetType() { return type; }
	void SetType(ObstacleType _type) { type = _type; }
};

