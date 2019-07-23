#pragma once
class Item
	:public CollisionObject
{
public:
	Item();
	Item(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	~Item();

	enum ItemID{MONEY, SHEILD, BOOST, WIND};

private:
	D3DXVECTOR2 vGamePos;

	ItemID id;

public:
	void Init();
	void Process();
	void SetCollisionRect();

public:
	D3DXVECTOR2* GetGamePos() { return &vGamePos; }
	void SetGamePos(float x, float y) { vGamePos.x = x; vGamePos.y = y; }

	ItemID GetID() { return id; }
	void SetID(ItemID id_) { id = id_; }
};

