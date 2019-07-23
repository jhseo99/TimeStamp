#pragma once
#include "SDKsound.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	CSound* pSound;
	CSound* pGun;
	CSound* pBomb1;
	CSound* pBomb2;
	CSound* pBomb3;

	static SoundManager* Instance() { return &singleton; }

private:
	static SoundManager singleton;

	CSoundManager* pSoundManager;

public:
	void Create(HWND hWnd);
	void LoadSound();
};

#define SOUNDMANAGER() SoundManager::Instance()