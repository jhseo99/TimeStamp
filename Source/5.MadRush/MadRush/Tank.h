#pragma once

class Tank
	: public Enemy
{
public:
	Tank(void);
	Tank(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Tank(void);

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