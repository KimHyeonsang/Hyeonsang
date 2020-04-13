#pragma once
#include"macro.h"
#include"Mapdraw.h"
typedef struct PlayerMove
{
	int x;
	int y;
	bool check;
}playerMove;
//위치 좌표 움직임
enum KEY
{
	KEY_UP = 119,
	KEY_DOWN = 115,
	KEY_LEFT = 97,
	KEY_RIGHT = 100,
	KEY_ENTER = 13
};

class Player
{
private:
	Mapdraw map;
	int m_ix;
	int m_iy;
	string shap;
	bool m_bmovecharacterCheck;
	bool m_bmovecheck;
	playerMove* *playermove;
	int m_icount;
	bool m_bcountcheck;
public:
	Player();
	void MovePlayer(Mapdraw* mapdraw);
	void playKey(Mapdraw* mapdraw);
	void beforecharaterdraw(Mapdraw* mapdraw, int x, int y);
	void PlayerSet();
	bool Victory(int boomnumber);
	~Player();
};