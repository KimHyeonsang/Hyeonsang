#include "JobClass.h"

/* JobClass */
void JobClass::SetWeapon(Weapon * _weapon)
{
	weapon = _weapon;
}

Weapon * JobClass::GetWeapon()
{
	return weapon;
}

/* Knight */
bool Knight::EquipCheck()
{
	Sword* sword = dynamic_cast<Sword*>(GetWeapon());

	if (sword == NULL)
		return false;

	cout << "°Ë Âø¿ë!" << endl;

	return 0; //sword->Attack();
}

/* Archer */
bool Archer::EquipCheck()
{
	Bow* bow = dynamic_cast<Bow*>(GetWeapon());

	if (bow == NULL)
		return false;

	cout << "È° Âø¿ë!" << endl;

	return 0;//bow->Attack();
}

/* Wizard */
bool Wizard::EquipCheck()
{
	Wand* wand = dynamic_cast<Wand*>(GetWeapon());

	if (wand == NULL)
		return false;

	cout << "ÁöÆÎÀÌ Âø¿ë!" << endl;

	return 0;// wand->Attack();
}