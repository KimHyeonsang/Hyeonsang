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

	RECT m_Charactor_rt;
	int m_count;
	fire_State m_efire;
	bool m_bScorecheck;
	int m_iScore;
public:
	virtual void Init(HDC _m_hBuffer,RECT player_rt) = 0;
	virtual void Render(HDC _m_hBuffer) = 0;
	virtual void Update() {};
	virtual int Score(int player_x) = 0;
	virtual void replay() = 0;
};

class jar :public impediments
{
public:
	jar();
	virtual void Init(HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update(RECT rt);
	virtual int Score(int player_x);
	virtual void replay();
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
	virtual void Init(HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update();
	virtual int Score(int player_x);
	virtual void replay();
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
public:
	RightFirering();
	virtual void Init(HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update();
	virtual int Score(int player_x) {return 0;};
	virtual void replay();
	inline RECT ringlocation()
	{
		return m_crash;
	}
	~RightFirering();
};

class MoneyFirering :public impediments //충돌범위설정
{
private:
	RECT m_crash;
public:
	MoneyFirering();
	virtual void Init(HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update();
	virtual int Score(int player_x) {return 0;};
	virtual int moneyScore();
	virtual void replay();
	~MoneyFirering();
	inline RECT ringlocation()
	{
		return m_crash;
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
	virtual void Init(HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update();
	virtual int Score(int player_x) {return 0;}; 
	virtual void replay();
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
	virtual void Init(HDC _m_hBuffer, RECT player_rt);
	virtual void Render(HDC _m_hBuffer);
	virtual void Update();
	virtual int Score(int player_x);
	virtual void replay();
	~MoneyleftFirering();
	inline RECT ringlocation()
	{
		return m_crash;
	}
};