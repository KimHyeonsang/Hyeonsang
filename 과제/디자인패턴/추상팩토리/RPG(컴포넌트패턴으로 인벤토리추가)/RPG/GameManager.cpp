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
	batteselect = true;
	bRamdomeffect = false;
	bweaponUse = false;
	bWeaponchange = false;
}

void GameManager::SelectJob()
{
	system("cls");
	int line = 0;
	int Select;
	int y = HEIGHT * 0.2f;
	BLUE
		map.BoxDraw(0, 0, WIDTH, HEIGHT);
	ORIGINAL
		map.DrawMidText("������ ���ϼ���(�����ϰ� ���ϼ���.)  ", WIDTH, y+ line++ * 3);
	map.DrawMidText("1. ����(��,�ظ�)  ", WIDTH, y + line++ * 3);
	map.DrawMidText("2. ����(�ܰ�) ", WIDTH, y + line++ * 3);
	map.DrawMidText("3. ������(�ϵ�) ", WIDTH, y + line++ * 3);
	map.DrawMidText("4. �ü�(Ȱ,��)  ", WIDTH, y + line++ * 3);
	Select = map.MenuSelectCursor(4, 3, WIDTH * 0.25f, HEIGHT * 0.3f);
		if (Select == 1)
		{
			KnightCharacter* knightFactory = new KnightCharacter();
			JobClass* knight = knightFactory->CreateJobClass();
			Weapon* sword = knightFactory->CreateWeapon();
		}
		else if (Select == 2)
		{
			shipCharactor* shipFactory = new shipCharactor();
			JobClass* ship = shipFactory->CreateJobClass();
			Weapon* Dagger = shipFactory->CreateWeapon();
		}
		else if (Select == 3)
		{
			WizardCharacter* wizardFactory = new WizardCharacter();
			JobClass* wizard = wizardFactory->CreateJobClass();
			Weapon* wand = wizardFactory->CreateWeapon();
		}
		else if (Select == 4)
		{
			ArcherCharacter* archerFactory = new ArcherCharacter();
			JobClass* archer = archerFactory->CreateJobClass();
			Weapon* bow = archerFactory->CreateWeapon();
		}
}
void GameManager::NewGame()
{
	system("cls");
	player = new Player;
	int y = HEIGHT * 0.14f;
	BLUE
		map.BoxDraw(0, 0, WIDTH, HEIGHT);
	ORIGINAL
		string name;
	if (bLoad == true)
	{
		YELLOW
			map.TextDraw("Player �̸� �Է� : ", WIDTH*0.65f, HEIGHT*0.5f);
		cin >> name;
		ORIGINAL
			player->SetName(name);
	}
	while (1)
	{
		batteselect = true;
		system("cls");
		BLUE
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			GameMenu();
		switch (map.MenuSelectCursor(7, 2, WIDTH * 0.35f, HEIGHT*0.38f))
		{
		case 1:
			Dangan();
			break;
		case 2:
			system("cls");
			YELLOW
				player->showplayer(WIDTH*0.5f, HEIGHT*0.4f, sword);
			ORIGINAL
				system("pause>null");
			break;
		case 3:
			system("cls");
			for (int i = 0; i < Ms.monstercount(); i++)
			{
				Ms.showMonster(WIDTH*0.5f, y, i);
				y += 4;
			}
			system("pause>null");
			break;
		case 4:
			weaponShop();
			break;
		case 5:
			player->invenview(WIDTH, HEIGHT * 0.1f);
			break;
		case 6:
			bSave = true;
			LoadSave();
			break;
		case 7:
			return;
		}
	}
}
void GameManager::GameMenu()
{
	map.TextDraw("�١� Menu �ڡ�", WIDTH*0.75f, HEIGHT*0.3f);
	map.TextDraw("Dongeon", WIDTH*0.88f, HEIGHT*0.38f);
	map.TextDraw("Player Info", WIDTH*0.85f, HEIGHT*0.46f);
	map.TextDraw("Monster Info", WIDTH*0.8f, HEIGHT*0.5f);
	map.TextDraw("Weapon Shop", WIDTH*0.85f, HEIGHT*0.58f);
	map.TextDraw("Inventory", WIDTH*0.85f, HEIGHT*0.64f);
	map.TextDraw("Save", WIDTH*0.88f, HEIGHT*0.72f);
	map.TextDraw("Exit", WIDTH*0.88f, HEIGHT*0.78f);
}

void GameManager::LoadSave()
{
	bLoad = true;
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
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			for (int i = 1; i < 11; i++)
			{
				map.gotoxy(x, y);
				sprintf(buf, "SaveMonster%d.txt", i);
				sprintf(buf2, "SavePlayer%d.txt", i);
				monsterload.open(buf);
				playerLoad.open(buf2);
				if (!monsterload && !playerLoad)
				{
					GREEN
						cout << i << "�� ���� : (���� ���� : X)" << endl;
				}
				else
				{
					GREEN
						cout << i << "�� ���� : (���� ���� : O)" << endl;
					monsterload.close();
					playerLoad.close();
				}
				y += 2;
			}
		map.gotoxy(x, y);
		cout << "11. ���ư���" << endl;
		ORIGINAL
			switch (select = map.MenuSelectCursor(11, 2, WIDTH * 0.2f, HEIGHT*0.2f))
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
		map.gotoxy(WIDTH * 0.5f, HEIGHT*0.5f);
		cout << "�ش� ������ �����ϴ�." << endl;
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
void GameManager::Dangan()
{
	int Select;
	while (batteselect)
	{
		batte = true;
		system("cls");
		BLUE
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			map.TextDraw("====���� �Ա�====", WIDTH*0.75f, HEIGHT*0.2f);
		map.TextDraw("1������ : [���]", WIDTH*0.78f, HEIGHT*0.38f);
		map.TextDraw("2������ : [��ũ]", WIDTH*0.8f, HEIGHT*0.46f);
		map.TextDraw("3������ : [�����ΰ�]", WIDTH*0.75f, HEIGHT*0.5f);
		map.TextDraw("4������ : [�����]", WIDTH*0.8f, HEIGHT*0.58f);
		map.TextDraw("5������ : [���̷����ó]", WIDTH*0.72f, HEIGHT*0.64f);
		map.TextDraw("6������ : [��ġ]", WIDTH*0.8f, HEIGHT*0.72f);
		map.TextDraw("���ư���", WIDTH*0.88f, HEIGHT*0.78f);
		switch (Select = map.MenuSelectCursor(7, 2, WIDTH * 0.3f, HEIGHT*0.38f))
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			monsterbatte(Select);
			break;
		case 7:
			return;
		}
	}
}
void GameManager::monsterbatte(int Select)
{
	int Monsterrandom = 0;
	int weaponeffect = 0;
	char numbering;
	int Playerkey = 0;
	bool Die = false;
	while (batte)
	{
		BLUE
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			YELLOW
			player->showplayer(WIDTH*0.5f, HEIGHT*0.14f, sward);
		map.TextDraw("���� : 1  ���� : 2  �� : 3", WIDTH*0.56f, HEIGHT*0.35f);
		if (bRamdomeffect == true)
		{
			map.gotoxy(WIDTH*0.08f, HEIGHT*0.45f);
			player->showeffect();
		}
		if (Playerkey == 1)
			map.TextDraw("����", WIDTH, HEIGHT*0.4f);
		else if (Playerkey == 2)
			map.TextDraw("����", WIDTH, HEIGHT*0.4f);
		else if (Playerkey == 3)
			map.TextDraw("��", WIDTH, HEIGHT*0.4f);

		ORIGINAL
			RED
			if (bDraw == true)
				map.TextDraw("Draw", WIDTH, HEIGHT*0.45f);
		if (bPlayerwin == true)
			map.TextDraw("Win", WIDTH, HEIGHT*0.45f);
		if (bPlayerLose == true)
			map.TextDraw("Lose", WIDTH, HEIGHT*0.45f);
		map.TextDraw("========================== vs =========================", WIDTH*0.08f, HEIGHT*0.5f);
		if (bDraw == true)
			map.TextDraw("Draw", WIDTH, HEIGHT*0.55f);
		if (bPlayerLose == true)
			map.TextDraw("Win", WIDTH, HEIGHT*0.55f);
		if (bPlayerwin == true)
			map.TextDraw("Lose", WIDTH, HEIGHT*0.55f);
		ORIGINAL

			if (Monsterrandom == 1)
				map.TextDraw("����", WIDTH, HEIGHT*0.6f);
			else if (Monsterrandom == 2)
				map.TextDraw("����", WIDTH, HEIGHT*0.6f);
			else if (Monsterrandom == 3)
				map.TextDraw("��", WIDTH, HEIGHT*0.6f);

		Ms.showMonster(WIDTH*0.5f, HEIGHT*0.82f, Select - 1);
		if (bRamdomeffect == false)
		{
			Monsterrandom = rand() % 3 + 1;
		}
		numbering = _getch();
		switch (numbering)//���� ���� �� ������ 
		{
		case '1':
			Playerkey = 1;
			Rock_Paper_Scissors(Playerkey, Monsterrandom, Select - 1);
			break;
		case '2':
			Playerkey = 2;
			Rock_Paper_Scissors(Playerkey, Monsterrandom, Select - 1);
			break;
		case '3':
			Playerkey = 3;
			Rock_Paper_Scissors(Playerkey, Monsterrandom, Select - 1);
			break;
		}
	}
}
void GameManager::Rock_Paper_Scissors(int Playerkey, int Monsterrandom, int Select)
{
	bRamdomeffect = false;
	if (Playerkey == ROCK && Monsterrandom == ROCK || Playerkey == SCISSORS && Monsterrandom == SCISSORS
		|| Playerkey == PAPER && Monsterrandom == PAPER)//���º�
	{
		bDraw = true;
		bPlayerwin = false;
		bPlayerLose = false;
	}
	else if (Playerkey == ROCK && Monsterrandom == SCISSORS || Playerkey == SCISSORS && Monsterrandom == PAPER
		|| Playerkey == PAPER && Monsterrandom == SCISSORS)// �ΰ� �¸�
	{
		bPlayerwin = true;
		bPlayerLose = false;
		bDraw = false;
		if (bweaponUse == true)//���⸦ �����ϸ�
		{
			Ms.Damage(player->weaponeffect(bRamdomeffect), Select);//ȿ��Ȯ��
		}
		else
			Ms.Damage(player->power(), Select);//�Ϲ� ���� ���������� ����� ���� ������

		if (Ms.Current_health(Select) <= 0)
		{
			bRamdomeffect = false;
			system("cls");
			BLUE
				map.BoxDraw(0, 0, WIDTH, HEIGHT);
			ORIGINAL
				player->Victory(WIDTH*0.5f, HEIGHT*0.4f, Ms.Earned_Experience(Select), Ms.money(Select));
			Ms.RegetHp(Select);
			batte = false;
		}

	}
	else if (Playerkey == ROCK && Monsterrandom == PAPER || Playerkey == SCISSORS && Monsterrandom == ROCK
		|| Playerkey == PAPER && Monsterrandom == ROCK)//���� �¸�
	{
		bDraw = false;
		bPlayerwin = false;
		bPlayerLose = true;
		player->Damage(Ms.power(Select));
		system("cls");
		BLUE
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
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
	while (1)
	{
		system("cls");
		BLUE
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			map.TextDraw("�� �� S H O P �� ��", WIDTH * 0.7f, HEIGHT*0.3f);
		map.TextDraw("Dagger", WIDTH * 0.8f, HEIGHT*0.38f);
		map.TextDraw("Gun", WIDTH*0.85f, HEIGHT*0.46f);
		map.TextDraw("Sword", WIDTH * 0.8f, HEIGHT*0.5f);
		map.TextDraw("Wand", WIDTH * 0.8f, HEIGHT*0.58f);
		map.TextDraw("Bow", WIDTH*0.85f, HEIGHT*0.65f);
		map.TextDraw("Hammer", WIDTH * 0.8f, HEIGHT*0.7f);
		map.TextDraw("���ư���", WIDTH*0.8f, HEIGHT*0.78f);
		switch (Select = map.MenuSelectCursor(7, 2, WIDTH * 0.3f, HEIGHT*0.38f))
		{
		case WEAPON_DAGGER:
		case WEAPON_GUN:
		case WEAPON_SWORD:
		case WEAPON_WAND:
		case WEAPON_BOW:
		case WEAPON_HAMMER:
			if (bweaponUse == true)
				player->finalweapon();
			shop.showweaponNemnnu(bweaponUse, (WEAPON)Select, player);
			break;
		case WEAPON_END:
			return;
		}
	}
}

GameManager::~GameManager()
{
	delete player;
	if (player != NULL)
		player = NULL;
}
