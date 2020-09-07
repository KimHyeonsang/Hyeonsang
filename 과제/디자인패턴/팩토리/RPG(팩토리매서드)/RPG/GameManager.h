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
	Monster Ms;
	WeaponShop shop;
	bool bLoad;
	bool bSave;
	bool bLoadfile;
	bool bPlayerwin;
	bool bDraw;
	bool bPlayerLose;
	bool batte;
	bool BattleESC;
	bool bRamdomeffect;
	bool m_bshopopen;
	bool bWeaponchange;
public:
	/*static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;

		return m_hThis;
	}*/
	inline bool Battle()
	{
		return BattleESC;
	}
	inline bool Shop()
	{
		return m_bshopopen;
	}
	bool Load()
	{
		return bLoad;
	}
	void Loadfile(bool check)
	{
		bLoadfile = check;
	}
	void LoadSave();
	void Load(char* buf, int Select, char* buf2);
	void Save(char* buf, int Select, char* buf2);
	void Dangan(bool batteselect);
	void monsterbatte(int Select, bool batteselect);
	void Rock_Paper_Scissors(int Playerkey, int Monsterrandom, int Select, bool batteselect);
	void weaponShop();
	void SelectJob();
	void Different_profession();
	void Playinfo();
	void Monsterinfo();
	void playerinveninfo();
	GameManager();
	~GameManager();

	virtual void Initialized();
	virtual void Menu();
	virtual void Finished();
	virtual int mapSelect(int MenuLen, int AddCol, int x, int y);
protected:
	MapDraw* map;
	Player* player;
	virtual MapDraw* CreateMenu() = 0;
};

class firstMenu :public GameManager //ù��° �޴�
{
protected:
	virtual MapDraw* CreateMenu();
};

class JobManager :public GameManager //������ �Ŵ���
{
protected:
	virtual MapDraw* CreateMenu();
};

class MainMenuManager :public GameManager //�� �̸�
{
protected:
	virtual MapDraw* CreateMenu();
};

class DanganMenuManager :public GameManager //���� �޴�
{
protected:
	virtual MapDraw* CreateMenu();
};

class ShopMenuManager :public GameManager //���⼥
{
protected:
	virtual MapDraw* CreateMenu();
};
