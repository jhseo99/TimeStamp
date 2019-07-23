#pragma once

class Bullet
	: public Object
{
public:
	Bullet(void);
	Bullet(LPDIRECT3DTEXTURE9 texture, int width, int height, float fSpeed);
	~Bullet(void);

protected:
	int randNum;
	bool bShoot;
	float fGradiant;
	float fFirePosX;
	float fFirePosY;
	D3DXVECTOR2 vDirect;

public:
	void Move(D3DXVECTOR2* vDirection);
	void Hit();

	void SetFirePos(float x, float y);
	void SetGradiant(float _gradiant) { fGradiant = _gradiant; }
	void SetShoot(bool _shoot) { bShoot = _shoot; }
	void SetRandNum(int num) { randNum = num; }

	int GetRandNum() { return randNum; }
	D3DXVECTOR2* GetDirectVec() { return &vDirect; }

private:
	virtual void Create();
	virtual void Process();
};