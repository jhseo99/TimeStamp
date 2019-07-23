#pragma once

class Soldier
	: public Enemy
{
public:
	Soldier(void);
	Soldier(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Soldier(void);

public:
	void CreateMissile();
	void Shoot(DWORD absoluteFrame);
	void Aim();

private:
	virtual void Create();
	virtual void Process();
};