#pragma once
#include "Bullet.h"

#define PI 3.141592

class DirectBullet
	:public Bullet
{
public:
	DirectBullet();
	DirectBullet(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~DirectBullet();

protected:
	D3DXVECTOR3 vDirect;

public:
	void Create(int width, int height);
	void Shot();

	D3DXVECTOR3* GetDirect() { return &vDirect; }
	void SetDirect(D3DXVECTOR3 direct) { vDirect = direct; }
};

