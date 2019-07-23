#pragma once
#include "Bullet.h"

class AimBullet
	:public Bullet
{
public:
	AimBullet();
	AimBullet(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~AimBullet();

private:
	Object* pTarget;
	D3DXVECTOR3 vDirect;
	bool bAim;

public:
	void Create(int width, int height);
	void Shot();
	void Aim(Object* pObject);

	bool GetAim() { return bAim; }
	void SetAim(bool aim) { bAim = aim; }

	D3DXVECTOR3* GetDirect() { return &vDirect; }
	void SetDirect(D3DXVECTOR3 direct) { vDirect = direct; }
	void SetDirect(float x, float y, float z) { vDirect.x = x; vDirect.y = y; vDirect.z = z; }
};

