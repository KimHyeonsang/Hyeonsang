#pragma once
#include"macro.h"
#include"Interface.h"
typedef struct Ranking 
{
	string str_Name;
	int m_iStage;
	int m_iScore;
}ranking;

class Rank
{
private:
	int m_iRanknumber;
	Interface in_face;
	ranking* rankking;
	list<ranking*> List;
	list<ranking*>::iterator iter;
public:
	Rank();
	void setRanking(string name, int stage, int score);
	void retry();
	void Ranking();
	void Rankingsystem(int m_iWith, int m_iHeight);
	~Rank();
};

