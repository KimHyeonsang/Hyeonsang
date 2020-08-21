#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Monster.h"
#include"Player.h"
#include"WeaponShop.h"
#define ROCK 2
#define SCISSORS 1
#define PAPER 3


class GameManager
{
private:
	static GameManager* m_hThis;
	MapDraw map;
	Monster Ms;
	Player* player;
	WeaponShop shop;
	bool bLoad;
	bool bSave;
	bool bLoadfile;
	bool bPlayerwin;
	bool bDraw;
	bool bPlayerLose;
	bool batte;
	bool batteselect;
	bool bRamdomeffect;
	bool bweaponUse;
	bool bWeaponchange;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;

		return m_hThis;
	}
	bool Load()
	{
		return bLoad;
	}
	void Loadfile(bool check)
	{
		bLoadfile = check;
	}
	void NewGame();
	void GameMenu();
	void LoadSave();
	void Load(char* buf, int Select, char* buf2);
	void Save(char* buf, int Select, char* buf2);
	void Dangan();
	void monsterbatte(int Select);
	void Rock_Paper_Scissors(int Playerkey, int Monsterrandom, int Select);
	void weaponShop();
	GameManager();
	~GameManager();
};

