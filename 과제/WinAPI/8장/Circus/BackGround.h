#pragma once
#include"mecro.h"

class BackGround
{
protected:
	HDC m_hBackBuffer;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	BITMAP m_bit;
	SIZE m_size;
	RECT m_rect;
	State m_state;
	int m_ispeed;
public:
	virtual void Init(int x,int y,HDC _m_hBuffer) = 0;
	virtual void Render(HDC _m_hBuffer) =0;
	virtual void Update(Direction direction, float time) = 0;
	virtual void replay(int x,int y) = 0;
	void End();
};
class Ground:public BackGround
{
public:
	virtual void Init(int x, int y,HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time) {};
	virtual void replay(int x, int y) {};
};
class crowd:public BackGround
{
private:
	HDC m_hBackBuffer2;
	HBITMAP m_BitMap2;
	HBITMAP m_OldBitMap2;
	BITMAP m_bit2;
public:
	virtual void Init(int x, int y, HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual void replay(int x, int y);
};


class Elephant :public BackGround
{
public:
	virtual void Init(int x, int y, HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual void replay(int x, int y);
};

class Miter :public BackGround
{
private:
	char m_charMiter[128];
	int m_imitercount;
public:
	virtual void Init(int x, int y, HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual void replay(int x, int y);
	inline int miter()
	{
		return m_imitercount;
	}
};


class EndBox :public BackGround
{
public:
	virtual void Init(int x, int y, HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual void replay(int x, int y);
	inline RECT Endlocation()
	{
		return m_rect;
	}
};
