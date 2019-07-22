#pragma once

#define ANIHIT 5
#define ANIEXPLOSION 16
#define ANIBOMB 15
#define ANIBOSS 30

class Enemy
	: public Object
{
public:
	Enemy(void);
	~Enemy(void);

public:
	Effect* pEffectHit;
	Effect* pExplosion;
	Effect* pEffectBomb;
	Effect* pEffectBoss;
	RECT rtAniHit[ANIHIT];
	RECT rtAniExplosion[ANIEXPLOSION];
	RECT rtAniBomb[ANIBOMB];
	RECT rtAniBoss[ANIBOSS];
	vector<Bullet*> vecBullet;
	int nBulletCount;
	int nCurrentShot;
	int nAniHitCount;
	int nAniExplosionCount;
	int nAniBombCount;
	int nAniBossCount;
	bool bAniHit;
	bool bExplosion;
	bool bAniBoss;
	bool bBomb;
	int lastHitFrame;
	int lastExplosionFrame;
	int lastBombFrame;
	int lastBossFrame;
	bool bDie;

public:
	void Respawn();
	void Move();
	void Hit(float hp);
	void SetAniRect();
	void AniHit();
	void AniExplosion();
	void AniBomb();
	void AniBoss();

private:
	virtual void Create();
	virtual void Process();
};