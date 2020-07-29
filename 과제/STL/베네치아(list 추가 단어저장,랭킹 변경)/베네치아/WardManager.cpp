#include "WardManager.h"
#include"GameManager.h"
//�������� ��ɸ� �Ѵ� ���Ŷ� �׷��� �� ������� ����ִ�
//�̰� ���ݼ��� ���ݵ��� �����ϴ°Ŷ� ����
//�ܾ� Ŭ������ �迭�� �Ҵ��ϰ� �ű⿡ �ҷ��°� �ִ´�

WardManager::WardManager()
{
	m_bspeedchange = false;
	m_bspeedstop = false;
	m_bclear = false;
	m_bwardblind = false;
	startward = clock();
	m_iWardnumber = 0;
	Scorecount = 0;
	ifstream wardLoad;
	wardLoad.open("Word.txt");
	if (wardLoad.is_open())
	{
		wardLoad >> m_iWardnumber;
		while (wardLoad.eof() == false)
		{
			wardLoad >> strWard;
			ward = new Ward(strWard); //�ҷ��� �ܾ���� �ܾ����
			List.push_back(ward); //�ҷ��� �ܾ�� ����			
		}
		wardLoad.close();
	}
}

void WardManager::SettingWard()  //�ܾ� ����
{
	if (clock() - startward >= 3000) //3�ʸ���
	{
		while (1)
		{
			iter = List.begin();
			int Randomnumber = rand() % m_iWardnumber;
			for (int i = 0; i < Randomnumber; i++)
				++iter;
			ward = *iter;
			if (ward->Setting() == false)
			{
				ward->InfoWard();
				startward = clock();
				break;
			}
		}
	}
}
void WardManager::dropward() //�ܾ� ����߸���
{
	
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		ward->drop(m_bspeedstop);
	}
}
bool WardManager::Dies(int Height, string str, GameManager* game) //�ܾ� ���߰� �ܾ�����
{
	GM = game;
	int num = 0;
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		num++;
		if (ward->Die(Height, str, this, GM) == true)
		{
			m_inumber = num;  //������ �ܾ��� ���ڸ� ����   m_inumber�� ������ �״ܾ��� ��ġ�� ��Ÿ�������Ѵ�.  i�� true�� ���� �Ǵ� ��ȣ
			itemtme = clock();
			return true;
		}
	}
	return false;
}
void WardManager::wardLive(int Height)
{
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		ward->Live(Height);
	}
	
}
void WardManager::LevelUp(int number)//�����������
{
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		ward->dropUp(number);
	}
		
}
bool WardManager::lifeless(int Height)
{
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		if (ward->lifeless(Height) == true)
			return true;
	}
}
void WardManager::reset() //�ܾ� ����
{
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		ward->ReSetWard();
	}
}
void WardManager::ActivateItemEffect(WARDEFFET Effet, GameManager* game)//������ȿ���ߵ�
{
	GM = game;
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		if (Effet == WARDEFFET_SLOW)
		{
			m_bspeedchange = true;
			ward->speedchange(m_bspeedchange);
		}
		else if (Effet == WARDEFFET_FAST)
		{
			m_bspeedchange = false;
			ward->speedchange(m_bspeedchange);
		}
		else if (Effet == WARDEFFET_CLEAR)
		{
			m_bclear = true;
			if (ward->ReSetWard() == true)
			{
				Scorecount++;
				GM->ScoreItem(Scorecount);
				Scorecount = 0;
			}
		}
		else if (Effet == WARDEFFET_STOP)
		{
			m_bspeedstop = true;
			ward->drop(m_bspeedstop);
		}
		else if (Effet == WARDEFFET_BLIND)
		{
			m_bwardblind = true;
			ward->blindward(m_bwardblind);
		}
	}
}
void WardManager::ItemEffectOff(WARDEFFET Effet)
{
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		if (Effet == WARDEFFET_SLOW)
		{
			m_bspeedchange = false;
			ward->speedchange(m_bspeedchange);
		}
		else if (Effet == WARDEFFET_FAST)
		{
			m_bspeedchange = true;
			ward->speedchange(m_bspeedchange);
		}
		else if (Effet == WARDEFFET_STOP)
		{
			m_bspeedstop = false;
			ward->drop(m_bspeedstop);
		}
		else if (Effet == WARDEFFET_BLIND)
		{
			m_bwardblind = false;
			ward->blindward(m_bwardblind);
		}
	}
}
void WardManager::reitem(bool& bEffect)
{
	int i = 0;
	if (clock() - itemtme >= 2000)
	{
		for (iter = List.begin(); iter != List.end(); ++iter)
		{
			i++;
			ward = *iter;
			if (i == m_inumber)
			{
				ward->Reback(this);
				break;
			}
		}
		bEffect = false;
		itemtme = clock();
	}
}
WardManager::~WardManager()
{		
	for each(Ward* ward in List)
	{
		delete ward;
		ward = NULL;
	}

	List.clear(); // ����Ȱ� ����
}
