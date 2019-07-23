#include "DXUT.h"
#include "Stage1.h"


Stage1::Stage1()
{
}


Stage1::~Stage1()
{
}

void Stage1::CreateScene(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CreateObject(pd3dDevice);
	InitBoss();

	pStage_1->Create(pd3dDevice, L"texture\\stage1_1.png");
	pStage_2->Create(pd3dDevice, L"texture\\stage1_2.png");
	pStone1->Create(pd3dDevice, L"texture\\stone1.png");
	pStone2->Create(pd3dDevice, L"texture\\stone2.png");
	pBoss1->Create(pd3dDevice, L"texture\\boss1.png");
	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBoss1->GetBullet(i)->Create(pd3dDevice, L"texture\\16Bullet.png");
	}
}

void Stage1::Update()
{
	RespawnBoss1();
	UpdateStage();
	pBoss1->Process(16.0f);
	for (int i = 0; i < MAX_BULLET; i++)
	{
		CollisionCheck(PLAYER(), pBoss1->GetBullet(i));
		CollisionCheck(pBoss1, PLAYER()->GetBullet(i));
	}
}

void Stage1::Render(LPD3DXSPRITE pSprite)
{
	RenderStage(pSprite);

	pBoss1->Render(pSprite);
	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBoss1->GetBullet(i)->Render(pSprite);
	}

	pStone1->Render(pSprite);
	pStone2->Render(pSprite);

}

void Stage1::InitBoss()
{
	pBoss1 = new Boss;
	bBoss1 = false;
}

void Stage1::RespawnBoss1()
{
	if (DXUTGetTime() > 30.0f && !bBoss1)
	{
		pBoss1->SetVisible(true);

		D3DXVECTOR3 vPos;
		vPos.x = 1600.0f;
		vPos.y = 300.0f;
		vPos.z = 0.0f;

		pBoss1->SetPosition(vPos);
		bBoss1 = true;
	}
}
