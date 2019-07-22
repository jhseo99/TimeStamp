#pragma once

#define TRACK_SECTION_NUM 8

class Track
	:public RenderObject
{
public:
	Track();
	Track(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	~Track();

public:
	D3DXVECTOR2 vSection[TRACK_SECTION_NUM];
	
public:
	void SetSection();

public:
	D3DXVECTOR2* GetSection(int nSectionNum) { return &vSection[nSectionNum]; }	
	
	void SetVector(D3DXVECTOR2* vec, float x, float y) { vec->x = x;  vec->y = y; };
};

