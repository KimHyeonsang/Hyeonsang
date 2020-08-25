#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Weapon.h"
#include"Inventory.h"
#include"JobClass.h"
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
	Weapon* m_pweapon;
	int number;
	Inventory* inventory;//bag안에 무기 정보를 입력
	Inventory* Daggerbag;
	Inventory* Bowbag;
	Inventory* Gunbag;
	Inventory* Wandbag;
	Inventory* Swordbag;
	Inventory* Hammerbag;
	Inventory* Money;
public:
	void showplayer(int x, int y, Weapon* hm);
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
};


class CharacterFactory
{
	vector<JobClass*> jobs;
	vector<Weapon*> weapons;

public:
	~CharacterFactory();

	virtual Weapon * CreateWeapon() = 0;
	virtual JobClass* CreateJobClass() = 0;

protected:
	void AddJob(JobClass* job);
	void AddWeapon(Weapon* weapon);

};

class KnightCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass* CreateJobClass();
};

class ArcherCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass* CreateJobClass();
};

class WizardCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass* CreateJobClass();
};

class shipCharactor :public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass* CreateJobClass();
};