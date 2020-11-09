#pragma once
#include"define.h"
//그리기 저장하기 움직이기

class chess
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;

public:
	chess();
	void Init(HWND hWnd,int x, int y,LPCWSTR FileName);
	void Draw(HDC hdc);
	virtual bool Move(int Team,POINT pt, vector<chess*>*enemy) = 0; //움직이는데 가는길에 장애물(같은팀,상대팀)이 있으면 이동불가
	virtual bool MoveCheck(POINT pt,RECT rt) = 0;
	virtual bool checkmate(RECT EnemyKing_rt, RECT Team_rt) = 0;
	virtual bool checkmateCheck(RECT EnemyKing_rt) = 0;
	inline int size_x() { return m_size.cx;	}
	inline int size_y()	{ return m_size.cy;	}
	inline int Rank()	{ return m_iRank;	}
	inline RECT Rt()	{ return Rect;	}
	inline int Rt_x()	{ return Rect.left;	}
	inline int Rt_y()	{ return Rect.top;	}
	~chess();
protected:
	SIZE m_size;
	RECT Rect;
	int m_iRank;	
	vector<chess*>::iterator enemy_iter;
	chess* m_Enemy;
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
	bool Move(int Team, POINT pt, vector<chess*>*enemy);
	bool MoveCheck(POINT pt, RECT rt);
	bool checkmate(RECT EnemyKing_rt, RECT Team_rt);
	bool checkmateCheck(RECT EnemyKing_rt);
	void promotion();
};

class King :public chess
{
public:
	King();
	bool Move(int Team, POINT pt, vector<chess*>*enemy);
	bool MoveCheck(POINT pt, RECT rt);
	bool checkmate(RECT EnemyKing_rt, RECT Team_rt);
	bool checkmateCheck(RECT EnemyKing_rt);
};

class Knight :public chess
{
public:
	Knight();
	bool Move(int Team, POINT pt, vector<chess*>*enemy);
	bool MoveCheck(POINT pt, RECT rt);
	bool checkmate(RECT EnemyKing_rt, RECT Team_rt);
	bool checkmateCheck(RECT EnemyKing_rt);
};

class Rook :public chess
{
public:
	Rook();
	bool Move(int Team, POINT pt, vector<chess*>*enemy);
	bool MoveCheck(POINT pt, RECT rt);
	bool checkmate(RECT EnemyKing_rt, RECT Team_rt);
	bool checkmateCheck(RECT EnemyKing_rt);
};

class Queen :public chess
{
public:
	Queen();
	bool Move(int Team, POINT pt, vector<chess*>*enemy);
	bool MoveCheck(POINT pt, RECT rt);
	bool checkmate(RECT EnemyKing_rt, RECT Team_rt);
	bool checkmateCheck(RECT EnemyKing_rt);
};

class Bishop :public chess
{
public:
	Bishop();
	bool Move(int Team, POINT pt, vector<chess*>*enemy);
	bool MoveCheck(POINT pt, RECT rt);
	bool checkmate(RECT EnemyKing_rt, RECT Team_rt);
	bool checkmateCheck(RECT EnemyKing_rt);
};
