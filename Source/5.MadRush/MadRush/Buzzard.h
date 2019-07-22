#pragma once

class Buzzard
	: public Enemy
{
public:
	Buzzard(void);
	Buzzard(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Buzzard(void);

private:
	float fWay;

public:
	void CreateMissile();
	void Shoot(DWORD absoluteFrame);
	void nWay(Bullet* bullet, int num);

private:
	virtual void Create();
	virtual void Process();
};