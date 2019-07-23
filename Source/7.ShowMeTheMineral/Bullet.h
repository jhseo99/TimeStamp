#pragma once
#include "Object.h"

class Bullet
	:public Object
{
public:
	Bullet();
	Bullet(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Bullet();

protected:
	float fSpeed;
	float fAngle;
	bool bShot;

public:
	void Create(int width, int height);
	void Shot();

public:
	float GetSpeed() { return fSpeed; }
	void SetSpeed(float speed) { fSpeed = speed; }

	float GetAngle() { return fAngle; }
	void SetAngle(float angle) { fAngle = angle; }

	bool GetShot() { return bShot; }
	void SetShot(bool shot) { bShot = shot; }
};

