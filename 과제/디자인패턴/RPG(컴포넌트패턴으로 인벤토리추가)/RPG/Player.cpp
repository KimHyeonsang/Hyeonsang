#include "Player.h"



Player::Player()
{
	ifstream playerload;
	bWeaponchange = false;
	int state[6];
	playerload.open("DefaultPlayer.txt");
	{
		if (playerload.is_open() == true)
		{
			if (info != NULL)
				info = NULL;
			info = new player_Info;
			playerload >> state[0];
			info->power = state[0];
			playerload >> state[1];
			info->Max_health = state[1];
			playerload >> state[2];
			info->Max_experience = state[2];
			playerload >> state[3];
			info->Earned_Experience = state[3];
			playerload >> state[4];
			info->Level = state[4];
			playerload >> state[5];
			info->Gold = state[5];
			info->Current_experience = 0;
			info->Current_health = info->Max_health;
			info->itemnumber = 0;
			playerload.close();
		}
	}
	inventory = new Bag("MainBag");//bag안에 무기 정보를 입력
	Daggerbag = new Bag("DaggerBag");
	Bowbag = new Bag("BowBag");
	Gunbag = new Bag("GunBag");
	Wandbag = new Bag("WandBag");
	Hammerbag = new Bag("HammerBag");
	Swordbag = new Bag("SwordBag");
	Money = new Item("Money", 2000);
	inventory->AddInventory(Money);//인벤토리에 돈을 담는다
}
void Player::SetName(string str)
{
	info->name = str;
}
void Player::showplayer(int x, int y, int number)
{
	map.gotoxy(x, y);
	cout << "      =======" << info->name << "< " << info->Level << "Lv>=====";
	y++;
	map.gotoxy(x, y);
	cout << "공격력 = " << info->power << "\t" << "생명력 = " << info->Current_health << " / " << info->Max_health;
	y++;
	map.gotoxy(x, y);
	cout << "경험치 = " << info->Current_experience << " / " << info->Max_experience << "\t" << "GerExp = " << info->Earned_Experience;
	y++;
	map.gotoxy(x, y);
	cout << "Gold = " << info->Gold;
	y++;
	x -= 10;
	/*if (bWeaponusing == true)
	{
		map.gotoxy(x, y);
		//cout << "무기타입 : " << m_pweapon->WeaponType() << " 무기이름 : " << m_pweapon->WeaponName() << " 공격력 : " << m_pweapon->weaponAttack();
		m_pweapon->ShowInfo(x - 8, y + 4);

	}*/
	cout << endl;
}
void Player::LoadPlayer(char* buf)
{
	ifstream load;
	int monstercount[1];
	string monstername[1];
	int state[9];
	load.open(buf);
	{
		while (!load.eof())
		{
			if (info != NULL)
				info = NULL;
			info = new player_Info;
			load >> monstername[0];
			info->name = monstername[0];
			load >> state[0];
			info->power = state[0];
			load >> state[1];
			info->Max_health = state[1];
			load >> state[2];
			info->Max_experience = state[2];
			load >> state[3];
			info->Earned_Experience = state[3];
			load >> state[4];
			info->Level = state[4];
			load >> state[5];
			info->Gold = state[5];
			load >> state[6];
			info->Current_experience = state[6];
			load >> state[7];
			info->Current_health = state[7];
			load >> state[8];
			info->itemnumber = state[8];
			load.close();
		}
	}
}
void Player::Reset()
{
	delete info;
	if (info != NULL)
		info = NULL;
}
void Player::Save(char* buf, int number)
{
	ofstream SavePlayer;
	SavePlayer.open(buf);
	if (SavePlayer.is_open())
	{
		SavePlayer << info->name << " ";
		SavePlayer << info->power << " ";
		SavePlayer << info->Max_health << " ";
		SavePlayer << info->Max_experience << " ";
		SavePlayer << info->Earned_Experience << " ";
		SavePlayer << info->Level << " ";
		SavePlayer << info->Gold << " ";
		SavePlayer << info->Current_experience << " ";
		SavePlayer << info->Current_health << endl;
		SavePlayer << info->itemnumber << " ";
		SavePlayer.close();
	}
}
void Player::Damage(int power)
{
	info->Current_health -= power;
}
void Player::Victory(int x, int y, int Experience, int Gold)
{
	map.gotoxy(x, y);
	RED
		cout << "      " << info->name << "  승리!!";
	y += 2;
	map.gotoxy(x, y);
	cout << info->name << "가 경험치 " << Experience << "를 얻었습니다." << endl;
	ORIGINAL
		y += 2;
	info->Current_experience += Experience;
	info->Gold += Gold;
	inventory->RemoveInventory(Money);
	Money = new Item("Money", info->Gold);
	inventory->AddInventory(Money);
	map.gotoxy(-1, -1);
	system("pause>null");
	if (info->Current_experience >= info->Max_experience)
	{
		YELLOW
			power_random = rand() % 5;
		health_random = rand() % 11;
		srand(time(NULL));
		info->Current_experience = 0;
		info->Level++;
		info->Max_experience *= 1.3;
		info->power += power_random;
		info->Max_health += health_random;
		info->Current_health = info->Max_health;
		map.gotoxy(x, y);
		y += 2;
		cout << info->name << "레벨업!!";
		map.gotoxy(x, y);
		y += 2;
		cout << "공격력" << power_random << "증가!";
		map.gotoxy(x, y);
		cout << "생명력" << health_random << "증가!";
		ORIGINAL
			map.gotoxy(-1, -1);
		system("pause>null");
	}
}
void Player::ResetHp()
{
	info->Current_health = info->Max_health;
}
void Player::Buy(Weapon* weapon, WEAPON Type)//구매 하고 인벤토리 넣기
{
	m_pweapon = weapon;
	info->Gold -= weapon->WeaponGold();//골드 빼기
	inventory->RemoveInventory(Money);
	Money = new Item("Money", info->Gold);
	inventory->AddInventory(Money);
	Inventory* item;
	Inventory* item1;
	Inventory* item2;
	Inventory* item3;
	Inventory* item4;
	Inventory* item5;
	
	//어느 가방에 아이템을 넣어야하는지 조건을 달아야한다.
	switch (Type)
	{	
	case WEAPON_DAGGER:
		item = new Item("Dagger",m_pweapon);//아이템 정보를 아이템에 저장
		Daggerbag->AddInventory(item); //대거 가방에 아이템정보를 담는다
		inventory->RemoveInventory(Daggerbag);
		inventory->AddInventory(Daggerbag);//인벤토리에 가방정보를 담는다
		break;
	case WEAPON_GUN:
		item1 = new Item("Gun",m_pweapon);
		Gunbag->AddInventory(item1);
		inventory->RemoveInventory(Gunbag);
		inventory->AddInventory(Gunbag);
		break;
	case WEAPON_SWORD:
		item2 = new Item("Sword",m_pweapon);
		Swordbag->AddInventory(item2);
		inventory->RemoveInventory(Swordbag);
		inventory->AddInventory(Swordbag);
		break;
	case WEAPON_WAND:
		item3 = new Item("Wand",m_pweapon);
		Wandbag->AddInventory(item3);
		inventory->RemoveInventory(Wandbag);
		inventory->AddInventory(Wandbag);
		break;
	case WEAPON_BOW:
		item4 = new Item("Bow",m_pweapon);
		Bowbag->AddInventory(item4);
		inventory->RemoveInventory(Bowbag);
		inventory->AddInventory(Bowbag);
		break;
	case WEAPON_HAMMER:
		item5 = new Item("Hammer",m_pweapon);
		Hammerbag->AddInventory(item5);
		inventory->RemoveInventory(Hammerbag);
		inventory->AddInventory(Hammerbag);
		break;
	}
}

void Player::invenview(int x,int y)
{
	system("cls");
	
	inventory->View(x,y);
	

}
int Player::weaponeffect(bool& bRamdomeffect)
{
	return info->power + m_pweapon->Weaponeffect(number, bRamdomeffect);
}
void  Player::showeffect()
{
	m_pweapon->ShowWeaponeffect();
}


void Player::finalweapon()
{
	if (info->itemnumber == 1)
	{
		delete m_pweapon;
		if (m_pweapon != NULL)
			m_pweapon = NULL;
	}
}
Player::~Player()
{
	if (info->itemnumber == 1)
	{
		delete m_pweapon;
		if (m_pweapon != NULL)
			m_pweapon = NULL;
	}
	delete info;
	if (info != NULL)
		info = NULL;
}