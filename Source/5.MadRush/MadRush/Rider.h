#pragma once

class Rider
	: public Enemy
{
public:
	Rider(void);
	Rider(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Rider(void);

public:
	void CreateMissile();
	void Shoot(DWORD absoluteFrame);

private:
	virtual void Create();
	virtual void Process();
};