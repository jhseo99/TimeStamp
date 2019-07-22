#pragma once
class PlayerHorse
	:public Horse
{
public:
	PlayerHorse();
	PlayerHorse(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	~PlayerHorse();

public:
	void Process();
	void KeyProc();

public:
	float GetMoney() { return fMoney; }
	void SetMoney(float money) { fMoney = money; }
};

