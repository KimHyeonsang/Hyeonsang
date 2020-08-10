#include<iostream>
#include<vector>
#include<conio.h>
#include<Windows.h>
using namespace std;

/////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
///////////////////////////////////////////////////////////
#define HEIGHT 5
#define WIDTH 5


enum Map
{
	PLAYER = 1,
	ITEM_MAX,
	TRAP_NUMBER,
	TRAP2,
	WALL = 6,
	WALL2,
	TRAP = 40,
	DOOR =50,
	ENTRY_START = 60,
	EXIT = 70
};

void MapDraw(vector<vector<int>> map)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
				cout<<"■";
			else if (map[y][x] == WALL2)
				cout << "■";
			else if (map[y][x] == NULL)
				cout << "  ";
			else if (map[y][x] >= TRAP && map[y][x] <= TRAP + TRAP_NUMBER)
				cout << "  ";
			else if (map[y][x] >= TRAP2 && map[y][x] <= TRAP2 + TRAP_NUMBER)
				cout << "  ";
			else if (map[y][x] == PLAYER)
			{
				RED
					cout << "♬";
				ORIGINAL
			}
			else if (map[y][x] == EXIT)
			{
				YELLOW
					printf("△");
				ORIGINAL
			}
			else if (map[y][x] == DOOR)
			{
				GOLD
					printf("■");
				ORIGINAL
			}
			else if (map[y][x] == ENTRY_START)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
		}
		cout << endl;
	}
	cout << "출구 : ";
	YELLOW
		cout << "△";
	ORIGINAL
		cout << "입구";
	BLUE
		cout << "◎\n";
	ORIGINAL
		cout << "아이템";
	GOLD
		cout << "★";
	ORIGINAL
		cout << "문:";
	GOLD
		cout << "■";
	ORIGINAL

}
void Map(vector<vector<int>> map)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		if (i == 0 || i == HEIGHT - 1)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				map[i][j] = WALL;
			}
		}
		else
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (j == 0 || j == WIDTH - 1)
					map[i][j] = WALL;
			}
		}
	}
	map[1][1] = PLAYER;
	map[2][2] = WALL;
	map[3][2] = WALL;
	map[3][1] = ENTRY_START;
	map[1][2] = DOOR;
	map[1][3] = EXIT;
	MapDraw(map);
}


void main()
{
	vector<vector<int> > arr(HEIGHT, vector<int>(WIDTH, 0));
	Map(arr);
}