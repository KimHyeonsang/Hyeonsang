#pragma once
#include"Player.h"

class PlayerFactory
{
	vector<Player*> jobs;
	vector<Weapon*> weapons;
public:
	virtual Weapon* CreateWeapon() = 0;
	virtual Player* CreateJobClass() = 0;
	~PlayerFactory();
protected:
	void Addjob(Player* job);
	void AddWeapon(Weapon* weapon);
};

class KnightCharacter : public PlayerFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Player* CreateJobClass();
};

class ArcherCharacter : public PlayerFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Player* CreateJobClass();
};

class WizardCharacter : public PlayerFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Player* CreateJobClass();
};

class AssassinCharacter : public PlayerFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Player* CreateJobClass();
};

