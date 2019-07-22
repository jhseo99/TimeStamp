#pragma once
#include "DirectBullet.h"

#define SPLIT_MAX_BULLET 8

class SplitBullet
	:public DirectBullet
{
public:
	SplitBullet();
	SplitBullet(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~SplitBullet();

	DirectBullet* pBullet[SPLIT_MAX_BULLET];

private:
	float fSplitTime;
	bool bSplit;

public:
	void Create(int width, int height);
	void Split();
	void CircleRespawn(DirectBullet* pBullet, int num);
};

