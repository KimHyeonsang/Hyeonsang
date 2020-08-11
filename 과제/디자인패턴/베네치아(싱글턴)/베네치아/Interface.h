#pragma once
#include"macro.h"  //배경그림관리
#define UP 'w'
#define DOWN 's'
#define ENTER 13


class Interface
{
public:
	Interface();
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void BoxErase(int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	inline void Setcolor(int forground, int background)
	{
		int code = forground + background * 16;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
	}
	~Interface();
};

