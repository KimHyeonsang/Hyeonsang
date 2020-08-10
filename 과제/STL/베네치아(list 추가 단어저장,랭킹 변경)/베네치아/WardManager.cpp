#include "WardManager.h"
#include"GameManager.h"
//워드한테 명령만 한다 떨궈라 그려라 등 워드들을 들고있다
//이건 웨펀샵이 웨펀들을 관리하는거랑 같다
//단어 클래스를 배열로 할당하고 거기에 불러온걸 넣는다

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
			ward = new Ward(strWard); //불러온 단어들을 단어에저장
			List.push_back(ward); //불러온 단어들 저장			
		}
		wardLoad.close();
	}
}

void WardManager::SettingWard()  //단어 셋팅
{
	if (clock() - startward >= 3000) //3초마다
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
void WardManager::dropward() //단어 떨어뜨리기
{
	
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		ward->drop(m_bspeedstop);
	}
}
bool WardManager::Dies(int Height, string str, GameManager* game) //단어 맞추고 단어지움
{
	GM = game;
	int num = 0;
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		num++;
		if (ward->Die(Height, str, this, GM) == true)
		{
			m_inumber = num;  //지워진 단어의 숫자를 저장   m_inumber을 저장이 그단어의 위치를 나타낼려고한다.  i는 true의 참이 되는 번호
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
void WardManager::LevelUp(int number)//스테이지상승
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
void WardManager::reset() //단어 리셋
{
	for (iter = List.begin(); iter != List.end(); ++iter)
	{
		ward = *iter;
		ward->ReSetWard();
	}
}
void WardManager::ActivateItemEffect(WARDEFFET Effet, GameManager* game)//아이템효과발동
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

	List.clear(); // 저장된거 제거
}
