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
	player = 1,
	TRAP,
	TRAP_NUMBER,
	TRAP2,
	WALL,
	WALL2
};

void MapDraw(vector<vector<int>> map)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
				printf("■");
			else if (map[y][x] == WALL2)
				printf("■");
			else if (map[y][x] == NULL)
				printf("  ");
			else if (map[y][x] >= TRAP && map[y][x] <= TRAP + TRAP_NUMBER)
				printf("  ");
			else if (map[y][x] >= TRAP2 && map[y][x] <= TRAP2 + TRAP_NUMBER)
				printf("  ");
		}
		printf("\n");
	}
	printf("출구:");
	YELLOW
		printf("△");
	ORIGINAL
		printf("입구");
	BLUE
		printf("◎\n");
	ORIGINAL
		printf("아이템");
	GOLD
		printf("★");
	ORIGINAL
		printf("문:");
	GOLD
		printf("■");
	ORIGINAL
		printf("   함정 조심!!!!");
	GREEN
		printf("   ♨");
	ORIGINAL
		printf("아이템 갯수:%d", 0);

}

void main()
{
	/*vector<int> arr(5, 0);
	vector<int> arr2(5, 0);
	vector<int> arr3(5, 0);
	vector<int> arr4(5, 0);
	vector<int> arr5(5, 0);*/
	vector<vector<int> > arr(5, vector<int>(5, 0));
	for (int i = 0; i < 5; i++)
	{
		if (i == 0 || i == 4)
		{
			for (int j = 0; j < 5; j++)
			{
				arr[i][j] = WALL;
			}
		}
		else
		{
			for (int j = 0; j < 5; j++)
			{
				if (j == 0 || j == 4)
					arr[i][j] = WALL;
			}
		}
	}
	MapDraw(arr);
}