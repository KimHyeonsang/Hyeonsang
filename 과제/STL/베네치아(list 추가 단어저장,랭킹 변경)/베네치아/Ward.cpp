
#include "Ward.h"
#include"WardManager.h"
#include"GameManager.h"
//�ܾ �����Ҷ� ����Ȯ���� �־ �ܾ �������� ������ �������� �ƴϸ� �Ϲ�����

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
void Ward::InfoWard()//��ġ,�����ۼ���
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
	int length = m_strWard.length() / 2; //���� 
	while (1)
	{
		m_ix = rand() % (set_x * 2); //��ǥ
		if (m_ix - length > 1 && m_ix + length < (set_x * 2))
			break;
	}
	m_strtmpWard = m_strWard;
	m_bSet = true;
}

void Ward::drop(bool stopward) //����߸���
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
bool Ward::Die(int Height, string str, WardManager* wardmanager, GameManager* GM)//�ܾ ���߾� �������
{
	m_WardManager = wardmanager;
	if (str == m_strWard)
	{
		ReSetWard();
		if (wardEffet != WARDEFFET_NORMAL)
			m_WardManager->ActivateItemEffect(wardEffet, GM);//ȿ���ߵ�
		return true;
	}
	else
		return false;
}
void Ward::Live(int Height)//������ ��Ƴ��°�
{
	if (m_iy == Height - 2)
	{
		ReSetWard();
	}
}
void Ward::dropUp(int number) //�ӵ� �÷��� �ʱ�ȭ
{
	if (m_idroptime > 500)
	{
		m_idroptime -= number;
	}
	ReSetWard();
}

bool Ward::ReSetWard()//�ʱ�ȭ
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

void Ward::speedchange(bool speed)//�ӵ�
{
	if(speed == true)
		m_idroptime -= 20;
	else
		m_idroptime += 20;
}

void Ward::Reback(WardManager* wardmanager)//�����ð��� ������ ������ ȿ���� �ǵ�����
{
	m_WardManager = wardmanager;
	if(wardEffet != WARDEFFET_CLEAR)
		m_WardManager->ItemEffectOff(wardEffet);
}
void Ward::blindward(bool blind)//�ܾ� ������
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
