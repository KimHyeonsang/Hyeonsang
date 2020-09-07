#include "MapDraw.h"



MapDraw::MapDraw()
{
}
void MapDraw::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}
void MapDraw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}
void MapDraw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void MapDraw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void MapDraw::BoxErase(int Width, int Height)
{
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}
void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "┌";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┐";
		}
		else if (y == Height - 1)
		{
			cout << "└";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┘";
		}
		else
		{
			cout << "│";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "│";
		}
	}
	return;
}
int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		DrawPoint("▷", x, y);
	ORIGINAL
		while (1)
		{
			switch (_getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				return Select;
			}
			RED
				DrawPoint("▷", x, y);
			ORIGINAL
		}
}
MapDraw::~MapDraw()
{
}
////////////////////////////////////////////////////////////////
//직업메뉴
JobMap::JobMap()
{
	
}

JobMap::~JobMap()
{
}

void JobMap::Render()
{
	system("cls");
	int line = 0;
	int y = HEIGHT * 0.2f;
	BLUE
		BoxDraw(0, 0, WIDTH * 2, HEIGHT);
	ORIGINAL
		DrawMidText("직업을 정하세요(신중하게 정하세요.)  ", WIDTH, y + line++ * 3);
	DrawMidText("1. 전사(검,해머)  ", WIDTH, y + line++ * 3);
	DrawMidText("2. 도적(단검) ", WIDTH, y + line++ * 3);
	DrawMidText("3. 마법사(완드) ", WIDTH, y + line++ * 3);
	DrawMidText("4. 궁수(활,총)  ", WIDTH, y + line++ * 3);
}
/////////////////////////////////////////////////////////////////
//새게임
NewGameMenu::NewGameMenu()
{

}

NewGameMenu::~NewGameMenu()
{
}

void NewGameMenu::Render()
{
	BLUE
		BoxDraw(0, 0, WIDTH * 2, HEIGHT);
	ORIGINAL
	TextDraw("☆★ Menu ★☆", WIDTH*0.75f, HEIGHT*0.3f);
	TextDraw("Dongeon", WIDTH*0.88f, HEIGHT*0.38f);
	TextDraw("Player Info", WIDTH*0.85f, HEIGHT*0.46f);
	TextDraw("Monster Info", WIDTH*0.8f, HEIGHT*0.5f);
	TextDraw("Weapon Shop", WIDTH*0.85f, HEIGHT*0.58f);
	TextDraw("Inventory", WIDTH*0.85f, HEIGHT*0.64f);
	TextDraw("Save", WIDTH*0.88f, HEIGHT*0.72f);
	TextDraw("Exit", WIDTH*0.88f, HEIGHT*0.78f);
}
///////////////////////////////////////////////////////////////////
// 첫번째 메뉴
firstmenu::firstmenu()
{

}

firstmenu::~firstmenu()
{
	
}

void firstmenu::Render()
{
	system("cls");
	BLUE
		BoxDraw(0, 0, WIDTH * 2 , HEIGHT);
	ORIGINAL
	DrawMidText("☆★ DonGeonRPG ★☆", WIDTH, HEIGHT* 0.4);
	DrawMidText("New Game", WIDTH, HEIGHT* 0.4 + 3);
	DrawMidText("Load Game", WIDTH, HEIGHT* 0.4 + 6);
	DrawMidText("Game Exit", WIDTH, HEIGHT* 0.4 + 9);
}

/////////////////////////////////////////////////////////////////
//메인 메뉴
Mainmenu::Mainmenu()
{

}

Mainmenu::~Mainmenu()
{
}

void Mainmenu::Render()
{
	system("cls");
	BLUE
		BoxDraw(0, 0, WIDTH * 2, HEIGHT);
	ORIGINAL
	TextDraw("☆★ Menu ★☆", WIDTH*0.75f, HEIGHT*0.3f);
	TextDraw("Dongeon", WIDTH*0.88f, HEIGHT*0.38f);
	TextDraw("Player Info", WIDTH*0.85f, HEIGHT*0.46f);
	TextDraw("Monster Info", WIDTH*0.8f, HEIGHT*0.5f);
	TextDraw("Weapon Shop", WIDTH*0.85f, HEIGHT*0.58f);
	TextDraw("Inventory", WIDTH*0.85f, HEIGHT*0.64f);
	TextDraw("Save", WIDTH*0.88f, HEIGHT*0.72f);
	TextDraw("Exit", WIDTH*0.88f, HEIGHT*0.78f);
}
///////////////////////////////////////////////////////////////////
//던전 매뉴

danganmenu::danganmenu()
{

}

danganmenu::~danganmenu()
{
}

void danganmenu::Render()
{
	system("cls");
	BLUE
		BoxDraw(0, 0, WIDTH * 2, HEIGHT);
	ORIGINAL
		TextDraw("====던전 입구====", WIDTH*0.75f, HEIGHT*0.2f);
	TextDraw("1층던전 : [고블린]", WIDTH*0.78f, HEIGHT*0.38f);
	TextDraw("2층던전 : [오크]", WIDTH*0.8f, HEIGHT*0.46f);
	TextDraw("3층던전 : [늑대인간]", WIDTH*0.75f, HEIGHT*0.5f);
	TextDraw("4층던전 : [오우거]", WIDTH*0.8f, HEIGHT*0.58f);
	TextDraw("5층던전 : [스켈레톤아처]", WIDTH*0.72f, HEIGHT*0.64f);
	TextDraw("6층던전 : [리치]", WIDTH*0.8f, HEIGHT*0.72f);
	TextDraw("돌아가기", WIDTH*0.88f, HEIGHT*0.78f);
}

///////////////////////////////////////////////////////////////////////////
//무기샵메뉴
shopMenu::shopMenu()
{

}

shopMenu::~shopMenu()
{
}

void shopMenu::Render()
{
	system("cls");
	BLUE
		BoxDraw(0, 0, WIDTH * 2, HEIGHT);
	ORIGINAL
	TextDraw("♧ ♣ S H O P ♣ ♧", WIDTH * 0.7f, HEIGHT*0.3f);
	TextDraw("Dagger", WIDTH * 0.8f, HEIGHT*0.38f);
	TextDraw("Gun", WIDTH*0.85f, HEIGHT*0.46f);
	TextDraw("Sword", WIDTH * 0.8f, HEIGHT*0.5f);
	TextDraw("Wand", WIDTH * 0.8f, HEIGHT*0.58f);
	TextDraw("Bow", WIDTH*0.85f, HEIGHT*0.65f);
	TextDraw("Hammer", WIDTH * 0.8f, HEIGHT*0.7f);
	TextDraw("돌아가기", WIDTH*0.8f, HEIGHT*0.78f);
}