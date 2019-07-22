#include "DXUT.h"
#include "Boss.h"


Boss::Boss()
{
	InitBoss();
}


Boss::~Boss()
{
}

void Boss::InitBoss()
{
	RECT rt;
	rt.left = 0;
	rt.right = BOSS_WIDTH;
	rt.top = 0;
	rt.bottom = BOSS_HEIGHT;
	SetRect(rt);

	fLastBullet = 0;
	nCurBullet = 0;

	SetSpeedX(-0.5f);
	SetSpeedY(0);

	lastEffect = 0;

	fHp = 100.0f;

	pEffect = new Effect;
	pEffect->SetAniEffect(220, 220, 5, 2);

	CreateBullet(40, 40);
}

void Boss::Process(float nWay)
{
	if (bVisible)
	{
		UpdateCollision(69, 245, 36, 253);
		Move();
		Shot(nWay);
		HitSystem(100.0f);
	}
	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBullet[i]->Move(true);
	}
	Die();
}

void Boss::Shot(float nWay)
{
	D3DXVECTOR3 vFirePos;

	if (DXUTGetTime() - fLastBullet > 5.0f)
	{
		for (int i = 0; i < (int)nWay; i++)
		{
			pBullet[nCurBullet]->SetShot(true);
			pBullet[nCurBullet]->SetVisible(true);

			vFirePos.x = vPosition.x + BOSS_WIDTH / 2;
			vFirePos.y = vPosition.y + BOSS_HEIGHT / 2;
			vFirePos.z = 0;

			pBullet[nCurBullet]->SetPosition(vFirePos);
			pBullet[nCurBullet]->SetSpeedX(10.0f);
			pBullet[nCurBullet]->SetSpeedY(10.0f);

			CircleBullet(pBullet[nCurBullet], i, nWay);

			nCurBullet++;
		}

		if (nCurBullet >= MAX_BULLET)
		{
			nCurBullet = 0;
		}

		fLastBullet = DXUTGetTime();
	}
}

void Boss::CircleBullet(Bullet* pBullet, int num, float nWay)
{
	pBullet->GetDirection()->x = (float)cos(2.0 * PI * (num  / nWay));
	pBullet->GetDirection()->y = (float)sin(2.0 * PI * (num / nWay));
	pBullet->GetDirection()->z = 0.0f;

	D3DXVec3Normalize(pBullet->GetDirection(), pBullet->GetDirection());
}

void Boss::CreateBullet(int width, int height)
{
	RECT rt;
	rt.left = 0;
	rt.right = width;
	rt.top = 0;
	rt.bottom = height;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		pBullet[i] = new Bullet;
		pBullet[i]->SetSpeedX(25.0f);
		pBullet[i]->SetSpeedY(25.0f);
		pBullet[i]->SetGradiant(0);
		pBullet[i]->SetRect(rt);
	}
}

void Boss::Die()
{
	if (bDie)
	{
		pEffect->SetPosition(vPosition);
		pEffect->SetVisible(true);
		pEffect->AniEffect(10);
	}
	if (pEffect->GetFinish())
	{
		pEffect->SetFinish(false);
		bDie = false;
	}
}