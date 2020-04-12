#include "Boom.h"



Boom::Boom()
{
	m_iBoomNumber = ((WIDTH * HEIGHT) / 5);
	m_bomlist = new BombList*[m_iBoomNumber];
	for (int i = 0; i < m_iBoomNumber; i++)
	{
		m_bomlist[i] = new BombList;

	}
	srand(time(NULL));
}

void Boom::BoomSetting(Mapdraw* map)
{
	for (int i = 0; i < m_iBoomNumber; i++)
	{
		m_bomlist[i]->x = rand() % 9 + 1;//1~9
		m_bomlist[i]->y = rand() % 9 + 1;
		map->Createmine(m_bomlist[i]->x, m_bomlist[i]->y);
	}
}
void Boom::BoomReSet()//삭제하고 다시할당
{
	for (int i = 0; i < m_iBoomNumber; i++)
	{
		if (m_bomlist[i] != NULL)
		{
			delete m_bomlist[i];
			m_bomlist[i] = NULL;
		}
	}
	if (m_bomlist != NULL)
	{
		delete m_bomlist;
		m_bomlist = NULL;
	}
	m_bomlist = new BombList*[m_iBoomNumber];
	for (int i = 0; i < m_iBoomNumber; i++)
	{
		m_bomlist[i] = new BombList;

	}
}
Boom::~Boom()
{
	for (int i = 0; i < m_iBoomNumber; i++)
	{
		if (m_bomlist[i] != NULL)
		{
			delete m_bomlist[i];
			m_bomlist[i] = NULL;
		}
	}
	if (m_bomlist != NULL)
	{
		delete m_bomlist;
		m_bomlist = NULL;
	}
}
