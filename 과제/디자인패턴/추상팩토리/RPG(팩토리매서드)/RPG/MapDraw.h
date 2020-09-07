#pragma once
#include"Mecro.h"
#define UP 'w'
#define DOWN 's'
#define ENTER 13
class MapDraw
{
public:
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void BoxErase(int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
	int MenuSelectCursor(int Menulen, int Addcol, int x, int y);
	MapDraw();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	virtual ~MapDraw();
	virtual void Render() = 0;
};

class JobMap :public MapDraw
{
public:
	JobMap();
	virtual ~JobMap();
	virtual void Render();
};

class NewGameMenu :public MapDraw
{
public:
	NewGameMenu();
	virtual ~NewGameMenu();
	virtual void Render();
};

class firstmenu :public MapDraw
{
public:
	firstmenu();
	virtual ~firstmenu();
	virtual void Render();
};

class Mainmenu :public MapDraw
{
public:
	Mainmenu();
	virtual ~Mainmenu();
	virtual void Render();
};

class danganmenu :public MapDraw
{
public:
	danganmenu();
	virtual ~danganmenu();
	virtual void Render();
};

class shopMenu :public MapDraw
{
public:
	shopMenu();
	virtual ~shopMenu();
	virtual void Render();
};