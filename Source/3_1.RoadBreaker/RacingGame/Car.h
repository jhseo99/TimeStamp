#pragma once

class Car
	:public Object
{
public:
	Car();
	Car(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Car();

public:
	virtual void Create(int width, int height);

	void Respawn();
	void Move();
};

