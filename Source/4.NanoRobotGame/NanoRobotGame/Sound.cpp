#include "stdafx.h"

Sound::Sound()
{
	m_pdSound = NULL;
}


Sound::~Sound()
{
}

void Sound::Init(HWND hWnd)
{
	DirectSoundCreate8(NULL, &m_pdSound, NULL);

	m_pdSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
}

bool Sound::LoadWave(TCHAR* filename, LPDIRECTSOUND3DBUFFER lpDSBuffer)
{
	HMMIO hmmio;
	MMCKINFO ckInRIFF, ckin;
	PCMWAVEFORMAT pcmWaveFormat;
	WAVEFORMATEX* pWaveFormat;

	hmmio = mmioOpen(filename, NULL, MMIO_ALLOCBUF | MMIO_READ);
	
	ckInRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (!mmioDescend(hmmio, &ckInRIFF, NULL, MMIO_FINDRIFF))
	{
		mmioClose(hmmio, 0);

		return FALSE;
	}

	ckin.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (!mmioDescend(hmmio, &ckin, &ckInRIFF, MMIO_FINDCHUNK))
	{
		mmioClose(hmmio, 0);

		return FALSE;
	}

	if (!mmioRead(hmmio, (HPSTR)&pcmWaveFormat, sizeof(pcmWaveFormat)))
	{
		mmioClose(hmmio, 0);

		return FALSE;
	}

	pWaveFormat = new WAVEFORMATEX;


}