#pragma once
#include"Mecro.h"
#include"MapDraw.h"
//���� ��ȣ ������ �޾� ������ ����
class Weapon
{
protected:
	int m_iDamage;//������
	string m_strName;//�̸�
	WEAPON m_Type;//Ÿ��
	string m_strType;
	int m_iprice;//���
	MapDraw* map;
public:
	virtual void ShowWeaponeffect() = 0;
	virtual int Weaponeffect(int number, bool& bRamdomeffect) = 0;//����ȿ��
	Weapon(int Damage, string Name, WEAPON type, int price);
	Weapon();
	void ShowInfo(int x,int y);
	int WeaponGold();
	int weaponAttack();
	string WeaponName();
	inline WEAPON WeaponType()
	{
		return m_Type;
	}
	virtual ~Weapon();
};

class Bow : public Weapon
{
public:
	virtual int Weaponeffect(int number, bool& bRamdomeffect);
	virtual void ShowWeaponeffect();
	Bow(int Damage, string Name, WEAPON type, int price) : Weapon(Damage, Name, type, price) {}
	Bow(string name,int Damage,int Gold);
//	Bow(Bow* bow);
	Bow();
	virtual ~Bow();
};

class Dagger : public Weapon
{
public:
	virtual int Weaponeffect(int number, bool& bRamdomeffect);
	virtual void ShowWeaponeffect();
	Dagger(int Damage, string Name, WEAPON type, int price) : Weapon(Damage, Name, type, price) {}
	Dagger(string name, int Damage, int Gold);
//	Dagger(Dagger* dagger);
	Dagger();
	virtual ~Dagger();
};

class Gun : public Weapon
{
public:
	virtual int Weaponeffect(int number, bool& bRamdomeffect);
	virtual void ShowWeaponeffect();
	Gun(int Damage, string Name, WEAPON type, int price) : Weapon(Damage, Name, type, price) {}
	Gun(string name, int Damage, int Gold);
//	Gun(Gun* gun);
	Gun();
	virtual ~Gun();
};


class Hammer : public Weapon
{
private:
	int RanDowmHammer;
	int Hammercount;
	int fistHammer;
public:
	virtual int Weaponeffect(int number, bool& bRamdomeffect);
	virtual void ShowWeaponeffect();
	Hammer(int Damage, string Name, WEAPON type, int price) : Weapon(Damage, Name, type, price) {}
	Hammer(string name, int Damage, int Gold);
//	Hammer(Hammer* hammer);
	Hammer();
	virtual ~Hammer();
};

class Sword : public Weapon
{
private:
	int RanDowmSword;
	int Swordcount;
	int fistSword;
public:
	virtual int Weaponeffect(int number, bool& bRamdomeffect);
	virtual void ShowWeaponeffect();
	Sword(int Damage, string Name, WEAPON type, int price) : Weapon(Damage, Name, type, price) {}
	Sword(string name, int Damage, int Gold);
//	Sword(Sword* sword);
	Sword();
	virtual ~Sword();
};

class Wand : public Weapon
{
private:
	int RanDowmWand;
	int Wandcount;
	int fistWand;
public:
	virtual int Weaponeffect(int number, bool& bRamdomeffect);
	virtual void ShowWeaponeffect();
	Wand(int Damage, string Name, WEAPON type, int price) : Weapon(Damage, Name, type, price) {}
	Wand(string name, int Damage, int Gold);
//	Wand(Wand* sword);
	Wand();
	virtual ~Wand();
};