#include "Mapdraw.h"



Mapdraw::Mapdraw()
{
	for (int y = 0; y < WIDTH; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			m_imap[y][x] = { 0 };
		}
	}
	m_iboomCount = 0;
	m_bGameOver = false;
}
void Mapdraw::createOutBox()//외부벽설정
{
	for (int y = 0; y < HEIGHT; y++)
	{
		if (y == 0 || y == HEIGHT - 1)
		{
			for (int x = 0; x < WIDTH; x++)
				m_imap[y][x] = { MAPPACKGE_OUTBOX };
		}
		else
		{
			for (int x = 0; x < WIDTH; x++)
			{
				if (x == 0 || x == WIDTH - 1)
					m_imap[y][x] = { MAPPACKGE_OUTBOX };
			}
		}
	}
}

void Mapdraw::mapdraw()
{
	for (int y = 0; y < WIDTH; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			if (m_imap[y][x] == MAPPACKGE_OUTBOX)
				cout << "■";
			else
				cout << "  ";
		}
		cout << endl;
	}
}

void Mapdraw::settingobject(string str, int& x, int y)//캐릭터 지뢰그리기
{
	if (x % 2 != 0)
		x -= 1;
	gotoxy(x, y);
	cout << str;
}
void Mapdraw::Createmine(int& x, int& y)
{
	while (1)
	{
		if (m_imap[y][x] == MAPPACKGE_BOOM)
		{
			if (y == 1)
				y++;
			else
				y--;
			if (x == 9)
				x--;
			else
				x++;
		}
		else
		{
			m_imap[y][x] = MAPPACKGE_BOOM;
			return;
		}
	}
}

void Mapdraw::counttingBoom()
{
	for (int y = 1; y < WIDTH - 1; y++)
	{
		for (int x = 1; x < HEIGHT - 1; x++)
		{
			if (m_imap[y][x] != MAPPACKGE_BOOM)
			{
				if (m_imap[y][x + 1] == MAPPACKGE_BOOM)//오른쪽
					m_iboomCount++;
				if (m_imap[y][x - 1] == MAPPACKGE_BOOM)//왼쪽
					m_iboomCount++;
				if (m_imap[y + 1][x] == MAPPACKGE_BOOM)//아래
					m_iboomCount++;
				if (m_imap[y - 1][x] == MAPPACKGE_BOOM)//위
					m_iboomCount++;
				if (m_imap[y - 1][x + 1] == MAPPACKGE_BOOM)//오른쪽위
					m_iboomCount++;
				if (m_imap[y + 1][x - 1] == MAPPACKGE_BOOM)//왼쪽아래
					m_iboomCount++;
				if (m_imap[y + 1][x + 1] == MAPPACKGE_BOOM)//왼쪽위
					m_iboomCount++;
				if (m_imap[y - 1][x - 1] == MAPPACKGE_BOOM)//오른쪽아래
					m_iboomCount++;
				m_imap[y][x] = m_iboomCount;
			}
			m_iboomCount = 0;
		}
	}
}
void Mapdraw::openBox(int player_x, int player_y)//캐릭터가 눌리면 무엇인지 확인
{
	int playx = player_x /= 2;
	if (m_imap[player_y][playx] == 0)
	{
		if (m_imap[player_y][playx + 1] >= 1 && m_imap[player_y][playx + 1] < 9)//오른쪽
		{
			gotoxy((playx * 2) + PLAYER_X_MOVE, player_y);
			cout << m_imap[player_y][playx + 1];
		}
		if (m_imap[player_y][playx - 1] >= 1 && m_imap[player_y][playx - 1] < 9)//왼쪽
		{
			gotoxy((playx * 2) - PLAYER_X_MOVE, player_y);
			cout << m_imap[player_y][playx - 1];
		}
		if (m_imap[player_y + 1][playx] >= 1 && m_imap[player_y + 1][playx] < 9)//아래
		{
			gotoxy(playx * 2, player_y + PLAYER_Y_MOVE);
			cout << m_imap[player_y + 1][playx];
		}
		if (m_imap[player_y - 1][playx] >= 1 && m_imap[player_y - 1][playx] < 9)//위
		{
			gotoxy(playx * 2, player_y - PLAYER_Y_MOVE);
			cout << m_imap[player_y - 1][playx];
		}
		if (m_imap[player_y - 1][playx + 1] >= 1 && m_imap[player_y - 1][playx + 1] < 9)//오른쪽위
		{
			gotoxy((playx * 2) + PLAYER_X_MOVE, player_y - PLAYER_Y_MOVE);
			cout << m_imap[player_y - 1][playx + 1];
		}
		if (m_imap[player_y + 1][playx - 1] >= 1 && m_imap[player_y + 1][playx - 1] < 9)//왼쪽아래
		{
			gotoxy((playx * 2) - PLAYER_X_MOVE, player_y + PLAYER_Y_MOVE);
			cout << m_imap[player_y + 1][playx - 1];
		}
		if (m_imap[player_y + 1][playx + 1] >= 1 && m_imap[player_y + 1][playx + 1] < 9)//왼쪽위
		{
			gotoxy((playx * 2) + PLAYER_X_MOVE, player_y + PLAYER_Y_MOVE);
			cout << m_imap[player_y + 1][playx + 1];
		}
		if (m_imap[player_y - 1][playx - 1] >= 1 && m_imap[player_y - 1][playx - 1] < 9)//오른쪽아래
		{
			gotoxy((playx * 2) - PLAYER_X_MOVE, player_y - PLAYER_Y_MOVE);
			cout << m_imap[player_y - 1][playx - 1];
		}
	}
	if (m_imap[player_y][playx] > 0 && m_imap[player_y][playx] < 9)//다른 것이면 그리기
	{
		gotoxy((playx * 2), player_y);
		cout << m_imap[player_y][playx];
	}
	if (m_imap[player_y][playx] == MAPPACKGE_BOOM)// 지뢰이면 
		m_bGameOver = true;
}
void Mapdraw::Resetboard()
{
	for (int y = 0; y < WIDTH; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			m_imap[y][x] = { 0 };
		}
	}
	m_bGameOver = false;
}
void Mapdraw::beforelocation(int x, int y)//이전좌표숫자그리기
{
	gotoxy(x, y);
	cout << m_imap[y][x / 2];
}
Mapdraw::~Mapdraw()
{
}
