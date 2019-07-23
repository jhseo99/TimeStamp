#pragma once
#include "MoveObject.h"

class Enemy
	:public MoveObject
{
public:
	Enemy();
	~Enemy();

private:
	bool bSplit;
	float lastHit;

public:
	void HitSystem(float hp);
	void HitAni();

	bool GetSplit() { return bSplit; }
	void SetSplit(bool split) { bSplit = split; }
};

