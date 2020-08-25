#pragma once
#include"Mecro.h"
#include <iomanip>
#include"Weapon.h"
#include"MapDraw.h"

class Inventory
{
	Inventory* parent;
	const string name;
	bool m_bCheckPage;
public:
	Inventory(string name);
	MapDraw map;
	
	virtual void View(int x,int y) = 0;
	virtual void AddInventory(Inventory* inventory) = 0;
	virtual void RemoveInventory(Inventory* inventory) = 0;

	void SetParent(Inventory* _parent);
	Inventory* GetParent();
	string GetName();
	void Checkpage(bool check);
	bool Check()
	{
		return m_bCheckPage;
	}
	int GetLevel();
protected:
	int GetSize();
};

class Item : public Inventory
{
	Weapon* weaponlist;
	string m_iMoney;
public:
	Item(string name,Weapon* weapon);
	Item(string name, int money);
	void View(int x,int y)override;
	void AddInventory(Inventory* inventory) {};
	void RemoveInventory(Inventory* inventory) {};

};

class Bag : public Inventory
{
	
	vector<Inventory*> inventoryList;
public:
	Bag(string name);
	~Bag();

	void View(int x,int y)override;
	void AddInventory(Inventory* inventory) override;
	void RemoveInventory(Inventory* inventory) override;
};