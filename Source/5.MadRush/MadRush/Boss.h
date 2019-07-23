#pragma once

class Boss
	: public Enemy
{
public:
	Boss(void);
	Boss(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Boss(void);

private:
	float fWay;

public:
	void CreateMissile();
	void Shoot(DWORD absoluteFrame);
	void Circle(Bullet* bullet, int num);

private:
	virtual void Create();
	virtual void Process();
};