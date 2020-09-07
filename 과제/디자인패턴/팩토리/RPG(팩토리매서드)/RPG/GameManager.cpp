#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
	bLoad = true;
	bSave = false;
	bLoadfile = false;
	bDraw = false;
	bPlayerwin = false;
	bPlayerLose = false;
	batte = true;
	bRamdomeffect = false;
//	bweaponUse = false;
	bWeaponchange = false;
}

void GameManager::SelectJob()
{
	int Select;
	Select = map->MenuSelectCursor(4, 3, WIDTH * 0.25f, HEIGHT * 0.3f);
	player = player->SelectJob(Select);
	system("cls");
	int y = HEIGHT * 0.14f;
	BLUE
		map->BoxDraw(0, 0, WIDTH, HEIGHT);
	ORIGINAL
		string name;
	if (bLoad == true)
	{
		YELLOW
			map->TextDraw("Player 이름 입력 : ", WIDTH*0.65f, HEIGHT*0.5f);
		cin >> name;
		ORIGINAL
			player->SetName(name);
	}
}

void GameManager::LoadSave()
{
	bLoad = true;
	bSave = true;
	int select;
	char buf[256];
	char buf2[256];
	ifstream monsterload, playerLoad;
	int x = WIDTH * 0.5f;
	int y = HEIGHT * 0.2f;
	while (bLoad)
	{
		system("cls");
		BLUE
			map->BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			for (int i = 1; i < 11; i++)
			{
				map->gotoxy(x, y);
				sprintf(buf, "SaveMonster%d.txt", i);
				sprintf(buf2, "SavePlayer%d.txt", i);
				monsterload.open(buf);
				playerLoad.open(buf2);
				if (!monsterload && !playerLoad)
				{
					GREEN
						cout << i << "번 슬롯 : (파일 여부 : X)" << endl;
				}
				else
				{
					GREEN
						cout << i << "번 슬롯 : (파일 여부 : O)" << endl;
					monsterload.close();
					playerLoad.close();
				}
				y += 2;
			}
		map->gotoxy(x, y);
		cout << "11. 돌아가기" << endl;
		ORIGINAL
			switch (select = map->MenuSelectCursor(11, 2, WIDTH * 0.2f, HEIGHT*0.2f))
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				if (bLoadfile == true)
					Load(buf, select, buf2);
				if (bSave == true)
					Save(buf, select, buf2);
				x = WIDTH * 0.5f;
				y = HEIGHT * 0.2f;
				if (monsterload)
					return;
				break;
			case 11:
				return;
			default:
				break;
			}
	}
}

void GameManager::Playinfo()
{
	system("cls");
	YELLOW
		player->showplayer(WIDTH, HEIGHT*0.4f);
	ORIGINAL
		system("pause>null");
}

void GameManager::playerinveninfo()
{
	player->invenview(WIDTH, HEIGHT * 0.1f);
}

void GameManager::Monsterinfo()
{
	int y = HEIGHT * 0.14f;
	system("cls");
	for (int i = 0; i < Ms.monstercount(); i++)
	{
		Ms.showMonster(WIDTH*0.5f, y, i);
		y += 4;
	}
	system("pause>null");
}

void GameManager::Load(char* buf, int Select, char *buf2)
{
	system("cls");
	ifstream monsterload, playerLoad;
	sprintf(buf, "SaveMonster%d.txt", Select);
	sprintf(buf2, "SavePlayer%d.txt", Select);
	monsterload.open(buf);
	playerLoad.open(buf2);
	if (!monsterload && !playerLoad)
	{
		map->gotoxy(WIDTH * 0.5f, HEIGHT*0.5f);
		cout << "해당 파일이 없습니다." << endl;
		system("pause>null");
	}
	else
	{
		Ms.Reset();
		Ms.LoadMonster(buf);
		player->Reset();
		player->LoadPlayer(buf2);
	}
}

void GameManager::Save(char* buf, int Select, char* buf2)
{
	system("cls");
	ofstream monsterload, playerLoad;
	sprintf(buf, "SaveMonster%d.txt", Select);
	sprintf(buf2, "SavePlayer%d.txt", Select);
	Ms.Save(buf);
	player->Save(buf2, shop.WeaponNumber());
	bLoad = false;
}

void GameManager::Dangan(bool batteselect)
{
	int Select;
	batte = true;
	switch (Select = map->MenuSelectCursor(7, 2, WIDTH * 0.3f, HEIGHT*0.38f))
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		monsterbatte(Select, batteselect);
		break;
	case 7:
		BattleESC = false;
		break;
	}
}

void GameManager::monsterbatte(int Select,bool batteselect)
{
	int Monsterrandom = 0;
	int weaponeffect = 0;
	char numbering;
	int Playerkey = 0;
	bool Die = false;
	while (batte)
	{
		BLUE
			map->BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			YELLOW
			player->showplayer(WIDTH, HEIGHT*0.1f);
		map->TextDraw("가위 : 1  바위 : 2  보 : 3", WIDTH*0.56f, HEIGHT*0.35f);
		if (bRamdomeffect == true)
		{
			map->gotoxy(WIDTH*0.08f, HEIGHT*0.45f);
			player->showeffect();
		}
		if (Playerkey == 1)
			map->TextDraw("가위", WIDTH, HEIGHT*0.4f);
		else if (Playerkey == 2)
			map->TextDraw("바위", WIDTH, HEIGHT*0.4f);
		else if (Playerkey == 3)
			map->TextDraw("보", WIDTH, HEIGHT*0.4f);

		ORIGINAL
			RED
			if (bDraw == true)
				map->TextDraw("Draw", WIDTH, HEIGHT*0.45f);
		if (bPlayerwin == true)
			map->TextDraw("Win", WIDTH, HEIGHT*0.45f);
		if (bPlayerLose == true)
			map->TextDraw("Lose", WIDTH, HEIGHT*0.45f);
		map->TextDraw("========================== vs =========================", WIDTH*0.08f, HEIGHT*0.5f);
		if (bDraw == true)
			map->TextDraw("Draw", WIDTH, HEIGHT*0.55f);
		if (bPlayerLose == true)
			map->TextDraw("Win", WIDTH, HEIGHT*0.55f);
		if (bPlayerwin == true)
			map->TextDraw("Lose", WIDTH, HEIGHT*0.55f);
		ORIGINAL

			if (Monsterrandom == 1)
				map->TextDraw("가위", WIDTH, HEIGHT*0.6f);
			else if (Monsterrandom == 2)
				map->TextDraw("바위", WIDTH, HEIGHT*0.6f);
			else if (Monsterrandom == 3)
				map->TextDraw("보", WIDTH, HEIGHT*0.6f);

		Ms.showMonster(WIDTH*0.5f, HEIGHT*0.82f, Select - 1);
		if (bRamdomeffect == false)
		{
			Monsterrandom = rand() % 3 + 1;
		}
		numbering = _getch();
		switch (numbering)//가위 바위 보 누를떄 
		{
		case '1':
			Playerkey = 1;
			Rock_Paper_Scissors(Playerkey, Monsterrandom, Select - 1, batteselect);
			break;
		case '2':
			Playerkey = 2;
			Rock_Paper_Scissors(Playerkey, Monsterrandom, Select - 1, batteselect);
			break;
		case '3':
			Playerkey = 3;
			Rock_Paper_Scissors(Playerkey, Monsterrandom, Select - 1, batteselect);
			break;
		}
	}
}

void GameManager::Rock_Paper_Scissors(int Playerkey, int Monsterrandom, int Select, bool batteselect)
{
	bRamdomeffect = false;
	if (Playerkey == ROCK && Monsterrandom == ROCK || Playerkey == SCISSORS && Monsterrandom == SCISSORS
		|| Playerkey == PAPER && Monsterrandom == PAPER)//무승부
	{
		bDraw = true;
		bPlayerwin = false;
		bPlayerLose = false;
	}
	else if (Playerkey == ROCK && Monsterrandom == SCISSORS || Playerkey == SCISSORS && Monsterrandom == PAPER
		|| Playerkey == PAPER && Monsterrandom == ROCK)// 인간 승리
	{
		bPlayerwin = true;
		bPlayerLose = false;
		bDraw = false;
		//if (bweaponUse == true)//무기를 장착하면
		//{
		//	Ms.Damage(player->weaponeffect(bRamdomeffect), Select);//효과확률
		//}
		//else
		Ms.Damage(player->weaponeffect(bRamdomeffect), Select);//일반 공격 무기있으면 무기랑 합한 데미지

		if (Ms.Current_health(Select) <= 0)
		{
			bRamdomeffect = false;
			system("cls");
			BLUE
				map->BoxDraw(0, 0, WIDTH, HEIGHT);
			ORIGINAL
				player->Victory(WIDTH*0.5f, HEIGHT*0.4f, Ms.Earned_Experience(Select), Ms.money(Select));
			Ms.RegetHp(Select);
			batte = false;
		}

	}
	else if (Playerkey == ROCK && Monsterrandom == PAPER || Playerkey == SCISSORS && Monsterrandom == ROCK
		|| Playerkey == PAPER && Monsterrandom == SCISSORS)//몬스터 승리
	{
		bDraw = false;
		bPlayerwin = false;
		bPlayerLose = true;
		player->Damage(Ms.power(Select));
		system("cls");
		BLUE
			map->BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			if (player->Current_health() <= 0)
			{
				Ms.Victory(WIDTH*0.5f, HEIGHT*0.4f, player->Earned_Experience(), Select);
				player->ResetHp();
				batte = false;
				batteselect = false;
			}
	}
}

void GameManager::weaponShop()
{
	int Select;
	m_bshopopen = true;
	switch (Select = map->MenuSelectCursor(7, 2, WIDTH * 0.3f, HEIGHT*0.38f))
	{
	case WEAPON_DAGGER:
		if (player->job() != PLAYERJOB_ASSASSIN)
			Different_profession();
		else
			shop.showweaponNemnnu((WEAPON)Select, player);
		break;
	case WEAPON_GUN:
		if (player->job() != PLAYERJOB_ARCHER)
			Different_profession();
		else
			shop.showweaponNemnnu((WEAPON)Select, player);
		break;
	case WEAPON_SWORD:
		if (player->job() != PLAYERJOB_KNIGHT)
			Different_profession();
		else
			shop.showweaponNemnnu((WEAPON)Select, player);
		break;
	case WEAPON_WAND:
		if (player->job() != PLAYERJOB_WIZARD)
			Different_profession();
		else
			shop.showweaponNemnnu((WEAPON)Select, player);
		break;
	case WEAPON_BOW:
		if (player->job() != PLAYERJOB_ARCHER)
			Different_profession();
		else
			shop.showweaponNemnnu((WEAPON)Select, player);
		break;
	case WEAPON_HAMMER:
		if (player->job() != PLAYERJOB_KNIGHT)
			Different_profession();
		else
			shop.showweaponNemnnu((WEAPON)Select, player);
		break;
	case WEAPON_END:
		m_bshopopen = false;
		return;
	}
}

void GameManager::Different_profession()
{
	system("cls");
	map->DrawMidText("다른 직업군입니다. 구매할수없습니다.", WIDTH, HEIGHT*0.5f);
	getch();
}

int GameManager::mapSelect(int MenuLen, int AddCol, int x, int y)
{
	return map->MenuSelectCursor(MenuLen, AddCol, x, y);
}

GameManager::~GameManager()
{
	delete player;
	if (player != NULL)
		player = NULL;
}

void GameManager::Initialized()
{
	map = CreateMenu();
}

void GameManager::Menu()
{
	map->Render();
}

void GameManager::Finished()
{
	delete map;
}

MapDraw* JobManager::CreateMenu()
{
	return new JobMap();
}


MapDraw* firstMenu::CreateMenu()
{
	return new firstmenu();
}

MapDraw* MainMenuManager::CreateMenu()
{
	return new Mainmenu();
}

MapDraw* DanganMenuManager::CreateMenu()
{
	return new danganmenu();
}

MapDraw* ShopMenuManager::CreateMenu()
{
	return new shopMenu();
}