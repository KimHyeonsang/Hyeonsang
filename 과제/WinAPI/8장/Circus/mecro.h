#pragma once
#include<windows.h>
#include<vector>
using namespace std;

#define FINISH 9
#define RANDOM 1
#define CRASH_TIME 50
enum fire_State
{
	burn1,
	burn2
};

enum State //����
{
	NOMAL,
	WALK1,//������1
	WALK2,//������2
	JUMP, //����
	DIE,
	WIN, //�������� ����1
	WIN2 //�������� ����2
};

enum Direction //����
{
	IDLE,
	LEFT,
	RIGHT
};