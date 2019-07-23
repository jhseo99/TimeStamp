#pragma once

class Missile
	:public Object
{
public:
	Missile();
	Missile(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Missile();

protected:
	bool bShot;
	int nStartPosX;
	int nStartPosY;

public:
	virtual void Create(int width, int height);
	
	void SetStartPoint(int x, int y);
	void Shoot();
	void SetShoot(bool shot) { bShot = shot; }
};