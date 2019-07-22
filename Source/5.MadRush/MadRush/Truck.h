#pragma once

class Truck
	: public Enemy
{
public:
	Truck(void);
	Truck(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Truck(void);

public:
	void CreateMissile();
	void Shoot(DWORD absoluteFrame);
	void Aim();

private:
	virtual void Create();
	virtual void Process();
};