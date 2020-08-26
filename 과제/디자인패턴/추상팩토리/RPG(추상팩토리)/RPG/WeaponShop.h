#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Weapon.h"
#include"Player.h"
//公扁 府胶飘 包府
enum WEAPONLIST
{
	WEAPONLIST_DAGGER,
	WEAPONLIST_GUN,
	WEAPONLIST_SWORD,
	WEAPONLIST_WAND,
	WEAPONLIST_BOW,
	WEAPONLIST_HAMMER
};
class WeaponShop
{
private:
	int totalcount[6];
	int firstweapon[6];
	int Endweaponnumber;
	MapDraw map;
	bool bDaggerMenu;
	int m_iweaponNumber;
	Weapon* weaponlist;
	bool bWeaponchange;
	vector<Weapon*> m_vector;
	vector<Weapon*>::iterator m_iter;
public:
	WeaponShop();
	void NomaltopMenu(int Gold);
	void showweaponNemnnu(bool& bweaponUse, WEAPON  Type, Player* player);
//	void ShowSelect(int Select);
	inline int WeaponNumber()
	{
		return m_iweaponNumber;
	}
	~WeaponShop();
};

