#pragma once
#include"define.h"
//그리기 저장하기 움직이기

class chess
{
private:
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
public:
	chess();
	void Init(HWND hWnd,int x, int y,LPCWSTR FileName);
	void Draw(HDC hdc);
	virtual void Move(int Team,POINT pt) = 0; //움직이는데 가는길에 장애물(같은팀,상대팀)이 있으면 이동불가
	virtual bool MoveCheck(RECT POINT_RT,RECT rt,int Team) = 0;
	bool phawnAtack(RECT POINT_RT, RECT rt, int Team);

	inline int size_x() { return m_size.cx;	}
	inline int size_y()	{ return m_size.cy;	}
	inline int Rank()	{ return m_iRank;	}
	inline RECT Rt()	{ return Rect;	}
	inline int Rt_x()	{ return Rect.left;	}
	inline int Rt_y()	{ return Rect.top;	}
	~chess();
protected:
	HDC MemDC;
	SIZE m_size;
	RECT Rect;
	int m_iRank;
};

class Phawn :public chess
{
private:
	bool m_bfirstmove;
public:
	Phawn();
	inline bool firstmove()
	{
		return m_bfirstmove;
	}
	void Move(int Team, POINT pt);
	bool MoveCheck(RECT POINT_RT, RECT rt, int Team);
	void promotion();
};

class King :public chess
{
public:
	King();
	void Move(int Team, POINT pt);
	bool MoveCheck(RECT POINT_RT, RECT rt, int Team);
};

class Knight :public chess
{
public:
	Knight();
	void Move(int Team, POINT pt);
	bool MoveCheck(RECT POINT_RT, RECT rt, int Team);
};

class Rook :public chess
{
public:
	Rook();
	void Move(int Team, POINT pt);
	bool MoveCheck(RECT POINT_RT, RECT rt, int Team);
};

class Queen :public chess
{
public:
	Queen();
	void Move(int Team, POINT pt);
	bool MoveCheck(RECT POINT_RT, RECT rt, int Team);
};

class Bishop :public chess
{
public:
	Bishop();
	void Move(int Team, POINT pt);
	bool MoveCheck(RECT POINT_RT, RECT rt, int Team);
};
