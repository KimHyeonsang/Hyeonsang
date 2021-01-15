#pragma once
#include<windows.h>
#include<vector>
using namespace std;

enum fire_State
{
	burn1,
	burn2
};

enum State //상태
{
	NOMAL,
	WALK1,//움직임1
	WALK2,//움직임2
	JUMP, //점프
	DIE,
	WIN, //끝났을때 포즈1
	WIN2 //끝났을떄 포즈2
};

enum Direction //방향
{
	IDLE,
	LEFT,
	RIGHT
};