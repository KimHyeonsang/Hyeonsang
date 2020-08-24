#pragma once
#include<iostream>
using namespace std;

class Mouse
{
public:
	Mouse();
	virtual bool addmouse() =0;
	~Mouse();
};
class appleMouse :public Mouse
{
public:
	virtual bool addmouse();
};
class samsangMouse :public Mouse
{
public:
	virtual bool addmouse();
};
class LGMouse :public Mouse
{
public:
	virtual bool addmouse();
};
