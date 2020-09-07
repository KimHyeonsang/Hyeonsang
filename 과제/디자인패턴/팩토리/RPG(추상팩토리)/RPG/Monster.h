#pragma once
#include"Mecro.h"
#include"MapDraw.h"
typedef struct Monsters
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
}monsters;

class Monster
{
private:
	monsters* mster[100];
	int monstercounts;
	MapDraw map;
public:
	void LoadMonster(char* buf);
	void showMonster(int x, int y, int i);
	void Reset();
	void Damage(int power, int select);
	void RegetHp(int select);
	void Save(char* buf);
	void Victory(int x, int y, int Experience, int select);
	inline int monstercount()
	{
		return monstercounts;
	}
	inline int power(int number)
	{
		return mster[number]->power;
	}
	inline int Current_health(int number)
	{
		return mster[number]->Current_health;
	}
	inline int Earned_Experience(int number)
	{
		return mster[number]->Earned_Experience;
	}
	inline int money(int number)
	{
		return mster[number]->Gold;
	}
	Monster();
	~Monster();
};

