
#include "Ward.h"
#include"WardManager.h"
#include"GameManager.h"
//단어를 생성할때 랜덤확률을 주어서 단어가 아이템을 가지고 나가는지 아니면 일반인지

Ward::Ward(string ward)
{
	m_bSet = false;
	m_idroptime = 1000;
	m_icurrentTime = clock();
	m_strWard = ward;
	m_iy = 1;
	effectward = false;
	char m_ch[256];
	for (int i = 0; i < m_strWard.length(); i++)
	{
		m_ch[i] = '=';
		m_strblindWard += m_ch[i];
	}
}
Ward::Ward()
{
}
void Ward::InfoWard()//위치,아이템셋팅
{
	int set_x = WIDTH;
	if (rand() % 4 == 0)
	{
		in_face.Setcolor(LIGHTGREEN, DARKGRAY);
		wardEffet = (WARDEFFET)(rand() % WARDEFFET_END);
	}
	else
	{
		in_face.Setcolor(BLUE, DARKGRAY);
		wardEffet = WARDEFFET_NORMAL;
	}
	int length = m_strWard.length() / 2; //길이 
	while (1)
	{
		m_ix = rand() % (set_x * 2); //좌표
		if (m_ix - length > 1 && m_ix + length < (set_x * 2))
			break;
	}
	m_strtmpWard = m_strWard;
	m_bSet = true;
}

void Ward::drop(bool stopward) //떨어뜨리기
{
	if (m_bSet == true)
	{
		if (clock() - m_icurrentTime >= m_idroptime)
		{
			in_face.Setcolor(DARKGRAY, DARKGRAY);
			in_face.DrawMidText(m_strtmpWard, m_ix, m_iy);
			if (stopward == false)
				m_iy++;
			else
				m_iy;
			if (wardEffet != WARDEFFET_NORMAL)
				in_face.Setcolor(LIGHTGREEN, DARKGRAY);
			else
				in_face.Setcolor(BLUE, DARKGRAY);
			in_face.DrawMidText(m_strtmpWard, m_ix, m_iy);
			m_icurrentTime = clock();
		}
	}
}
bool Ward::Die(int Height, string str, WardManager* wardmanager, GameManager* GM)//단어를 맞추어 사라지기
{
	m_WardManager = wardmanager;
	if (str == m_strWard)
	{
		ReSetWard();
		if (wardEffet != WARDEFFET_NORMAL)
			m_WardManager->ActivateItemEffect(wardEffet, GM);//효과발동
		return true;
	}
	else
		return false;
}
void Ward::Live(int Height)//끝까지 살아남는것
{
	if (m_iy == Height - 2)
	{
		ReSetWard();
	}
}
void Ward::dropUp(int number) //속도 올려서 초기화
{
	if (m_idroptime > 500)
	{
		m_idroptime -= number;
	}
	ReSetWard();
}

bool Ward::ReSetWard()//초기화
{
	if (m_bSet == true)
	{
		in_face.Setcolor(DARKGRAY, DARKGRAY);
		in_face.DrawMidText(m_strtmpWard, m_ix, m_iy);
		m_iy = 1;
		m_bSet = false;
		return true;
	}
	else
		return false;
}
bool Ward::lifeless(int Height)
{
	if (m_iy == Height - 2)
	{
		return true;
	}
}

void Ward::speedchange(bool speed)//속도
{
	if(speed == true)
		m_idroptime -= 20;
	else
		m_idroptime += 20;
}

void Ward::Reback(WardManager* wardmanager)//일정시간이 지나면 아이템 효과를 되돌린다
{
	m_WardManager = wardmanager;
	if(wardEffet != WARDEFFET_CLEAR)
		m_WardManager->ItemEffectOff(wardEffet);
}
void Ward::blindward(bool blind)//단어 가리기
{
	if (blind == true)
	{
		m_strtmpWard = m_strblindWard;
	}
	else
	{
		m_strtmpWard = m_strWard;
	}
}


Ward::~Ward()
{
}
