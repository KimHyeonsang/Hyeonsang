#include "PlayerFactory.h"


PlayerFactory::~PlayerFactory()
{
	jobs.clear();
	weapons.clear();
}

void PlayerFactory::Addjob(Player * job)
{
	jobs.push_back(job);
}

void PlayerFactory::AddWeapon(Weapon * weapon)
{
	weapons.push_back(weapon);
}

/* Knight Character */
Weapon * KnightCharacter::CreateWeapon()
{
	return new Sword();
}

Player * KnightCharacter::CreateJobClass()
{
	return new Knight();
}

/* Archer Character */
Weapon * ArcherCharacter::CreateWeapon()
{
	return new Bow();
}

Player * ArcherCharacter::CreateJobClass()
{
	return new Archer();
}

/* Wizard Character */
Weapon * WizardCharacter::CreateWeapon()
{
	return new Wand();
}

Player * WizardCharacter::CreateJobClass()
{
	return new Wizard();
}

Player * AssassinCharacter::CreateJobClass()
{
	return new Assassin();
}
Weapon * AssassinCharacter::CreateWeapon()
{
	return new Dagger();
}
