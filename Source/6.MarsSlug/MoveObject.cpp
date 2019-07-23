#include "DXUT.h"
#include "MoveObject.h"


MoveObject::MoveObject()
{
}


MoveObject::~MoveObject()
{
}

void MoveObject::Move()
{
	if (bVisible)
	{
		vPosition.x += fSpeedX;
		vPosition.y += fSpeedY;
		if (vPosition.x <= 0 - rtSize.right)
		{
			bVisible = false;
		}
	}
}