#pragma once

class Wheel
	: public Enemy
{
public:
	Wheel(void);
	Wheel(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Wheel(void);

private:
	virtual void Create();
	virtual void Process();
};