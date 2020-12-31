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
	RECT m_Charactor_rt;
	int m_icount;
	State m_state;
public:
	virtual void Init(int x,int y,HDC _m_hBuffer, RECT player_rt) = 0;
	virtual void Render(HDC _m_hBuffer) =0;
	virtual void Update(RECT rt) = 0;
	virtual void replay(int x,int y, RECT player_rt) = 0;
	void End();
};
class Ground:public BackGround
{
public:
	virtual void Init(int x, int y,HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(RECT rt) {};
	virtual void replay(int x, int y, RECT player_rt) {};
};
class crowd:public BackGround
{
private:
	RECT m_player;
	HDC m_hBackBuffer2;
	HBITMAP m_BitMap2;
	HBITMAP m_OldBitMap2;
public:
	virtual void Init(int x, int y, HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(RECT rt);
	virtual void replay(int x, int y, RECT player_rt);
};


class Elephant :public BackGround
{
public:
	virtual void Init(int x, int y, HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(RECT rt);
	virtual void replay(int x, int y, RECT player_rt);
};

class Miter :public BackGround
{
private:
	char m_charMiter[128];
	int m_imitercount;
	RECT m_player;
public:
	virtual void Init(int x, int y, HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(RECT rt);
	virtual void replay(int x, int y, RECT player_rt);
	inline int miter()
	{
		return m_imitercount;
	}
};


class EndBox :public BackGround
{
private:
	RECT m_player;
public:
	virtual void Init(int x, int y, HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(RECT rt);
	virtual void replay(int x, int y, RECT player_rt) {};
	inline RECT Endlocation()
	{
		return m_rect;
	}
};