#include "Interface.h"


Interface::Interface()
{
}
void Interface::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}
void Interface::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void Interface::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void Interface::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}
void Interface::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "¦£";
			for (int x = 1; x < Width - 1; x++)
				cout << "¦¡";
			cout << "¦¤";
		}
		else if (y == Height - 1)
		{
			cout << "¦¦";
			for (int x = 1; x < Width - 1; x++)
				cout << "¦¡";
			cout << "¦¥";
		}
		else
		{
			cout << "¦¢";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "¦¢";
		}
	}
	return;
}
void Interface::BoxErase(int Width, int Height)
{
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}
int Interface::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	Setcolor(RED, DARKGRAY);
	DrawPoint("¢¹", x, y);
	ORIGINAL
		while (1)
		{
			switch (getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					Setcolor(DARKGRAY, DARKGRAY);
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					Setcolor(DARKGRAY, DARKGRAY);
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				return Select;
			}
			Setcolor(RED, DARKGRAY);
			DrawPoint("¢¹", x, y);
			ORIGINAL
		}
}
Interface::~Interface()
{
}
