#include"Mecro.h"
#include"MapDraw.h"
#include"GameManager.h"

void main()
{
	MapDraw map;
	srand(time(NULL));
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", WIDTH + 1, HEIGHT * 2);
	system(buf);
	
	while (1)
	{
		system("cls");
		BLUE
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			map.DrawMidText("☆★ DonGeonRPG ★☆", WIDTH, HEIGHT* 0.4);
		map.DrawMidText("New Game", WIDTH, HEIGHT* 0.4 + 3);
		map.DrawMidText("Load Game", WIDTH, HEIGHT* 0.4 + 6);
		map.DrawMidText("Game Exit", WIDTH, HEIGHT* 0.4 + 9);
		switch (map.MenuSelectCursor(3, 3, (WIDTH - strlen("Game Exit") / 2 - 3) / 2, HEIGHT* 0.4 + 3))
		{
		case 1: //만약 새로운 게임이면 기본능력치 부여
			GameManager::GetInstance()->NewGame();
			break;
		case 2:
			GameManager::GetInstance()->Loadfile(true);
			GameManager::GetInstance()->LoadSave();
			if (GameManager::GetInstance()->Load() == false)
				GameManager::GetInstance()->NewGame();
			break;
		case 3:
			return;
		}
	}
}