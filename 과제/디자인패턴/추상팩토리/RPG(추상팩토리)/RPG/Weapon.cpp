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
			Type = "���";
			break;
		case WEAPON_GUN:
			Type = "��";
			break;
		case WEAPON_SWORD:
			Type = "�ҵ�";
			break;
		case WEAPON_WAND:
			Type = "������";
			break;
		case WEAPON_BOW:
			Type = "Ȱ";
			break;
		case WEAPON_HAMMER:
			Type = "�б�";
			break;
	}
	map.DrawMidText("���� : " + to_string(m_iprice) + " ����Ÿ�� : " + Type, x, y);
	map.DrawMidText(" �����̸� : " + m_strName + " ���ݷ� : " + to_string(m_iDamage), x, y + 1);
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

}
Bow::Bow(Bow* bow)
{
	m_strName = bow->m_strName;
	m_iDamage = bow->m_iDamage;
	m_iprice = bow->m_iprice;
	m_Type = bow->m_Type;
}

Bow::Bow(string name, int Damage, int Gold)
{
	m_strName = name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_BOW;
}
int Bow::Weaponeffect(int number, bool& bRamdomeffect)
{//Ȯ���� 2Ÿ  ���Ⱑ 5���� Ȯ�� ������10��,20��,30��,40��,50��
	int weaponeffect = rand() % 100 + 1; //����
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
	cout << "ġ��Ÿ�� �͠����ϴ�.";
}
Bow::~Bow()
{
}
Dagger::Dagger()
{

}
Dagger::Dagger(Dagger* dagger)
{
	m_strName = dagger->m_strName;
	m_iDamage = dagger->m_iDamage;
	m_iprice = dagger->m_iprice;
	m_Type = dagger->m_Type;
}

Dagger::Dagger(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_DAGGER;
}
int Dagger::Weaponeffect(int number, bool& bRamdomeffect)
{//Ȯ���� 2Ÿ  ���Ⱑ 5���� Ȯ�� ������10��,20��,30��,40��,50��
	int weaponeffect = rand() % 100 + 1; //����
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
	cout << "�߰�Ÿ�� ���Ƚ��ϴ�.";
}
Dagger::~Dagger()
{
}

Gun::Gun()
{

}
Gun::Gun(Gun* gun)
{
	m_strName = gun->m_strName;
	m_iDamage = gun->m_iDamage;
	m_iprice = gun->m_iprice;
	m_Type = gun->m_Type;
}


Gun::Gun(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_GUN;
}

int Gun::Weaponeffect(int number, bool& bRamdomeffect)
{//Ȯ���� 2Ÿ  ���Ⱑ 5���� Ȯ�� ������10��,20��,30��,40��,50��
	int weaponeffect = rand() % 100 + 1; //����
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
	cout << "ġ��Ÿ�� �������ϴ�.";
}
Gun::~Gun()
{
}

Hammer::Hammer()
{

}
Hammer::Hammer(Hammer* hammer)
{
	m_strName = hammer->m_strName;
	m_iDamage = hammer->m_iDamage;
	m_iprice = hammer->m_iprice;
	m_Type = hammer->m_Type;
}

Hammer::Hammer(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_HAMMER;
}
int Hammer::Weaponeffect(int number, bool& bRamdomeffect)
{//Ȯ���� 2Ÿ  ���Ⱑ 5���� Ȯ�� ������10��,20��,30��,40��,50��
	int weaponeffect = rand() % 100 + 1; //����
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
	cout << "1�� ���� ������ �ɷȽ��ϴ�.";
}
Hammer::~Hammer()
{
}

Sword::Sword()
{
	m_strName = "�콼 ��";
	m_iDamage = 5;
	m_Type = WEAPON_SWORD;
	m_iprice = 0;
}
Sword::Sword(Sword* sword)
{
	m_strName = sword->m_strName;
	m_iDamage = sword->m_iDamage;
	m_iprice = sword->m_iprice;
	m_Type = sword->m_Type;
}

Sword::Sword(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_SWORD;
}

int Sword::Weaponeffect(int number, bool& bRamdomeffect)
{//Ȯ���� ġ��200��  ���Ⱑ 5���� Ȯ�� ������10��,20��,30��,40��,50��
	int weaponeffect = rand() % 100 + 1; //����
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
	cout << "ũ��Ƽ���� �������ϴ�.";
}
Sword::~Sword()
{
}

Wand::Wand()
{

}
Wand::Wand(Wand* wand)
{
	m_strName = wand->m_strName;
	m_iDamage = wand->m_iDamage;
	m_iprice = wand->m_iprice;
	m_Type = wand->m_Type;
}

Wand::Wand(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iprice = Gold;
	m_Type = WEAPON_WAND;
}
int Wand::Weaponeffect(int number, bool& bRamdomeffect)
{//Ȯ����ȸ��  ���Ⱑ 5���� Ȯ�� ������10��,20��,30��,40��,50��
	int weaponeffect = rand() % 100 + 1; //����
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
	cout << "2Ÿ�� ���Ƚ��ϴ�.";
}
Wand::~Wand()
{
}


