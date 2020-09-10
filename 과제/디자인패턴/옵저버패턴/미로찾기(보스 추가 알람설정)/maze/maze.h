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
	vector<int>character; //ĳ����
	vector<vector<int>>Entry_Potal;//�Ա���Ż
	vector<vector<int>>Exit_Potal;//�ⱸ��Ż
	vector<vector<int>>button;//����ġ
	vector<vector<int>>door;//�����¹�
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