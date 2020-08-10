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
	string m_strWard; //�ܾ�
	Interface in_face;
	bool m_bSet; //�ܾ�׷������ƴ���
	int m_idroptime;
	int m_icurrentTime;
	bool effectward;
	WardManager * m_WardManager;
	WARDEFFET wardEffet;
	string m_strtmpWard;  
	string m_strblindWard; // ����ε� �ܾ� ����
public:
	void drop(bool stopward);//����߸���
	void Live(int Height); //>? ����̾����� ��������
	bool Die(int Height, string str, WardManager* wardmanager, GameManager* GM); //�ױ�
	void dropUp(int number);
	bool ReSetWard();
	bool lifeless(int Height);
	Ward(string ward);
	void speedchange(bool speed);
	void Reback(WardManager* wardmanager); // �������� ���ʵ� ��������
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

