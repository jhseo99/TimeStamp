#include "DXUT.h"
#include "EnemyTeam.h"


EnemyTeam::EnemyTeam()
{
	InitEnemyTeam();
}


EnemyTeam::~EnemyTeam()
{
}

void EnemyTeam::InitEnemyTeam()
{
	for (int i = 0; i < TEAM_NUM; i++)
	{
		pEnemyAim[i] = new EnemyAim;
	}
}