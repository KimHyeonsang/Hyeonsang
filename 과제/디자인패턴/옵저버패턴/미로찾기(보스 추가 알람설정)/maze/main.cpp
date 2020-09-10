#include"maze.h"
#include"MapDraw.h"


void main()
{
	maze* Maze;
	MapDraw map;
	int y = HEIGHT * 0.4f;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d",WIDTH + 6, HEIGHT * 2);
	system(buf);
	while (1)
	{
		system("cls");
		Maze = new maze();
		int line = 0;
		map.DrawMidText("���ӽ���", WIDTH, y + line++ * 3);
		map.DrawMidText("���� �˶� ����", WIDTH, y + line++ * 3);
		map.DrawMidText("����", WIDTH, y + line++ * 3);
		switch (map.MenuSelectCursor(3, 3, WIDTH *0.2f, y))
		{
		case 1:
			Maze->Game();
			Maze->replay();
			break;
		case 2:
			Maze->alarm();
			break;
		case 3:
			return;
		}
	}
}