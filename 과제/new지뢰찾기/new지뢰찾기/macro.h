#pragma once
#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include<string>
#include<conio.h>
#include<time.h>
using namespace std;
#define WIDTH 11
#define HEIGHT 11
#define PLAYER_X_MOVE 2
#define PLAYER_Y_MOVE 1
enum MAPSIZE
{
	MAPSIZE_WIDTH = WIDTH * 2,
	MAPSIZE_HIGHT = HEIGHT + 1,
	MAPSIZE_COUNT = (WIDTH - 1) * (HEIGHT - 1) / 4
};
enum MAPPACKGE
{
	MAPPACKGE_BOOM = 9,
	MAPPACKGE_OUTBOX,
	MAPPACKGE_CHARATER
};