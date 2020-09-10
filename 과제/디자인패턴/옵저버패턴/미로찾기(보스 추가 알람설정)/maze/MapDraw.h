#pragma once
#include"mecro.h"

#define ENTER 13

class MapDraw
{
public:
	MapDraw();
	~MapDraw();
	int MenuSelectCursor(int Menulen, int Addcol, int x, int y);
	void DrawMidText(string str, int x, int y);
	void DrawPoint(string str, int x, int y);
	void ErasePoint(int x, int y);
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};

