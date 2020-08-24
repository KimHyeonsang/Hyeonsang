#pragma once
#include"Keybord.h"
#include"Mouse.h"

class Computer
{
private:
	Keybord* keybord;
	Mouse * mouse;
public:
	Computer();
	void Setting(Keybord* _keybord, Mouse * _mouse);
	virtual void checkking() = 0;
	~Computer();
protected:
	Keybord* Getkeybord();
	Mouse * Getmouse();
};

class SamsangComputer :public Computer
{
public:
	virtual void checkking();
};

class LGComputer :public Computer
{
public:
	virtual void checkking();
};

class appleComputer :public Computer
{
public:
	virtual void checkking();
};

