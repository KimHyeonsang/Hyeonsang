#pragma once
#include"macro.h"
class Mapdraw
{
private:
	int m_imap[WIDTH][HEIGHT];
	int m_iboomCount;
	bool m_bGameOver;
public:
	void createOutBox();
	void mapdraw();
	void settingobject(string str, int& x, int y);
	void Createmine(int& x, int& y);
	void counttingBoom();
	void openBox(int player_x, int player_y);
	void beforelocation(int x, int y);
	void Restboard();
	void gotoxy(int x, int y)
	{
		COORD pos = { x,y };

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	}
	inline bool GameOver()
	{
		return m_bGameOver;
	}
	inline int number(int x,int y)
	{
		return m_imap[y][x];
	}
	Mapdraw();
	~Mapdraw();
};

