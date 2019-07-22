#pragma once
#include "Object.h"

class Stone
	:public Object
{
public:
	Stone();
	Stone(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Stone();

	enum StoneType{WAVE, FREEWAVE, HORN, HOLE};
	RECT rtStoneCollsion[3];

private:
	StoneType stoneType;

public:
	void Create(int width, int height);
	void Respawn();
	void Update();
	void SetCollision(RECT* rect, int left, int right, int top, int bottom);

	StoneType GetStoneType() { return stoneType; }
	void SetStoneType(StoneType type) { stoneType = type; }
};

