#pragma once

class Missile
	: public Object
{
public:
	Missile(void);
	Missile(LPDIRECT3DTEXTURE9 texture, int width, int height);
	~Missile(void);

protected:
	bool bShoot;
	float fGradiant;
	float fFirePosX;
	float fFirePosY;

public:
	void Move(D3DXVECTOR3 vDirection);
	void Hit();

	void SetFirePos(float x, float y);
	void SetGradiant(float _gradiant) { fGradiant = _gradiant; }
	void SetShoot(bool _shoot) { bShoot = _shoot; }

private:
	virtual void Create();
	virtual void Process();
};