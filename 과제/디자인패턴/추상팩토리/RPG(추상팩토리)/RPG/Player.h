#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Weapon.h"
#include"Inventory.h"


typedef struct Player_Info
{
	string name;
	int power;
	int Current_health;//현재 체력
	int Max_health; //최대체력
	int Current_experience;//현재 경험치
	int Max_experience;//최대 경험치
	int Earned_Experience;//획득 경험치
	int Level;//레벨
	int Gold;//돈
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
	int number;
	Inventory* inventory;//bag안에 무기 정보를 입력
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
	Player* SelectJob(int select);
	void invenview(int x,int y);
	void SetWeapon(Weapon* _weapon);
	inline string playername()
	{
		return info->name;
	}
	inline int power()
	{
		return info->power + m_pweapon->weaponAttack();
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
	inline PLAYERJOB job()
	{
		return playerjob;
	}
	Player();
	~Player();
protected:
	Weapon* GetWeapon();
	Weapon* m_pweapon;
	PLAYERJOB playerjob;
};

class Knight : public Player
{
public:
	Knight();
	virtual bool EquipCheck();
};

class Archer : public Player
{
public:
	Archer();
	virtual bool EquipCheck();
};

class Wizard : public Player
{
public:
	Wizard();
	virtual bool EquipCheck();
};

class Assassin : public Player
{
public:
	Assassin();
	virtual bool EquipCheck();
};