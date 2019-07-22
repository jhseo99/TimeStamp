#pragma once
#include "EnemyAim.h"

#define TEAM_NUM 4

class EnemyTeam
	:public EnemyAim
{
public:
	EnemyTeam();
	~EnemyTeam();

public:
	EnemyAim* pEnemyAim[TEAM_NUM];

public:
	void InitEnemyTeam();
	void 
};
