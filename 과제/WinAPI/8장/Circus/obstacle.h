#pragma once
#include"mecro.h"

class impediments
{
protected:
	HDC m_hBackBuffer[2];
	HBITMAP m_BitMap[2];
	HBITMAP m_OldBitMap[2];
	BITMAP m_bit[2];
	SIZE m_size[2];
	RECT m_rect[2];
	fire_State m_efire;
	bool m_bScorecheck;
	int m_iScore;
	int speed;

public:
	virtual void Init(int x, int y ,HDC _m_hBuffer) = 0;
	virtual void Render(HDC _m_hBuffer) = 0;
	virtual void Update(Direction direction, float time) {};
	virtual int Score(int player_x, State state) = 0;
	virtual void replay(int x,int y) = 0;
};

class jar :public impediments
{
public:
	jar();
	virtual void Init(int x, int y,HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual int Score(int player_x, State state);
	virtual void replay(int x, int y);
	inline RECT jarlocation()
	{
		return m_rect[0];
	}
	~jar();
};

class LeftFirering :public impediments
{
private:
	RECT m_crash;
public:
	LeftFirering();
	virtual void Init(int x,int y,HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual int Score(int player_x, State state);
	virtual void replay(int x, int y);
	inline RECT ringlocation()
	{
		return m_crash;
	}
	~LeftFirering();
};

class RightFirering :public impediments
{
private:
	RECT m_crash;
	int m_iRandomMoneyring;
public:
	RightFirering();
	virtual void Init(int x, int y, HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual int Score(int player_x, State state) {return 0;};
	virtual void replay(int x, int y);
	virtual void RandomCountReset(int n);
	inline RECT ringlocation()
	{
		return m_crash;
	}
	inline int randommoneyring()
	{
		return m_iRandomMoneyring;
	}
	~RightFirering();
};

class MoneyFirering :public impediments //충돌범위설정
{
private:
	RECT m_crash;
	bool m_brandem;
public:
	MoneyFirering();
	virtual void Init(int x, int y,HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual int Score(int player_x, State state) {return 0;};
	virtual int moneyScore();
	virtual void replay(int x, int y);
	~MoneyFirering();
	inline RECT ringlocation()
	{
		return m_crash;
	}
	inline bool ringcheck()
	{
		return m_brandem;
	}
	inline RECT money()
	{
		return m_rect[0];
	}
};

class MoneyrightFirering :public impediments
{
private:
	RECT m_crash;
public:
	MoneyrightFirering();
	virtual void Init(int x,int y,HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual int Score(int player_x, State state) {return 0;};
	virtual void replay(int x, int y);
	~MoneyrightFirering();
	inline RECT ringlocation()
	{
		return m_crash;
	}
};

class MoneyleftFirering :public impediments
{
private:
	RECT m_crash;
public:
	MoneyleftFirering();
	virtual void Init(int x, int y,HDC _m_hBuffer);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(Direction direction, float time);
	virtual int Score(int player_x, State state);
	virtual void replay(int x, int y);
	~MoneyleftFirering();
	inline RECT ringlocation()
	{
		return m_crash;
	}
};