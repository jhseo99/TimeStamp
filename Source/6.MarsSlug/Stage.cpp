#include "DXUT.h"
#include "Stage.h"

Stage::Stage()
{
}


Stage::~Stage()
{
}

void Stage::CreateObject(LPDIRECT3DDEVICE9 pd3dDevice)
{
	InitObject();

	PLAYER()->Create(pd3dDevice, L"texture\\Player.png");
	for (int i = 0; i < MAX_BULLET; i++)
	{
		PLAYER()->GetBullet(i)->Create(pd3dDevice, L"texture\\PlayerBullet.png");
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemyAim[i]->Create(pd3dDevice, L"texture\\EnemyAim.png");
		pEnemyAim[i]->GetEffect()->Create(pd3dDevice, L"texture\\Effect1.png");
		for (int j = 0; j < MAX_BULLET; j++)
		{
			pEnemyAim[i]->GetBullet(j)->Create(pd3dDevice, L"texture\\AimBullet.png");
		}
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemyDash[i]->Create(pd3dDevice, L"texture\\EnemyDash.png");
		pEnemyDash[i]->GetEffect()->Create(pd3dDevice, L"texture\\Effect2.png");
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemySplit[i]->Create(pd3dDevice, L"texture\\EnemySplit.png");
		pEnemySplit[i]->GetEffect()->Create(pd3dDevice, L"texture\\Effect1.png");
		for (int j = 0; j < MAX_BULLET; j++)
		{
			pEnemySplit[i]->GetBullet(j)->Create(pd3dDevice, L"texture\\SplitBullet.png");
		}
		for (int k = 0; k < SPLIT_NUM; k++)
		{
			pEnemySplit[i]->GetMiniSplit(k)->Create(pd3dDevice, L"texture\\MiniSplit.png");
			pEnemySplit[i]->GetMiniSplit(k)->GetEffect()->Create(pd3dDevice, L"texture\\Effec2.png");
		}
	}
}

void Stage::UpdateStage()
{
	RespawnAim();
	RespawnDash();
	RespawnSplit();

	pStage_1->MoveBackground();
	pStage_2->MoveBackground();
	pStone1->MoveBackground();
	pStone2->MoveBackground();

	PLAYER()->Process();

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemyAim[i]->Process(PLAYER());
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemyDash[i]->Process();
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemySplit[i]->Process(PLAYER());
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		CollisionCheck(PLAYER(), pEnemyDash[i]);
		for (int j = 0; j < MAX_BULLET; j++)
		{
			CollisionCheck(PLAYER(), pEnemyAim[i]->GetBullet(j));
			CollisionCheck(PLAYER(), pEnemySplit[i]->GetBullet(j));
			CollisionCheck(pEnemyAim[i], PLAYER()->GetBullet(j));
			CollisionCheck(pEnemyDash[i], PLAYER()->GetBullet(j));
			CollisionCheck(pEnemySplit[i], PLAYER()->GetBullet(j));
			for (int k = 0; k < SPLIT_NUM; k++)
			{
				CollisionCheck(pEnemySplit[i]->GetMiniSplit(k), PLAYER()->GetBullet(j));
			}
		}
		for (int k = 0; k < SPLIT_NUM; k++)
		{
			CollisionCheck(PLAYER(), pEnemySplit[i]->GetMiniSplit(k));
		}
	}

}

void Stage::RenderStage(LPD3DXSPRITE pSprite)
{
	pStage_1->Render(pSprite);
	pStage_2->Render(pSprite);
	PLAYER()->Render(pSprite);
	for (int i = 0; i < MAX_BULLET; i++)
	{
		PLAYER()->GetBullet(i)->Render(pSprite);
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		for (int j = 0; j < MAX_BULLET; j++)
		{
			pEnemyAim[i]->GetBullet(j)->Render(pSprite);
		}
		pEnemyAim[i]->Render(pSprite);
		pEnemyAim[i]->GetEffect()->Render(pSprite);
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemyDash[i]->Render(pSprite);
		pEnemyDash[i]->GetEffect()->Render(pSprite);
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		for (int j = 0; j < MAX_BULLET; j++)
		{
			pEnemySplit[i]->GetBullet(j)->Render(pSprite);
		}
		for (int k = 0; k < SPLIT_NUM; k++)
		{
			pEnemySplit[i]->GetMiniSplit(k)->Render(pSprite);
			pEnemySplit[i]->GetMiniSplit(k)->GetEffect()->Render(pSprite);
		}
		pEnemySplit[i]->Render(pSprite);
		pEnemySplit[i]->GetEffect()->Render(pSprite);
	}
}

void Stage::KeyProc()
{
	if (GetAsyncKeyState('W'))
	{
		PLAYER()->SetMoveState(Player::MoveState::UP);
		PLAYER()->Move();
	}
	if (GetAsyncKeyState('A'))
	{
		PLAYER()->SetMoveState(Player::MoveState::LEFT);
		PLAYER()->Move();
	}
	if (GetAsyncKeyState('S'))
	{
		PLAYER()->SetMoveState(Player::MoveState::DOWN);
		PLAYER()->Move();
	}
	if (GetAsyncKeyState('D'))
	{
		PLAYER()->SetMoveState(Player::MoveState::RIGHT);
		PLAYER()->Move();
	}
	if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_UP))
	{
		PLAYER()->SetGunState(Player::GunDirection::CHANGELT);
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		PLAYER()->SetGunState(Player::GunDirection::CHANGET);
	}
	else if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_DOWN))
	{
		PLAYER()->SetGunState(Player::GunDirection::CHANGELB);
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		PLAYER()->SetGunState(Player::GunDirection::CHANGEB);
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		PLAYER()->SetGunState(Player::GunDirection::IDLE);
	}
}

void Stage::CollisionCheck(Object* pObject1, Object* pObject2)
{
	if (pObject1->GetVisible() && pObject2->GetVisible())
	{
		if (pObject1->GetCollision()->left > pObject2->GetCollision()->right ||
			pObject1->GetCollision()->right < pObject2->GetCollision()->left ||
			pObject1->GetCollision()->top > pObject2->GetCollision()->bottom ||
			pObject1->GetCollision()->bottom < pObject2->GetCollision()->top)
		{

		}
		else
		{
			pObject1->SetHit(true);
			pObject2->SetHit(true);
		}
	}
}

void Stage::InitObject()
{
	pStage_1 = new Background;
	pStage_2 = new Background;

	D3DXVECTOR3 vStage1Pos;
	vStage1Pos.x = 0.0f;
	vStage1Pos.y = 0.0f;
	vStage1Pos.z = 0.0f;
	pStage_1->SetPosition(vStage1Pos);

	D3DXVECTOR3 vStage2Pos;
	vStage2Pos.x = 1600.0f;
	vStage2Pos.y = 0.0f;
	vStage2Pos.z = 0.0f;
	pStage_2->SetPosition(vStage2Pos);

	pStone1 = new Background;
	pStone2 = new Background;

	D3DXVECTOR3 vStone1Pos;
	vStone1Pos.x = 0.0f;
	vStone1Pos.y = 0.0f;
	vStone1Pos.z = 0.0f;
	pStone1->SetPosition(vStone1Pos);
	pStone1->SetSpeedX(1.0f);

	D3DXVECTOR3 vStone2Pos;
	vStone2Pos.x = 1600.0f;
	vStone2Pos.y = 0.0f;
	vStone2Pos.z = 0.0f;
	pStone2->SetPosition(vStone2Pos);
	pStone2->SetSpeedX(1.0f);

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemyAim[i] = new EnemyAim;
	}
	nCurEnemyAim = 0;
	fLastEnemyAim = 0.0f;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemyDash[i] = new EnemyDash;
	}
	nCurEnemyDash = 0;
	fLastEnemyDash = 0.0f;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		pEnemySplit[i] = new EnemySplit;
	}
	nCurEnemySplit = 0;
	fLastEnemySplit = 0.0f;
}

void Stage::RespawnAim()
{
	if (DXUTGetTime() - fLastEnemyAim > 3.0f)
	{
		D3DXVECTOR3 vPos;
		vPos.x = 1600.0f;
		vPos.y = (rand() % 600) + 50;
		vPos.z = 0.0f;

		pEnemyAim[nCurEnemyAim]->SetVisible(true);
		pEnemyAim[nCurEnemyAim]->SetPosition(vPos);

		nCurEnemyAim++;
		fLastEnemyAim = DXUTGetTime();
	}
	if (nCurEnemyAim >= MAX_ENEMY)
	{
		nCurEnemyAim = 0;
	}
}

void Stage::RespawnDash()
{
	if (DXUTGetTime() - fLastEnemyDash > 5.0f)
	{
		D3DXVECTOR3 vPos;
		vPos.x = 1600.0f;
		vPos.y = (rand() % 600) + 50;
		vPos.z = 0.0f;

		pEnemyDash[nCurEnemyDash]->SetVisible(true);
		pEnemyDash[nCurEnemyDash]->SetPosition(vPos);

		pEnemyDash[nCurEnemyDash]->Dash(PLAYER());

		nCurEnemyDash++;
		fLastEnemyDash = DXUTGetTime();
	}
	if (nCurEnemyDash >= MAX_ENEMY)
	{
		nCurEnemyDash = 0;
	}
}

void Stage::RespawnSplit()
{
	if (DXUTGetTime() - fLastEnemySplit > 10.0f)
	{
		D3DXVECTOR3 vPos;
		vPos.x = 1600.0f;
		vPos.y = (rand() % 600) + 50;
		vPos.z = 0.0f;

		pEnemySplit[nCurEnemySplit]->SetVisible(true);
		pEnemySplit[nCurEnemySplit]->SetPosition(vPos);

		nCurEnemySplit++;
		fLastEnemySplit = DXUTGetTime();
	}
	if (nCurEnemySplit >= MAX_ENEMY)
	{
		nCurEnemySplit = 0;
	}
}