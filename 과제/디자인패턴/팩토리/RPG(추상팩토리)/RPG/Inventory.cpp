#include "Inventory.h"


Inventory::Inventory(string name):name(name)
{
	parent = NULL;
}
void Inventory::SetParent(Inventory * _parent)
{
	parent = _parent;
}

Inventory * Inventory::GetParent()
{
	return parent;
}

string Inventory::GetName()
{
	return name;
}
void Inventory::Checkpage(bool check)
{
	m_bCheckPage = check;
}

int Inventory::GetLevel()
{
	int level = 0;

	Inventory* inventory = GetParent();

	while (inventory != NULL)
	{
		level++;
		inventory = inventory->GetParent();
	}

	return level;
}

int Inventory::GetSize()
{
	return name.size() + GetLevel() * 2;
}
Item::Item(string name,Weapon* weapon):Inventory(name)
{
	weaponlist = weapon;
}
Item::Item(string name, int money) : Inventory(name)
{
	weaponlist = NULL;
	m_iMoney = to_string(money);;
}

void Item::View(int x,int y) //������ ���ýÿ� ����ȿ� ��ǰ ���
{

	if(weaponlist == NULL)
		map.DrawMidText("�� :" + m_iMoney,x *1.65f,y - 3);
	else
		weaponlist->ShowInfo(x, y);//��ǰ�� ����
}

Bag::Bag(string name):Inventory(name)
{

}

Bag::~Bag()
{
	inventoryList.clear();
}

void Bag::View(int x,int y)//������ ����
{	
	 int line = 1;
	 int weaponnumber = 1;
	map.DrawMidText(GetName().c_str(), x , y);
	vector<Inventory*>::iterator begin = inventoryList.begin();
	vector<Inventory*>::iterator end = inventoryList.end();

	while (begin != end) 
	{
		
		if (GetName() == "MainBag")
		{
			(*begin)->View(x, y + line * 3);
			begin++;
		}
		else if (GetName() == "DaggerBag")
		{
			(*begin)->View(x, y + line++ * 3);
			begin++;
		}
		else if (GetName() == "GunBag")
		{
			(*begin)->View(x, y + line++ * 3);
			begin++;
		}
		else if (GetName() == "BowBag")
		{
			(*begin)->View(x, y + line++ * 3);
			begin++;
		}
		else if (GetName() == "WandBag")
		{
			(*begin)->View(x, y + line++ * 3);
			begin++;
		}
		else if (GetName() == "HammerBag")
		{
			(*begin)->View(x, y + line++ * 3);
			begin++;
		}
		else if (GetName() == "SwordBag")
		{
			(*begin)->View(x, y + line++ * 3);
			begin++;
		}
		if (weaponnumber >= 5) //�κ��丮���� �������� ĭ�� �ִ� 5ĭ�̰� �� �̻��϶� ����ĭ���� ������
		{
			getch();
			system("cls");
			weaponnumber = 1;
			line = 1;
		}
		else
			weaponnumber++;
	}
	getch();
	
	system("cls");
}

void Bag::AddInventory(Inventory* inventory)
{

	inventory->SetParent(this);	
	inventoryList.push_back(inventory);
}

void Bag::RemoveInventory(Inventory* inventory)
{
	vector<Inventory*>::iterator remove = find(inventoryList.begin(), inventoryList.end(), inventory);

	if (remove != inventoryList.end())
	{
		inventoryList.erase(remove);
	}
}
