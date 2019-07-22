#pragma once
#include "MoveObject.h"

#define STAGE_WIDTH 1600
#define STAGE_HEIGHT 900

class Background
	:public MoveObject
{
public:
	Background();
	~Background();

public:
	void InitBackground();
	void MoveBackground();
};

