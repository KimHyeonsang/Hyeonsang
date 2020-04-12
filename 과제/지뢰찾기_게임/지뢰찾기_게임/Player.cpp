#include "Player.h"



Player::Player()
{
	m_ix = WIDTH;
	m_iy = HEIGHT / 2;
	shap = "◇";
	m_bmovecharacterCheck = false;
	m_bmovecheck = false;
	m_icount = (WIDTH - 2)*(HEIGHT - 2);
	int count = 0;
	m_bcountcheck = false;
	playermove = new playerMove*[m_icount];
	for (int i = 0; i < m_icount; i++)
		playermove[i] = new playerMove;
	for (int y = 1; y < 10; y++)//플레이어 위치배열저장
	{
		for (int x = 1; x < 10; x++)
		{
			playermove[count]-> x = x * 2;
			playermove[count]-> y = y;
			count++;
		}
	}
}

void Player::MovePlayer(Mapdraw* mapdraw)
{
	int tmp_x, tmp_y;
	tmp_x = m_ix;
	tmp_y = m_iy;
	if(m_bmovecheck == false)
		mapdraw->settingobject(shap, m_ix, m_iy);
	playKey(mapdraw);
	beforecharaterdraw(mapdraw,tmp_x, tmp_y);
}
void Player::playKey(Mapdraw* mapdraw)
{
	if (kbhit())
	{
		char ch = getch();
		switch (ch)
		{
		case KEY_UP:
			if (m_iy > PLAYER_Y_MOVE)
			{
				m_iy -= 1;
				if (m_iy < 0)
					m_iy += PLAYER_Y_MOVE;
			}
			m_bmovecheck = true;
			m_bmovecharacterCheck = true;
			break;
		case KEY_DOWN:
			if (m_iy < HEIGHT - 2)
			{
				m_iy += PLAYER_Y_MOVE;
				if (m_iy > HEIGHT - 2)
					m_iy -= PLAYER_Y_MOVE;
			}
			m_bmovecheck = true;
			m_bmovecharacterCheck = true;
			break;
		case KEY_LEFT:
			if (m_ix > 2)
			{
				m_ix -= PLAYER_X_MOVE;
				if (m_ix < 2)
					m_ix += PLAYER_X_MOVE;
			}
			m_bmovecheck = true;
			m_bmovecharacterCheck = true;
			break;
		case KEY_RIGHT:
			if (m_ix <= MAPSIZE_WIDTH - PLAYER_X_MOVE)
			{
				m_ix += PLAYER_X_MOVE;
				if (m_ix >= MAPSIZE_WIDTH - PLAYER_X_MOVE)
					m_ix -= PLAYER_X_MOVE;
			}
			m_bmovecheck = true;
			m_bmovecharacterCheck = true;
			break;
		case KEY_ENTER:
			//효과 발동
			for (int i = 0; i < m_icount; i++)
			{
				if (playermove[i]->x == m_ix && playermove[i]->y == m_iy)
					playermove[i]->check = false;
			}
			mapdraw->openBox(m_ix, m_iy);
			if (mapdraw->number(m_ix/2, m_iy) == 0)
			{
				for (int i = 0; i < m_icount; i++)
				{
					if (playermove[i]->x == m_ix + PLAYER_X_MOVE && playermove[i]->y == m_iy)
						playermove[i]->check = false;
					if (playermove[i]->x == m_ix - PLAYER_X_MOVE && playermove[i]->y == m_iy)
						playermove[i]->check = false;
					if (playermove[i]->x == m_ix && playermove[i]->y == m_iy + PLAYER_Y_MOVE)
						playermove[i]->check = false;
					if (playermove[i]->x == m_ix && playermove[i]->y == m_iy - PLAYER_Y_MOVE)
						playermove[i]->check = false;
					if (playermove[i]->x == m_ix  + PLAYER_X_MOVE && playermove[i]->y == m_iy - PLAYER_Y_MOVE)
						playermove[i]->check = false;
					if (playermove[i]->x == m_ix  - PLAYER_X_MOVE && playermove[i]->y == m_iy + PLAYER_Y_MOVE)
						playermove[i]->check = false;
					if (playermove[i]->x == m_ix + PLAYER_X_MOVE && playermove[i]->y == m_iy + PLAYER_Y_MOVE)
						playermove[i]->check = false;
					if (playermove[i]->x == m_ix - PLAYER_X_MOVE && playermove[i]->y == m_iy - PLAYER_Y_MOVE)
						playermove[i]->check = false;
				}
			}
			break;
		default:
			break;
		}
	}
}
void Player::beforecharaterdraw(Mapdraw* mapdraw,int x, int y)//이전에플레이어위치지우기
{
	if (m_bmovecharacterCheck == false)
	{
		m_bmovecheck = false;
		return;
	}
	for (int i = 0; i < m_icount; i++)
	{
		if (playermove[i]->check == false && playermove[i]->x == x && playermove[i]->y == y)
		{
			mapdraw->beforelocation(x, y);
			m_bmovecheck = false;
			return;
		}
		else
		{
			map.settingobject("  ", x, y);
			m_bmovecheck = false;
		}
	}
	m_bmovecharacterCheck = false;
}
bool Player::Victory()
{
	int count = 0;
	for (int i = 0; i < m_icount; i++)
	{
		if (playermove[i]->check == true)
			count++;
	}
	if (count == m_icount)
		m_bcountcheck = true;
		return m_bcountcheck;
}
void Player::PlayerSet()//할당 해제후 재설정
{
	int count = 0;
	for (int i = 0; i < m_icount; i++)
	{
		if (playermove[i] != NULL)
		{
			delete playermove[i];
			playermove[i] = NULL;
		}
	}
	if (playermove != NULL)
	{
		delete playermove;
		playermove = NULL;
	}
	m_ix = WIDTH;
	m_iy = HEIGHT / 2;
	shap = "◇";
	m_bmovecharacterCheck = false;
	m_bmovecheck = false;

	playermove = new playerMove*[m_icount];
	for (int i = 0; i < m_icount; i++)
		playermove[i] = new playerMove;
	for (int y = 1; y < 10; y++)//플레이어 위치배열저장
	{
		for (int x = 1; x < 10; x++)
		{
			playermove[count]->x = x * 2;
			playermove[count]->y = y;
			count++;
		}
	}
}
Player::~Player()
{
	for (int i = 0; i < m_icount; i++)
	{
		if (playermove[i] != NULL)
		{
			delete playermove[i];
			playermove[i] = NULL;
		}
	}
	if (playermove != NULL)
	{
		delete playermove;
		playermove = NULL;
	}
}
