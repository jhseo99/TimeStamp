#pragma once

class GameObject
	:public Object
{
public:
	GameObject();
	GameObject(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~GameObject();

public:
	virtual void Create(int width, int height);

public:
	void MoveX(float speed);
	void MoveY(float speed);
};

