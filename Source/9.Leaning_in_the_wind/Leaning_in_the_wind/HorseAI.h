#pragma once
class HorseAI
	:public Horse
{
public:
	HorseAI();
	HorseAI(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	~HorseAI();

private:
	float fPathUpdateTime;
	int nWay;

	bool bSpeed;

public:
	void InitAI();
	void Process();

	void SetWay();
	void SpeedUpdate();
};

