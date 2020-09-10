#include"maze.h"
#include"mecro.h"
#include"Alarm.h"
#include"MapDraw.h"

maze::maze()
{
	for (int i = 0; i < 15; i++)
	{
		for (int i = 0; i < WIDTH; i++)
			arr.push_back(0);
		map.push_back(arr);
		arr.clear();
	};
	LastObjectIndex = NULL;
	m_bGameClear = false;
	for (int i = 0; i < POTAL_MAX; i++)
	{
		arr.push_back(i);
		Entry_Potal.push_back(arr);//포탈입구
		Exit_Potal.push_back(arr);//포탈출구
		arr.clear();
	};
	for (int i = 0; i < ITEM_MAX; i++)
	{
		arr.push_back(i);
		button.push_back(arr);//포탈입구
		door.push_back(arr);//포탈출구
		arr.clear();
	};
	start = clock();
	Golem = new BossDragon();
	player1 = new Player("아랑");
	srand(time(0));
	m_bBoss = true;
}
void maze::MapDraw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
				cout<<"■";
		//	else if (map[y][x] == WALL2)
		//		cout << "■";
			else if (map[y][x] == NULL)
				cout << "  ";
			else if (map[y][x] >= TRAP && map[y][x] <= TRAP + TRAP_NUMBER)
				cout << "  ";
			else if (map[y][x] >= TRAP2 && map[y][x] <= TRAP2 + TRAP_NUMBER)
				cout << "  ";
			else if (map[y][x] == END_GAME)
				cout << "  ";
			else if (map[y][x] == PLAYER)
			{
				RED
					cout << "♬";
				ORIGINAL
			}
			else if (map[y][x] == BOSS)
			{
				if (clock() - start >= 10000)
				{
					PLUM
						cout << "♥";
					ORIGINAL
				}
				else
					cout << "  ";
			}
			else if (map[y][x] >= EXIT_START && map[y][x] <= EXIT_START + POTAL_MAX)
			{
				YELLOW
					printf("△");
				ORIGINAL
			}
			else if (map[y][x] >= DOOR && map[y][x] <= DOOR + ITEM_MAX)
			{
				GOLD
					printf("■");
				ORIGINAL
			}
			else if (map[y][x] >= BUTTON && map[y][x] <= BUTTON + ITEM_MAX)
			{
				GREEN
					printf("★");
				ORIGINAL
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] <= ENTRY_START + POTAL_MAX)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
		}
	}
	cout << "출구 : ";
	YELLOW
		cout << "△";
	ORIGINAL
		cout << "입구";
	BLUE
		cout << "◎" << endl;
	ORIGINAL
		cout << "아이템";
	GOLD
		cout << "★";
	ORIGINAL
		cout << "문:";
	GOLD
		cout << "■" << endl;
	ORIGINAL
		if (clock() - start >= 5000 && m_bBoss)
		{
			Golem->SpawnBoss();
			m_bBoss = false;
		}
}
void maze::Map()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		if (i == 0 || i == HEIGHT - 1 || i == 7)
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
				if(j == 7)
					map[i][j] = WALL;
			}
		}
	}
	map[1][1] = PLAYER;
	map[2][2] = WALL;
	map[3][2] = WALL;
	map[8][8] = ENTRY_START;
	map[1][6] = ENTRY_START + 1;
	map[8][1] = ENTRY_START + 2;
	map[1][12] = ENTRY_START + 3;
	
	map[13][8] = EXIT_START;
	map[8][6] = EXIT_START + 1;
	map[6][8] = EXIT_START + 2;
	map[8][12] = EXIT_START + 3;

	map[1][2] = DOOR;
	map[6][2] = DOOR + 1;
	map[1][4] = BUTTON;
	map[9][4] = BUTTON + 1;
	map[12][14] = END_GAME;	
}
void maze::mapinit()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == PLAYER)
			{
				character.push_back(x);
				character.push_back(y);
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] <= ENTRY_START + POTAL_MAX)//포탈위치
			{
				Entry_Potal[map[y][x] - ENTRY_START].push_back(x);
				Entry_Potal[map[y][x] - ENTRY_START].push_back(y);
			}
			else if (map[y][x] >= EXIT_START && map[y][x] <= EXIT_START + POTAL_MAX)//나오는포탈
			{
				Exit_Potal[map[y][x] - EXIT_START].push_back(x);
				Exit_Potal[map[y][x] - EXIT_START].push_back(y);
			}
			else if (map[y][x] >= BUTTON && map[y][x] <= BUTTON + ITEM_MAX)//스위치
			{
				button[map[y][x] - BUTTON].push_back(x);
				button[map[y][x] - BUTTON].push_back(y);
			}
			else if (map[y][x] >= DOOR && map[y][x] <= DOOR + ITEM_MAX)//문
			{
				door[map[y][x] - DOOR].push_back(x);
				door[map[y][x] - DOOR].push_back(y);
			}
			else if (map[y][x] == BOSS)
			{
				Boss.push_back(x);
				Boss.push_back(y);
			}
			//else if (map[y][x] >= TRAP && map[y][x] <= TRAP + TRAP_NUMBER) //함정
			//{
			//	trap[map[y][x] - TRAP][X] = x;
			//	trap[map[y][x] - TRAP][Y] = y;
			//}
			//else if (map[y][x] >= TRAP2 && map[y][x] <= TRAP2 + TRAP_NUMBER)
			//{
			//	trap_open[map[y][x] - TRAP2][X] = x;
			//	trap_open[map[y][x] - TRAP2][Y] = y;
			//}
		}
	}
}

void maze::Move()
{
	char ch;
	ch = getch();
	system("cls");
	map[character[1]][character[0]] = LastObjectIndex;

	switch (ch)
	{
	case LEFT:
		if (map[character[1]][character[0] - 1] != WALL && !(map[character[1]][character[0] - 1] >= DOOR && map[character[1]][character[0] - 1] <= DOOR + ITEM_MAX)
			&& map[character[1]][character[0] - 1] != WALL2)
			character[0]--;
		break;
	case RIGHT:
		if (map[character[1]][character[0] + 1] != WALL && !(map[character[1]][character[0] + 1] >= DOOR && map[character[1]][character[0] + 1] <= DOOR + ITEM_MAX)
			&& map[character[1]][character[0] + 1] != WALL2)
			character[0]++;
		break;
	case UP:
		if (map[character[1] - 1][character[0]] != WALL && !(map[character[1] - 1][character[0]] >= DOOR && map[character[1] - 1][character[0]] <= DOOR + ITEM_MAX)
			&& map[character[1] - 1][character[0]] != WALL2)
			character[1]--;
		break;
	case DOWN:
		if (map[character[1] + 1][character[0]] != WALL && !(map[character[1] + 1][character[0]] >= DOOR && map[character[1] + 1][character[0]] <= DOOR + ITEM_MAX)
			&& map[character[1] + 1][character[0]] != WALL2)
			character[1]++;
		break;
	/*case SPACE:
		if (BoomCount > 0)
		{
			if (map[character[Y]][character[X] - 1] != WALL2 && map[character[Y]][character[X] + 1] != WALL2 &&
				map[character[Y] - 1][character[X]] != WALL2 && map[character[Y] + 1][character[X]] != WALL2)
			{
				map[character[Y] + 1][character[X]] = 0;
				map[character[Y] - 1][character[X]] = 0;
				map[character[Y]][character[X] + 1] = 0;
				map[character[Y]][character[X] - 1] = 0;
				BoomCount--;
			}

		}
		break;	*/
	case ESC:
		replay();
		break;

	}
	MoveCheck();
	End_Game();
	LastObjectIndex = map[character[1]][character[0]];
	map[character[1]][character[0]] = PLAYER;
}
void maze::MoveCheck()
{
	int index = map[character[1]][character[0]];
	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)//포탈 이동
	{
		character.clear();
		character.push_back(Exit_Potal[index - ENTRY_START][1]);
		character.push_back(Exit_Potal[index - ENTRY_START][2]);
	}
	else if (index >= BUTTON && index < BUTTON + POTAL_MAX)//아이템을 먹으면
	{
		map[button[index - BUTTON][2]][button[index - BUTTON][1]] = NULL;
		map[door[index - BUTTON][2]][door[index - BUTTON][1]] = NULL;
	}
	else if (index == BOSS) //보스
	{
		m_bGameClear = true;
	}
	//else if (index == ITEM2) //벽뿌 아이템
	//{
	//	LastObjectIndex = NULL;
	//	map[character[Y]][character[X]] = NULL;
	//	BoomCount++;
	//}
	//else 
	if (index == PLAYER)
	{
		LastObjectIndex = NULL;
		map[character[1]][character[0]] = NULL;
	}

}
void maze::End_Game()  //끝내기
{
	if (map[character[1]][character[0]] == END_GAME)
		m_bGameClear = true;
}

void maze::replay()//뒤로가기
{
	m_bGameClear = true;
}
void maze::respown()
{
	while (1)
	{
		m_iBoss_x = rand() % 15;
		m_iBoss_y = rand() % 15;
		if (map[m_iBoss_y][m_iBoss_x] == 0)
		{
			map[m_iBoss_y][m_iBoss_x] = BOSS;
			break;
		}
	}
}
void maze::Game()
{
	system("cls");
	Map();
	mapinit();
	player1->SetBossAlarm(Golem);
	while (!m_bGameClear)
	{
		MapDraw();
		Move();
		if (clock() - start >= 5000 && m_bBoss)
		{
			respown();
			
		}
	}
}
void maze::alarm()
{
	system("cls");
	int y = HEIGHT * 0.4f;
	int line = 0;
	mapdraw.DrawMidText("보스 알람 ON", WIDTH, y + line++ * 3);
	mapdraw.DrawMidText("보스 알람 OFF", WIDTH, y + line++ * 3);
	switch (mapdraw.MenuSelectCursor(2, 3, WIDTH *0.2f, y))
	{
	case 1:
		player1->SetBossAlarm(Golem);
		break;
	case 2:
		player1->SetBossAlarm(Golem,false);
		break;
	}
}
maze::~maze()
{
	map.clear();
}