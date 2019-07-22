#pragma once

class Effect
	: public Object
{
public:
	Effect(void);
	Effect(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Effect(void);

private:
	virtual void Create();
	virtual void Process();
};