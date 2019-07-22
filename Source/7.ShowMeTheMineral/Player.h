#pragma once
#include "Object.h"
#include "Bullet.h"
#include "AimBullet.h"
#include "Effect.h"
#include "AddOnPlayer.h"

#define PLAYER_WIDTH 110
#define PLAYER_HEIGHT 50
#define PLAYER_MAX_BULLET 150
#define ANI_MOVE 4
#define MAX_ADDON 2

class Player
	:public Object
{
public:
	Player();
	Player(LPDIRECT3DTEXTURE9 texture);
	~Player();

	enum MoveState{LEFT, RIGHT, UP, DOWN};
	enum GunState{BASE, DOUBLE, THREE, MISSILE, MISSILE_THREE, MISSILE_AIM};

	Bullet* pBullet[PLAYER_MAX_BULLET];
	Bullet* pMissile[PLAYER_MAX_BULLET];
	AimBullet* pAimMissile[PLAYER_MAX_BULLET];

	Effect* pFireEffect;
	Effect* pBombEffect;

	AddOnPlayer* pAddon[MAX_ADDON];
	
private:
	float fSpeed;
	float fDamage;
	
	float fBulletTime;
	int nBulletCount;
	int nGunLevel;
	float fGunTime;

	MoveState moveState;
	GunState gunState;
	GunState beforeGun;

	RECT rtMove[ANI_MOVE];
	float fAniMoveTime;
	int nMoveCount;
	int nCurrentMove;

	int nBombCount;
	bool bBomb;

	D3DXMATRIX matCamera;

	float fDefence;
	float fDefenceTime;

	bool bHitAni;
	float fHitTime;

	int nAddonLevel;

	bool bPhenix;

public:
	void Create();
	void Update();

public:
	void Move();
	void CreateBullet();
	void Shot();

	void BaseShot(Bullet* pBullet[]);
	void DoubleShot(Bullet* pBullet[]);
	void ThreeShot(Bullet* pBullet[]);
	void AimShot(AimBullet* pBullet[]);

	void MissileSystem();

	void SetAniRect();
	void AniMove();

	void Bomb();

	void CameraMove();

	void DefenceUp();

	void HitSystem();

	void AddOn();

public:
	MoveState GetMoveState() { return moveState; }
	void SetMoveState(MoveState state) { moveState = state; }

	GunState GetGunState() { return gunState; }
	void SetGunState(GunState state) { gunState = state; }

	float GetSpeed() { return fSpeed; }
	void SetSpeed(float speed) { fSpeed = speed; }

	float GetDamage() { return fDamage; }
	void SetDamage(float damage) { fDamage = damage; }

	int GetGunLevel() { return nGunLevel; }
	void SetGunLevel(int level) { nGunLevel = level; }

	float GetGunTime() { return fGunTime; }
	void SetGunTime(float time) { fGunTime = time; }

	bool GetBomb() { return bBomb; }
	void SetBomb(bool bomb) { bBomb = bomb; }

	int GetBombCount() { return nBombCount; }
	void SetBombCount(int count) { nBombCount = count; }

	D3DXMATRIX* GetCamera() { return &matCamera; }

	float GetDefence() { return fDefence; }
	void SetDefence(float defence) { fDefence = defence; }

	bool GetHitAni() { return bHitAni; }
	void SetHitAni(bool hitani) { bHitAni = hitani; }

	int GetAddonLevel() { return nAddonLevel; }
	void SetAddonLevel(int level) { nAddonLevel = level; }

	bool GetPhenix() { return bPhenix; }
	void SetPhenix(bool phenix) { bPhenix = phenix; }
};

