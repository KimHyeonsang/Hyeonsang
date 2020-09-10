#pragma once
#include<iostream>
#include<vector>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<string>
using namespace std;

#define HEIGHT 15
#define WIDTH 15
/////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
///////////////////////////////////////////////////////////


enum Map  //이동키 70번떄 포탈
{
	PLAYER = 1,
	ITEM_MAX,
	TRAP_NUMBER,
	TRAP2,
	WALL = 6,
	WALL2,
	BOSS = 20,
	TRAP = 30,
	BUTTON = 40,
	DOOR = 50,
	ENTRY_START = 60,
	EXIT_START =70,
	END_GAME = 100
};

enum PLAYERKEY
{
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
	SPACE = 32,
	ESC = 27
};