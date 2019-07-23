#pragma once

class Bomber
	: public Enemy
{
public:
	Bomber(void);
	Bomber(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Bomber(void);

private:
	virtual void Create();
	virtual void Process();
};