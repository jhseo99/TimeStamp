#include "DXUT.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
}

Obstacle::Obstacle(LPDIRECT3DTEXTURE9 texture, int width, int height)
{
	SetTexture(texture);
	Create(width, height);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Create(int width, int height)
{
	SetRect(0, width, 0, height);
	bVisible = false;
	bHit = false;
	type = ObstacleType::ROCK;
}

void Obstacle::Respawn()
{
	vPosition.x = 1024.0f;
	vPosition.y = rand() % 500;
	vPosition.z = 0;

	bVisible = true;
	bHit = false;
}

void Obstacle::Update(Player* pPlayer)
{
	if (bVisible)
	{
		vPosition.x -= 8.0f;
		if (bHit)
		{
			if (pPlayer->GetHitAni())
			{
				pPlayer->SetSpeed(2.0f);
			}
			else if (!pPlayer->GetHitAni())
			{
				pPlayer->SetSpeed(5.0f);
				bHit = false;
			}
		}
	}
	
	switch (type)
	{
	case ObstacleType::ROCK:
		SetCollision(17, 152, 36, 72);
		break;
	case ObstacleType::SEAWEED:
		SetCollision(41, 87, 35, 79);
		break;
	default:
		break;
	}
}