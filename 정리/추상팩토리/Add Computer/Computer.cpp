#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

void Computer::Setting(Keybord *_keybord, Mouse * _mouse)
{
	keybord = _keybord;
	mouse = _mouse;
}

Keybord *Computer::Getkeybord()
{
	return keybord;
}

Mouse *Computer::Getmouse()
{
	return mouse;
}

void SamsangComputer::checkking()
{
	samsangKeybord* samsangkeybord = dynamic_cast<samsangKeybord*>(Getkeybord());
	samsangMouse* samsangmouse = dynamic_cast<samsangMouse*>(Getmouse());

	if (samsangkeybord == NULL && samsangmouse == NULL)
		return;

	cout << "samsang �귣�带 ����ϰ� �ֽ��ϴ�." << endl;

	samsangkeybord->addkeybord();
	samsangmouse->addmouse();
}

void LGComputer::checkking()
{
	samsangKeybord* LGkeybord = dynamic_cast<samsangKeybord*>(Getkeybord());
	samsangMouse* LGmouse = dynamic_cast<samsangMouse*>(Getmouse());

	if (LGkeybord == NULL && LGmouse == NULL)
		return;

	cout << "LG �귣�带 ����ϰ� �ֽ��ϴ�." << endl;

	LGkeybord->addkeybord();
	LGmouse->addmouse();
}

void appleComputer::checkking()
{
	samsangKeybord* applekeybord = dynamic_cast<samsangKeybord*>(Getkeybord());
	samsangMouse* applemouse = dynamic_cast<samsangMouse*>(Getmouse());

	if (applekeybord == NULL && applemouse == NULL)
		return;

	cout << "���� �귣�带 ����ϰ� �ֽ��ϴ�." << endl;

	applekeybord->addkeybord();
	applemouse->addmouse();
}