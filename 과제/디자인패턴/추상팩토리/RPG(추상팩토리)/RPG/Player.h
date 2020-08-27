#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Weapon.h"
#include"Inventory.h"
typedef struct Player_Info
{
	string name;
	int power;
	int Current_health;//���� ü��
	int Max_health; //�ִ�ü��
	int Current_experience;//���� ����ġ
	int Max_experience;//�ִ� ����ġ
	int Earned_Experience;//ȹ�� ����ġ
	int Level;//����
	int Gold;//��
	int itemnumber;
}player_Info;
class Player
{
private:
	player_Info* info;
	MapDraw map;
	int power_random;
	int health_random;
	bool bWeaponchange;
	Weapon* m_pweapon;
	int number;
	Inventory* inventory;//bag�ȿ� ���� ������ �Է�
	Inventory* Daggerbag;
	Inventory* Bowbag;
	Inventory* Gunbag;
	Inventory* Wandbag;
	Inventory* Swordbag;
	Inventory* Hammerbag;
	Inventory* Money;
	Player* knight;
	Player* assassin;
	Player* wizard;
	Player* archer;
public:
	virtual bool EquipCheck() = 0;
	void showplayer(int x, int y);
	void SetName(string str);
	void LoadPlayer(char* buf);
	void Reset();
	void Damage(int power);
	void Save(char* buf, int number);
	void Victory(int x, int y, int Experience, int Gold);
	void ResetHp();
	void Buy(Weapon* newweapon, WEAPON Type);
	int weaponeffect(bool& bRamdomeffect);
	void showeffect();
	void finalweapon();
	void invenview(int x,int y);
	void SetWeapon(Weapon* _weapon);
	void JobSelect(int select);
	void showweapon(int x, int y);
	inline string playername()
	{
		return info->name;
	}
	inline int power()
	{
		if (info->itemnumber == 0)
			return info->power;
	}
	inline int Earned_Experience()
	{
		return info->Earned_Experience;
	}
	inline int Current_health()
	{
		return info->Current_health;
	}
	inline int Gold()
	{
		return info->Gold;
	}
	Player();
	~Player();
protected:
	Weapon* GetWeapon();
};

class Knight : public Player
{
public:
	virtual bool EquipCheck();
};

class Archer : public Player
{
public:
	virtual bool EquipCheck();
};

class Wizard : public Player
{
public:
	virtual bool EquipCheck();
};

class Assassin : public Player
{
public:
	virtual bool EquipCheck();
};