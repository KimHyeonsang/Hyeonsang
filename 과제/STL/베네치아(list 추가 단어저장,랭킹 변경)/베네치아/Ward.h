#pragma once
#include"macro.h"
#include"Interface.h"

class GameManager;
class WardManager;
class Ward
{
private:
	int m_ix;
	int m_iy;
	string m_strWard; //단어
	Interface in_face;
	bool m_bSet; //단어그려진지아닌지
	int m_idroptime;
	int m_icurrentTime;
	bool effectward;
	WardManager * m_WardManager;
	WARDEFFET wardEffet;
	string m_strtmpWard;  
	string m_strblindWard; // 블라인드 단어 저장
public:
	void drop(bool stopward);//떨어뜨리기
	void Live(int Height); //>? 살아이쓴ㄴ거 내려가기
	bool Die(int Height, string str, WardManager* wardmanager, GameManager* GM); //죽기
	void dropUp(int number);
	bool ReSetWard();
	bool lifeless(int Height);
	Ward(string ward);
	void speedchange(bool speed);
	void Reback(WardManager* wardmanager); // 느려지면 몇초뒤 빨라지기
	void blindward(bool blind);
	void InfoWard();
	inline bool Setting()
	{
		return m_bSet;
	}
	inline string strWard()
	{
		return m_strWard;
	}
	Ward();
	~Ward();
};

