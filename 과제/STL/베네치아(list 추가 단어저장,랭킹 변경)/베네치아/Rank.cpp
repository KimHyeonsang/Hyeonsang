#include "Rank.h"



Rank::Rank()
{
	m_iRanknumber = 0;
}

struct Greater
{
	bool operator()(ranking* left, ranking* right)
	{
		return left->m_iScore > right->m_iScore;
	}
};

void Rank::setRanking(string name, int stage, int score)//��ũ����
{
	ofstream RankSave("Rank.txt", ios::app);
	RankSave << endl;
	RankSave << name << " ";
	RankSave << stage << " ";
	RankSave << score;
	RankSave.close();
}
void Rank::Ranking() //��ũ �ҷ�����
{
	string str;
	ifstream RankingLoad;
	string name[1];
	int score[1];
	int stage[1];
	RankingLoad.open("Rank.txt");
	if (RankingLoad.is_open())
	{
		while (RankingLoad.eof() == false)
		{
			getline(RankingLoad, str);
		}
		RankingLoad.close();
	}
	if (rankking != NULL)
		rankking = NULL;
	
	RankingLoad.open("Rank.txt");
	if (RankingLoad.is_open())
	{
		while (RankingLoad.eof() == false)
		{
			rankking = new ranking;
			RankingLoad >> name[0];
			rankking->str_Name = name[0];
			RankingLoad >> stage[0];
			rankking->m_iStage = stage[0];
			RankingLoad >> score[0];			
			rankking->m_iScore = score[0];

			List.push_back(rankking);
		}
		RankingLoad.close();
	}
}
void Rank::Rankingsystem(int m_iWith, int m_iHeight)
{
	system("cls");
	int Height;
	in_face.Setcolor(GREEN, DARKGRAY);
	in_face.BoxDraw(0, 0, m_iWith, m_iHeight); //�׵θ�
	in_face.Setcolor(BLUE, DARKGRAY);
	in_face.BoxDraw(m_iWith, m_iHeight*0.1f, 20, 5);
	in_face.DrawMidText("Ranking", m_iWith, m_iHeight *0.1f + 2);
	in_face.DrawMidText("=========================================================================", m_iWith, m_iHeight *0.2f + 1);
	in_face.DrawMidText("Name", m_iWith * 0.7f, m_iHeight *0.3f);
	in_face.DrawMidText("Score", m_iWith, m_iHeight *0.3f);
	in_face.DrawMidText("Stage", m_iWith * 1.3f, m_iHeight *0.3f);
	Height = m_iHeight *0.3f;

	List.sort(Greater()); //��������

	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		rankking = *iter;
		Height += 2;
		in_face.gotoxy(m_iWith * 0.7f - 2, Height);
		cout << rankking->str_Name << "\t";
		in_face.gotoxy(m_iWith - 2, Height);
		cout << rankking->m_iScore << "\t";
		in_face.gotoxy(m_iWith * 1.3f, Height);
		cout << rankking->m_iStage << endl;
	}
	getch();
	retry();
}

void Rank::retry() //�����Ҵ�����
{
	for each(ranking* rankking in List)
	{
		delete rankking;
	}

	List.clear(); // ����Ȱ� ����
}
Rank::~Rank()
{
	for each(ranking* rankking in List)
	{
		delete rankking;
	}

	List.clear(); // ����Ȱ� ����
}
