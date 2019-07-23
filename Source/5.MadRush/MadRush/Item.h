#pragma once

class Item
	: public Object
{
public:
	Item(void);
	Item(LPDIRECT3DTEXTURE9 texture);
	~Item(void);

public:
	void Respawn();
	void Move();
	void HitHp();
	void HitGun();

private:
	virtual void Create();
	virtual void Process();
};