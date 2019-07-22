#include "DXUT.h"
#include "SoundManager.h"

SoundManager SoundManager::singleton;

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::Create(HWND hWnd)
{
	pSoundManager = new CSoundManager();
	pSoundManager->Initialize(hWnd, DSSCL_PRIORITY);
	pSoundManager->SetPrimaryBufferFormat(2, 22050, 16);

	LoadSound();
}

void SoundManager::LoadSound()
{
	pSoundManager->Create(&pSound, L"Sound\\Techno_1.wav", 0, GUID_NULL);
	pSoundManager->Create(&pGun, L"Sound\\Gun.wav", 0, GUID_NULL);
	pSoundManager->Create(&pBomb1, L"Sound\\Bomb1.wav", 0, GUID_NULL);
	pSoundManager->Create(&pBomb2, L"Sound\\Bomb2.wav", 0, GUID_NULL);
	pSoundManager->Create(&pBomb3, L"Sound\\Bomb3.wav", 0, GUID_NULL);
}