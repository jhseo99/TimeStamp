#pragma once

#define BEACH_SECTION_NUM 8

class Beach
	:public RenderObject
{
public:
	Beach();
	Beach(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* filename);
	~Beach();

public:
	D3DXVECTOR2 vSection[BEACH_SECTION_NUM];

public:
	void SetSection();

public:
	D3DXVECTOR2* GetSection(int nSectionNum) { return &vSection[nSectionNum]; }

	void SetVector(D3DXVECTOR2* vec, float x, float y) { vec->x = x;  vec->y = y; };
};

