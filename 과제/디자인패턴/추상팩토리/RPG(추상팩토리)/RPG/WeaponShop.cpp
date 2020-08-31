#include "WeaponShop.h"


//무기 리스트들
WeaponShop::WeaponShop()
{
	for (int i = 0; i < 6; i++)
	{
		totalcount[i] = { NULL };
		firstweapon[i] = { NULL };
	}
	bDaggerMenu = true;
	m_iweaponNumber = 0;
	bWeaponchange = false;
	Endweaponnumber = 0;
	ifstream load;
	string strName;
	string strType;
	int iDamage;
	int iGold;
	load.open("WeaponList.txt");
	if (load.is_open())
	{
		while (!load.eof())
		{
			load >> strType;
			load >> strName;
			load >> iDamage;
			load >> iGold;
			if (strType == "Dagger")
			{
				weaponlist = new Dagger(strName, iDamage, iGold);
				m_vector.push_back(weaponlist);
			}
			else if (strType == "Gun")
			{
				weaponlist = new Gun(strName, iDamage, iGold);
				m_vector.push_back(weaponlist);
			}
			else if (strType == "Bow")
			{
				weaponlist = new Bow(strName, iDamage, iGold);
				m_vector.push_back(weaponlist);
			}
			else if (strType == "Hammer")
			{
				weaponlist = new Hammer(strName, iDamage, iGold);
				m_vector.push_back(weaponlist);
			}
			else if (strType == "Sword")
			{
				weaponlist = new Sword(strName, iDamage, iGold);
				m_vector.push_back(weaponlist);
			}
			else if (strType == "Wand")
			{
				weaponlist = new Wand(strName, iDamage, iGold);
				m_vector.push_back(weaponlist);
			}
		}
		load.close();
	}

}

void WeaponShop::NomaltopMenu(int Gold)
{
	map.TextDraw("보유 Gold : ", WIDTH * 0.7f, HEIGHT*0.08f);
	map.gotoxy(WIDTH * 1.2f, HEIGHT*0.08f);
	cout << Gold;
	map.TextDraw("Dagger Sop", WIDTH * 0.8f, HEIGHT*0.15f);
}


void WeaponShop::showweaponNemnnu(bool& bweaponUse, WEAPON Type, Player* player)
{
	bDaggerMenu = true;
	bWeaponchange = false;
	Weapon* tempweapon;
	int select = 0;
	int Yline;
	int Page = 0;
	int count;
	bool CheckPage;
	while (bDaggerMenu)
	{
		Yline = 0;
		int Menucount = 0; //다음을 누를떄 그이후를할떄
		int Seconcount = 5; //맥심숫자
		int  y = HEIGHT * 0.2f;
		int CountList = 0;
		count = 0;
		system("cls");
		BLUE
			map.BoxDraw(0, 0, WIDTH, HEIGHT);
		ORIGINAL
			NomaltopMenu(player->Gold());
		YELLOW
			for (m_iter = m_vector.begin(); m_iter != m_vector.end(); ++m_iter)
			{
				weaponlist = *m_iter;
				if (weaponlist->WeaponType() == Type)
				{
					if (CountList >= Page && CountList < Page + 5)
					{
						weaponlist->ShowInfo(WIDTH, y + Yline++ * 3);
						Menucount++;
					}
					CountList++;
				}				
			}
		if (CountList > Page + 5)
			CheckPage = true;
		else
			CheckPage = false;

		ORIGINAL
		map.TextDraw("이전페이지", WIDTH*0.85f, y + Yline++ * 3);
		map.TextDraw("다음페이지", WIDTH * 0.85f, y + Yline++ * 3);
		map.TextDraw("나가기", WIDTH * 0.9f, y + Yline++ * 3);
		Menucount += 3;
		select = map.MenuSelectCursor(Menucount, 3, WIDTH * 0.1f, HEIGHT*0.2f);
		if (select <= Menucount - 3)
		{
		//	if (bWeaponchange == true)
		//		player->finalweapon();
			switch (Type)
			{
			case WEAPON_DAGGER:
				for (m_iter = m_vector.begin(); m_iter != m_vector.end(); ++m_iter)
				{
					weaponlist = *m_iter;
					if (weaponlist->WeaponType() == Type)
					{
						++count;
						if (count + Page == select)
						{
							if (JobCheckking(player))
								player->Buy(weaponlist, Type);
							else
								cout << "구매실패!" << endl;
						}
					}
				}
				break;
			case WEAPON_GUN:
				for (m_iter = m_vector.begin(); m_iter != m_vector.end(); ++m_iter)
				{
					weaponlist = *m_iter;
					if (weaponlist->WeaponType() == Type)
					{
						++count;
						if (count + Page == select)
							player->Buy(weaponlist, Type);
					}
				}
				break;
			case WEAPON_SWORD:
				for (m_iter = m_vector.begin(); m_iter != m_vector.end(); ++m_iter)
				{
					weaponlist = *m_iter;
					if (weaponlist->WeaponType() == Type)
					{
						++count;
						if (count + Page == select)
							player->Buy(weaponlist, Type);
					}
				}
				break;
			case WEAPON_WAND:
				for (m_iter = m_vector.begin(); m_iter != m_vector.end(); ++m_iter)
				{
					weaponlist = *m_iter;
					if (weaponlist->WeaponType() == Type)
					{
						++count;
						if (count + Page == select)
							player->Buy(weaponlist, Type);
					}
				}
				break;
			case WEAPON_BOW:
				for (m_iter = m_vector.begin(); m_iter != m_vector.end(); ++m_iter)
				{
					weaponlist = *m_iter;
					if (weaponlist->WeaponType() == Type)
					{
						++count;
						if (count + Page == select)
							player->Buy(weaponlist, Type);
					}
				}
				break;
			case WEAPON_HAMMER:
				for (m_iter = m_vector.begin(); m_iter != m_vector.end(); ++m_iter)
				{
					weaponlist = *m_iter;
					if (weaponlist->WeaponType() == Type)
					{
						++count;
						if (count + Page == select)
							player->Buy(weaponlist, Type);
					}
				}
				break;
			}
			bweaponUse = true;
		}
		else if (Menucount - 2 == select && Page - 5 >= 0)
		{
			Page -= 5;
		}
		else if (Menucount - 1 == select && CheckPage)
		{
			Page += 5;
		}
		else if (Menucount  == select)
		{
			bDaggerMenu = false;			
			break;		
		}
	}
}
bool WeaponShop::JobCheckking(Player* job)
{
	return job->EquipCheck();
}

WeaponShop::~WeaponShop()
{

}