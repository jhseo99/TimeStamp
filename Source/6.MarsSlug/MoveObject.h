#pragma once
#include "Object.h"

class MoveObject
	:public Object	
{
public:
	MoveObject();
	~MoveObject();

protected:
	float fSpeedX;
	float fSpeedY;

public:
	virtual void Move();

public:
	virtual void SetSpeedX(float speed) { fSpeedX = speed; }
	virtual void SetSpeedY(float speed) { fSpeedY = speed; }
};

