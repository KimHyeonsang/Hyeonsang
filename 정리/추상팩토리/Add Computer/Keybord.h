#pragma once
#include<iostream>
using namespace std;

class Keybord
{
public:
	virtual bool addkeybord() = 0;
};

class appleKeybord :public Keybord
{
public:
	virtual bool addkeybord();
};

class samsangKeybord :public Keybord
{
public:
	virtual bool addkeybord();
};

class LGKeybord :public Keybord
{
public:
	virtual bool addkeybord();
};
