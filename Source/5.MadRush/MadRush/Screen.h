#pragma once

class Screen
	: public Object
{
public:
	Screen(void);
	Screen(LPDIRECT3DTEXTURE9 texture, int x, int y);
	~Screen(void);

private:
	virtual void Create();
	virtual void Process();
};