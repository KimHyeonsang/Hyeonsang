#include "Weapon.h"


Weapon::Weapon(int Damage, string Name, WEAPON type, int price)
{
	m_iDamage = Damage;
	m_iprice = price;
	m_strName = Name;
	m_Type = type;
}
Weapon::Weapon()
{
	
}

void Weapon::ShowInfo(int x,int y)
{
	string Type;
	switch (m_Type)
	{
	case  WEAPON_DAGGER:
			Type = "´ë°Å";
			break;
		case WEAPON_GUN:
			Type = "ÃÑ";
			break;
		case WEAPON_SWORD:
			Type = "¼Òµå";
			break;
		case WEAPON_WAND:
			Type = "ÁöÆÎÀÌ";
			break;
		case WEAPON_BOW:
			Type = "È°";
			break;
		case WEAPON_HAMMER:
			Type = "µÐ±â";
			break;
	}
	map.DrawMidText("°¡°Ý : " + to_string(m_iprice) + " ¹«±âÅ¸ÀÔ : " + Type, x, y);
	map.DrawMidText(" ¹«±âÀÌ¸§ : " + m_strName + " °ø°Ý·Â : " + to_string(m_iDamage), x, y + 1);
}
int Weapon::WeaponGold()
{
	return m_iprice;
}
int Weapon::weaponAttack()
{
	return m_iDamage;
}
string Weapon::WeaponName()
{
	return m_strName;
}

Weapon::~Weapon()
{

}

Bow::Bow()
{
	m_strName = "³ì½¼ È°";
	m_iDamage = 5;
	m_Type = WEAPON_BOW;
	m_iprice = 0;

}
//Bow::Bow(Bow* bow)
//{
//	m_strName = bow->m_strName;
//	m_iDamage = bow->m_iDamage;
//	m_iprice = bow->m_iprice;
//	m_Type = bow->m_Type;
//}

Bow::Bow(string name, int Damage, int Gold)
{
	m_strName = name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_BOW;
}
int Bow::Weaponeffect(int number, bool& bRamdomeffect)
{//È®·ü·Î 2Å¸  ¹«±â°¡ 5°µµ¥ È®·ü Á¦°¢°¢10ÆÛ,20ÆÛ,30ÆÛ,40ÆÛ,50ÆÛ
	int weaponeffect = rand() % 100 + 1; //·£´ý
	srand(time(NULL));
	int critical = m_iDamage;
	if (number == 0)
	{
		if (weaponeffect <= 10)
		{
			critical *= 1.25;
			bRamdomeffect = true;
		}
	}
	else if (number == 1)
	{
		if (weaponeffect <= 20)
		{
			critical *= 1.25;
			bRamdomeffect = true;
		}
	}
	else if (number == 2)
	{
		if (weaponeffect <= 30)
		{
			critical *= 1.25;
			bRamdomeffect = true;
		}
	}
	else if (number == 3)
	{
		if (weaponeffect <= 40)
		{
			critical *= 1.25;
			bRamdomeffect = true;
		}
	}
	else if (number == 4)
	{
		if (weaponeffect <= 95)
		{
			critical *= 1.25;
			bRamdomeffect = true;
		}
	}
	return critical;
}
void Bow::ShowWeaponeffect()
{
	cout << "Ä¡¸íÅ¸°¡ ÅÍ ’½À´Ï´Ù.";
}
Bow::~Bow()
{
}
Dagger::Dagger()
{
	m_strName = "³ì½¼ ´Ü°Ë";
	m_iDamage = 5;
	m_Type = WEAPON_DAGGER;
	m_iprice = 0;
}
//Dagger::Dagger(Dagger* dagger)
//{
//	m_strName = dagger->m_strName;
//	m_iDamage = dagger->m_iDamage;
//	m_iprice = dagger->m_iprice;
//	m_Type = dagger->m_Type;
//}

Dagger::Dagger(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_DAGGER;
}
int Dagger::Weaponeffect(int number, bool& bRamdomeffect)
{//È®·ü·Î 2Å¸  ¹«±â°¡ 5°µµ¥ È®·ü Á¦°¢°¢10ÆÛ,20ÆÛ,30ÆÛ,40ÆÛ,50ÆÛ
	int weaponeffect = rand() % 100 + 1; //·£´ý
	srand(time(NULL));
	int DoubleDamage = m_iDamage;
	if (number == 5)
	{
		if (weaponeffect <= 10)
		{
			DoubleDamage = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	else if (number == 6)
	{
		if (weaponeffect <= 20)
		{
			DoubleDamage = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	else if (number == 7)
	{
		if (weaponeffect <= 30)
		{
			DoubleDamage = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	else if (number == 8)
	{
		if (weaponeffect <= 40)
		{
			DoubleDamage = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	else if (number == 9)
	{
		if (weaponeffect <= 50)
		{
			DoubleDamage = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	else if (number == 10)
	{
		if (weaponeffect <= 95)
		{
			DoubleDamage = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	return DoubleDamage;
}
void Dagger::ShowWeaponeffect()
{
	cout << "Ãß°¡Å¸¸¦ ¶§·È½À´Ï´Ù.";
}
Dagger::~Dagger()
{
}

Gun::Gun()
{
	m_strName = "³ì½¼ ÃÑ";
	m_iDamage = 5;
	m_Type = WEAPON_GUN;
	m_iprice = 0;
}
//Gun::Gun(Gun* gun)
//{
//	m_strName = gun->m_strName;
//	m_iDamage = gun->m_iDamage;
//	m_iprice = gun->m_iprice;
//	m_Type = gun->m_Type;
//}


Gun::Gun(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_GUN;
}

int Gun::Weaponeffect(int number, bool& bRamdomeffect)
{//È®·ü·Î 2Å¸  ¹«±â°¡ 5°µµ¥ È®·ü Á¦°¢°¢10ÆÛ,20ÆÛ,30ÆÛ,40ÆÛ,50ÆÛ
	int weaponeffect = rand() % 100 + 1; //·£´ý
	srand(time(NULL));
	int Critical = m_iDamage;
	if (number == 11)
	{
		if (weaponeffect <= 10)
		{
			Critical = m_iDamage * 1.5;
			bRamdomeffect = true;
		}
	}
	if (number == 12)
	{
		if (weaponeffect <= 20)
		{
			Critical = m_iDamage * 1.5;
			bRamdomeffect = true;
		}
	}
	if (number == 13)
	{
		if (weaponeffect <= 30)
		{
			Critical = m_iDamage * 1.5;
			bRamdomeffect = true;
		}
	}
	if (number == 14)
	{
		if (weaponeffect <= 95)
		{
			Critical = m_iDamage * 1.5;
			bRamdomeffect = true;
		}
	}
	return Critical;
}
void Gun::ShowWeaponeffect()
{
	cout << "Ä¡¸íÅ¸°¡ ÅÍÁ³½À´Ï´Ù.";
}
Gun::~Gun()
{
}

Hammer::Hammer()
{
	m_strName = "³ì½¼ ÇØ¸Ó";
	m_iDamage = 3;
	m_Type = WEAPON_HAMMER;
	m_iprice = 0;
}
//Hammer::Hammer(Hammer* hammer)
//{
//	m_strName = hammer->m_strName;
//	m_iDamage = hammer->m_iDamage;
//	m_iprice = hammer->m_iprice;
//	m_Type = hammer->m_Type;
//}

Hammer::Hammer(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_HAMMER;
}
int Hammer::Weaponeffect(int number, bool& bRamdomeffect)
{//È®·ü·Î 2Å¸  ¹«±â°¡ 5°µµ¥ È®·ü Á¦°¢°¢10ÆÛ,20ÆÛ,30ÆÛ,40ÆÛ,50ÆÛ
	int weaponeffect = rand() % 100 + 1; //·£´ý
	srand(time(NULL));
	if (number == 25)
	{
		if (weaponeffect <= 10)
		{
			bRamdomeffect = true;
		}
	}
	if (number == 26)
	{
		if (weaponeffect <= 20)
		{
			bRamdomeffect = true;
		}
	}
	if (number == 27)
	{
		if (weaponeffect <= 30)
		{
			bRamdomeffect = true;
		}
	}
	if (number == 28)
	{
		if (weaponeffect <= 40)
		{
			bRamdomeffect = true;
		}
	}
	if (number == 29)
	{
		if (weaponeffect <= 95)
		{
			bRamdomeffect = true;
		}
	}
	return m_iDamage;
}
void Hammer::ShowWeaponeffect()
{
	cout << "1ÅÏ µ¿¾È ½ºÅÏÀÌ °É·È½À´Ï´Ù.";
}
Hammer::~Hammer()
{
}

Sword::Sword()
{
	m_strName = "³ì½¼ °Ë";
	m_iDamage = 5;
	m_Type = WEAPON_SWORD;
	m_iprice = 0;
}
//Sword::Sword(Sword* sword)
//{
//	m_strName = sword->m_strName;
//	m_iDamage = sword->m_iDamage;
//	m_iprice = sword->m_iprice;
//	m_Type = sword->m_Type;
//}

Sword::Sword(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_SWORD;
}

int Sword::Weaponeffect(int number, bool& bRamdomeffect)
{//È®·ü·Î Ä¡¸í200ÆÛ  ¹«±â°¡ 5°µµ¥ È®·ü Á¦°¢°¢10ÆÛ,20ÆÛ,30ÆÛ,40ÆÛ,50ÆÛ
	int weaponeffect = rand() % 100 + 1; //·£´ý
	srand(time(NULL));
	int Critical = m_iDamage;
	if (number == 15)
	{
		if (weaponeffect <= 10)
		{
			Critical = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	if (number == 16)
	{
		if (weaponeffect <= 20)
		{
			Critical = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	if (number == 17)
	{
		if (weaponeffect <= 30)
		{
			Critical = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	if (number == 18)
	{
		if (weaponeffect <= 40)
		{
			Critical = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	if (number == 19)
	{
		if (weaponeffect <= 95)
		{
			Critical = m_iDamage * 2;
			bRamdomeffect = true;
		}
	}
	return Critical;
}
void Sword::ShowWeaponeffect()
{
	cout << "Å©¸®Æ¼ÄÃÀÌ ÅÍÁ³½À´Ï´Ù.";
}
Sword::~Sword()
{
}

Wand::Wand()
{
	m_strName = "³ì½¼ ÁöÆÎÀÌ";
	m_iDamage = 3;
	m_Type = WEAPON_WAND;
	m_iprice = 0;
}
//Wand::Wand(Wand* wand)
//{
//	m_strName = wand->m_strName;
//	m_iDamage = wand->m_iDamage;
//	m_iprice = wand->m_iprice;
//	m_Type = wand->m_Type;
//}

Wand::Wand(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_WAND;
}
int Wand::Weaponeffect(int number, bool& bRamdomeffect)
{//È®·ü·ÎÈ¸º¹  ¹«±â°¡ 5°µµ¥ È®·ü Á¦°¢°¢10ÆÛ,20ÆÛ,30ÆÛ,40ÆÛ,50ÆÛ
	int weaponeffect = rand() % 100 + 1; //·£´ý
	srand(time(NULL));
	int Critical;
	if (number == 20)
	{
		if (weaponeffect <= 10)
		{
			Critical = m_iDamage * 2.5;
			bRamdomeffect = true;
		}
	}
	if (number == 21)
	{
		if (weaponeffect <= 20)
		{
			Critical = m_iDamage * 2.5;
			bRamdomeffect = true;
		}
	}
	if (number == 22)
	{
		if (weaponeffect <= 30)
		{
			Critical = m_iDamage * 2.5;
			bRamdomeffect = true;
		}
	}
	if (number == 23)
	{
		if (weaponeffect <= 40)
		{
			Critical = m_iDamage * 2.5;
			bRamdomeffect = true;
		}
	}
	if (number == 24)
	{
		if (weaponeffect <= 95)
		{
			Critical = m_iDamage * 2.5;
			bRamdomeffect = true;
		}
	}
	return Critical;
}
void Wand::ShowWeaponeffect()
{
	cout << "2Å¸¸¦ ¶§·È½À´Ï´Ù.";
}
Wand::~Wand()
{
}


