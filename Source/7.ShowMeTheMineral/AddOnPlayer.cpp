#include "DXUT.h"
#include "AddOnPlayer.h"
#include "ObjectManager.h"
#include "GaTimer.h"

AddOnPlayer::AddOnPlayer()
{
}

AddOnPlayer::AddOnPlayer(LPDIRECT3DTEXTURE9 texture)
{
	SetTexture(texture);
	Create();
}

AddOnPlayer::~AddOnPlayer()
{
}

void AddOnPlayer::Create()
{
	SetRect(0, ADDON_WIDTH, 0, ADDON_HEIGHT);
	bVisible = false;
	fBulletTime = 0.0f;
	nBulletCount = 0;

	CreateBullet();
}

void AddOnPlayer::Update()
{
	if (bVisible)
	{
		Shot();
	}
	for (int i = 0; i < ADDON_BULLET; i++)
	{
		pBullet[i]->SetCollision(0, 15, 0, 15);
		pBullet[i]->Shot();
	}
}

void AddOnPlayer::CreateBullet()
{
	for (int i = 0; i < ADDON_BULLET; i++)
	{
		pBullet[i] = new Bullet(OBJMANAGER()->GetTexture(GaBase::TextureID::ADD_ON_BULLET), 15, 15);
	}
}

void AddOnPlayer::Shot()
{
	if (GATIMER()->GetTimer() - fBulletTime > 0.3f)
	{
		pBullet[nBulletCount]->SetVisible(true);
		pBullet[nBulletCount]->SetPosition(vPosition.x, vPosition.y, 0);
		pBullet[nBulletCount]->SetSpeed(15.0f);
		pBullet[nBulletCount]->SetAngle(0.0f);
		pBullet[nBulletCount]->SetShot(true);

		nBulletCount++;
		fBulletTime = GATIMER()->GetTimer();
	}
	if (nBulletCount >= ADDON_BULLET)
	{
		nBulletCount = 0;
	}
}