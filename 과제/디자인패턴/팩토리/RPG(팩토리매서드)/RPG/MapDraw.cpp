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
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else if (y == Height - 1)
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "��";
		}
	}
	return;
}
int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		DrawPoint("��", x, y);
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
				DrawPoint("��", x, y);
			ORIGINAL
		}
}
MapDraw::~MapDraw()
{
}
////////////////////////////////////////////////////////////////
//�����޴�
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
		DrawMidText("������ ���ϼ���(�����ϰ� ���ϼ���.)  ", WIDTH, y + line++ * 3);
	DrawMidText("1. ����(��,�ظ�)  ", WIDTH, y + line++ * 3);
	DrawMidText("2. ����(�ܰ�) ", WIDTH, y + line++ * 3);
	DrawMidText("3. ������(�ϵ�) ", WIDTH, y + line++ * 3);
	DrawMidText("4. �ü�(Ȱ,��)  ", WIDTH, y + line++ * 3);
}
/////////////////////////////////////////////////////////////////
//������
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
	TextDraw("�١� Menu �ڡ�", WIDTH*0.75f, HEIGHT*0.3f);
	TextDraw("Dongeon", WIDTH*0.88f, HEIGHT*0.38f);
	TextDraw("Player Info", WIDTH*0.85f, HEIGHT*0.46f);
	TextDraw("Monster Info", WIDTH*0.8f, HEIGHT*0.5f);
	TextDraw("Weapon Shop", WIDTH*0.85f, HEIGHT*0.58f);
	TextDraw("Inventory", WIDTH*0.85f, HEIGHT*0.64f);
	TextDraw("Save", WIDTH*0.88f, HEIGHT*0.72f);
	TextDraw("Exit", WIDTH*0.88f, HEIGHT*0.78f);
}
///////////////////////////////////////////////////////////////////
// ù��° �޴�
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
	DrawMidText("�١� DonGeonRPG �ڡ�", WIDTH, HEIGHT* 0.4);
	DrawMidText("New Game", WIDTH, HEIGHT* 0.4 + 3);
	DrawMidText("Load Game", WIDTH, HEIGHT* 0.4 + 6);
	DrawMidText("Game Exit", WIDTH, HEIGHT* 0.4 + 9);
}

/////////////////////////////////////////////////////////////////
//���� �޴�
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
	TextDraw("�١� Menu �ڡ�", WIDTH*0.75f, HEIGHT*0.3f);
	TextDraw("Dongeon", WIDTH*0.88f, HEIGHT*0.38f);
	TextDraw("Player Info", WIDTH*0.85f, HEIGHT*0.46f);
	TextDraw("Monster Info", WIDTH*0.8f, HEIGHT*0.5f);
	TextDraw("Weapon Shop", WIDTH*0.85f, HEIGHT*0.58f);
	TextDraw("Inventory", WIDTH*0.85f, HEIGHT*0.64f);
	TextDraw("Save", WIDTH*0.88f, HEIGHT*0.72f);
	TextDraw("Exit", WIDTH*0.88f, HEIGHT*0.78f);
}
///////////////////////////////////////////////////////////////////
//���� �Ŵ�

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
		TextDraw("====���� �Ա�====", WIDTH*0.75f, HEIGHT*0.2f);
	TextDraw("1������ : [���]", WIDTH*0.78f, HEIGHT*0.38f);
	TextDraw("2������ : [��ũ]", WIDTH*0.8f, HEIGHT*0.46f);
	TextDraw("3������ : [�����ΰ�]", WIDTH*0.75f, HEIGHT*0.5f);
	TextDraw("4������ : [�����]", WIDTH*0.8f, HEIGHT*0.58f);
	TextDraw("5������ : [���̷����ó]", WIDTH*0.72f, HEIGHT*0.64f);
	TextDraw("6������ : [��ġ]", WIDTH*0.8f, HEIGHT*0.72f);
	TextDraw("���ư���", WIDTH*0.88f, HEIGHT*0.78f);
}

///////////////////////////////////////////////////////////////////////////
//���⼥�޴�
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
	TextDraw("�� �� S H O P �� ��", WIDTH * 0.7f, HEIGHT*0.3f);
	TextDraw("Dagger", WIDTH * 0.8f, HEIGHT*0.38f);
	TextDraw("Gun", WIDTH*0.85f, HEIGHT*0.46f);
	TextDraw("Sword", WIDTH * 0.8f, HEIGHT*0.5f);
	TextDraw("Wand", WIDTH * 0.8f, HEIGHT*0.58f);
	TextDraw("Bow", WIDTH*0.85f, HEIGHT*0.65f);
	TextDraw("Hammer", WIDTH * 0.8f, HEIGHT*0.7f);
	TextDraw("���ư���", WIDTH*0.8f, HEIGHT*0.78f);
}