#pragma once
class CollisionObject
	:public RenderObject
{
public:
	CollisionObject();
	~CollisionObject();

protected:
	RECT rtCollision;
	bool bHit;

public:
	virtual void InitCollision();

public:
	virtual RECT* GetCollisionRect() { return &rtCollision; }
	virtual void SetCollisionRect(int left, int right, int top, int bottom) { rtCollision.left = left; rtCollision.right = right; rtCollision.top = top; rtCollision.bottom = bottom; }

	virtual bool GetHit() { return bHit; }
	virtual void SetHit(bool hit) { bHit = hit; }
};

