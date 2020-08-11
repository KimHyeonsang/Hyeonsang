#pragma once
#include"macro.h"
#include"Interface.h"
#include"WardManager.h"
#include"Rank.h"
#define ENTER 13
#define BACKSPACE 8

class GameManager
{
private:
	static GameManager* m_This;
	Interface in_face;
	string* strStory;
	string Name;
	WardManager ward;
	Rank rank;
	int storycount;
	int m_iWith;
	int m_iHeight;
	bool m_bstory;
	string strtemp;
	string strUser;
	int m_iwardcount;
	int Score;
	bool m_bStop;
	int stoptime;
	bool bstage;  //��������
	int m_istagenumber;
	int life;
	bool bEffect;
	bool m_bchect; //ä���ߺ��̰��ϱ�
	bool m_binterface; //���,�̸�,���� ��ӱ׸��� ����
public:
	static GameManager* GetInstance()
	{
		if (m_This == NULL)
			m_This = new GameManager;
		return m_This;
	}
	void story_setName();
	void gostory();
	char Skip();
	void SetName();
	void underinterface();
	void Play();
	void chetting(int& stagetime);
	void stage(int stagetime);
	void LevelUp(int& stagetime);
	void ScoreItem(int count);
	void reset();
	GameManager();
	~GameManager();
};

