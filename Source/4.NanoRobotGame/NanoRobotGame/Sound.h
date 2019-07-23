#pragma once

class Sound
{
public:
	~Sound();

	static Sound* Instance() { return &singleton; }

	void Init(HWND hWnd);
	bool LoadWave(TCHAR* filename, LPDIRECTSOUND3DBUFFER lpDSBuffer);

private:
	Sound();

	static Sound singleton;

	LPDIRECTSOUND8 m_pdSound;

};

#define SOUND() Sound::Instance()