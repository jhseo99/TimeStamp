#pragma once

class GaugeBar
	: public Object
{
public:
	GaugeBar(void);
	GaugeBar(LPDIRECT3DTEXTURE9 texture);
	~GaugeBar(void);

private:
	virtual void Create();
	virtual void Process();
};