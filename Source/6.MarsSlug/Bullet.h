#pragma once
#include "MoveObject.h"

class Bullet
	:public MoveObject
{
public:
	Bullet();
	~Bullet();

private:
	float fGradiant;
	D3DXVECTOR3 vDirection;
	bool bShot;

public:
	void InitBullet();
	void Move();
	void Move(bool bAim);
	void Hit();

	void SetGradiant(float gradiant) { fGradiant = gradiant; }
	void SetShot(bool shot) { bShot = shot; }

	D3DXVECTOR3* GetDirection() { return &vDirection; }
	void SetDirection(D3DXVECTOR3 direction) { vDirection = direction; }
};

