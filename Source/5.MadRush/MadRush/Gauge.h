#pragma once

class Gauge
	: public Object
{
public:
	Gauge(void);
	Gauge(LPDIRECT3DTEXTURE9 texture);
	~Gauge(void);

private:
	virtual void Create();
	virtual void Process();
};