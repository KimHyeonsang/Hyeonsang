#include "Monster.h"



Monster::Monster()
{
	ifstream load;
	int monstercount[1];
	string monstername[100];
	int state[6];
	load.open("DefaultMonster.txt");
	{
		while (!load.eof())
		{
			load >> monstercount[0];
			monstercounts = monstercount[0];
			for (int i = 0; i < monstercount[0]; i++)
			{
				if (mster[i] != NULL)
					mster[i] = NULL;
				mster[i] = new Monsters;
				load >> monstername[i];
				mster[i]->name = monstername[i];
				load >> state[0];
				mster[i]->power = state[0];
				load >> state[1];
				mster[i]->Max_health = state[1];
				load >> state[2];
				mster[i]->Max_experience = state[2];
				load >> state[3];
				mster[i]->Earned_Experience = state[3];
				load >> state[4];
				mster[i]->Level = state[4];
				load >> state[5];
				mster[i]->Gold = state[5];
				mster[i]->Current_experience = 0;
				mster[i]->Current_health = mster[i]->Max_health;
			}
			load.close();
		}
	}
}
void Monster::LoadMonster(char* buf)
{
	ifstream load;
	int monstercount[1];
	string monstername[100];
	int state[8];
	load.open(buf);
	{
		while (!load.eof())
		{
			load >> monstercount[0];
			monstercounts = monstercount[0];
			for (int i = 0; i < monstercount[0]; i++)
			{
				if (mster[i] != NULL)
					mster[i] = NULL;
				mster[i] = new Monsters;
				load >> monstername[i];
				mster[i]->name = monstername[i];
				load >> state[0];
				mster[i]->power = state[0];
				load >> state[1];
				mster[i]->Max_health = state[1];
				load >> state[2];
				mster[i]->Max_experience = state[2];
				load >> state[3];
				mster[i]->Earned_Experience = state[3];
				load >> state[4];
				mster[i]->Level = state[4];
				load >> state[5];
				mster[i]->Gold = state[5];
				load >> state[6];
				mster[i]->Current_experience = state[6];
				load >> state[7];
				mster[i]->Current_health = state[7];
			}
			load.close();
		}
	}
}
void Monster::showMonster(int x, int y, int i)
{
	map.gotoxy(x, y);
	cout << "      =======" << mster[i]->name << "< " << mster[i]->Level << "Lv>=====";
	y++;
	map.gotoxy(x, y);
	cout << "공격력 = " << mster[i]->power << "\t" << "생명력 = " << mster[i]->Current_health << " / " << mster[i]->Max_health;
	y++;
	map.gotoxy(x, y);
	cout << "경험치 = " << mster[i]->Current_experience << " / " << mster[i]->Max_experience << "\t" << "GerExp = " << mster[i]->Earned_Experience;
	y++;
	map.gotoxy(x, y);
	cout << "Gold = " << mster[i]->Gold;
	y++;
	cout << endl;
}
void Monster::Reset()
{
	for (int i = 0; i < monstercounts; i++)
	{
		delete mster[i];
		if (mster[i] != NULL)
			mster[i] = NULL;
	}
}
void Monster::Save(char* buf)
{
	ofstream SaveMonster;
	SaveMonster.open(buf);
	if (SaveMonster.is_open())
	{
		SaveMonster << monstercounts << endl;
		for (int i = 0; i < monstercounts; i++)
		{
			SaveMonster << mster[i]->name << " ";
			SaveMonster << mster[i]->power << " ";
			SaveMonster << mster[i]->Max_health << " ";
			SaveMonster << mster[i]->Max_experience << " ";
			SaveMonster << mster[i]->Earned_Experience << " ";
			SaveMonster << mster[i]->Level << " ";
			SaveMonster << mster[i]->Gold << " ";
			SaveMonster << mster[i]->Current_experience << " ";
			SaveMonster << mster[i]->Current_health << endl;
		}
		SaveMonster.close();
	}
}
void Monster::Damage(int power, int select)//데미지 받기
{
	mster[select]->Current_health -= power;
}
void Monster::RegetHp(int select)
{
	mster[select]->Current_health = mster[select]->Max_health;
}
void Monster::Victory(int x, int y, int Experience, int select)
{
	map.gotoxy(x, y);
	RED
		cout << "      " << mster[select]->name << "  승리!!";
	y += 2;
	map.gotoxy(x, y);
	cout << mster[select]->name << "가 경험치 " << Experience << "를 얻었습니다.";
	ORIGINAL
		y += 2, x += 5;
	map.gotoxy(x, y);
	cout << "플레이어 패배";
	mster[select]->Current_experience += Experience;
	map.gotoxy(-1, -1);
	system("pause>null");
}
Monster::~Monster()
{
	for (int i = 0; i < monstercounts; i++)
	{
		delete mster[i];
		if (mster[i] != NULL)
			mster[i] = NULL;
	}
}
