#pragma once
#include"mecro.h"
#include"Alarm.h"
#include"MapDraw.h"


#define POTAL_MAX 4

class maze
{
private:
	MapDraw mapdraw;
	vector<vector<int>>map;
	vector<int>arr;
	vector<int>character; //캐릭터
	vector<vector<int>>Entry_Potal;//입구포탈
	vector<vector<int>>Exit_Potal;//출구포탈
	vector<vector<int>>button;//스위치
	vector<vector<int>>door;//열리는문
	vector<int>Boss;
	int LastObjectIndex;
	bool m_bGameClear;
	int start;
	int m_iBoss_x;
	int m_iBoss_y;
	BossDragon* Golem;
	Player* player1;
	bool m_bBoss;
public:
	maze();
	~maze();
	void MapDraw();
	void Game();
	void mapinit();
	void Map();
	void Move();
	void MoveCheck();
	void End_Game();
	void replay();
	void respown();
	void alarm();
};