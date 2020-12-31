#include "Character.h"



Character::Character()
{
	m_state = WALK1;
	m_iHartcount = 3;
}

void Character::Init(HWND hWnd,HDC _m_hBuffer)
{
	m_hWnd = hWnd;
	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//player0.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//플레이어
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	BITMAP bit;
	GetObject(m_BitMap[0], sizeof(BITMAP), &bit);
	m_size.cx = bit.bmWidth;
	m_size.cy = bit.bmHeight;

	m_hBackBuffer[1] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, "RES//player2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//플레이어 점프
	m_OldBitMap[1] = (HBITMAP)SelectObject(m_hBackBuffer[1], m_BitMap[1]);
	GetObject(m_BitMap[1], sizeof(BITMAP), &bit);
	m_size.cx = bit.bmWidth;
	m_size.cy = bit.bmHeight;

	m_hBackBuffer[2] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[2] = (HBITMAP)LoadImage(NULL, "RES//player1.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//플레이어 달리기
	m_OldBitMap[2] = (HBITMAP)SelectObject(m_hBackBuffer[2], m_BitMap[2]);
	GetObject(m_BitMap[2], sizeof(BITMAP), &bit);
	m_size.cx = bit.bmWidth;
	m_size.cy = bit.bmHeight;

	m_hBackBuffer[3] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[3] = (HBITMAP)LoadImage(NULL, "RES//icon.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//플레이어목숨
	m_OldBitMap[3] = (HBITMAP)SelectObject(m_hBackBuffer[3], m_BitMap[3]);
	GetObject(m_BitMap[3], sizeof(BITMAP), &m_bithart);

	m_hBackBuffer[4] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[4] = (HBITMAP)LoadImage(NULL, "RES//win.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//플레이어 승리 포즈1
	m_OldBitMap[4] = (HBITMAP)SelectObject(m_hBackBuffer[4], m_BitMap[4]);
	GetObject(m_BitMap[4], sizeof(BITMAP), &m_bitWin);

	m_hBackBuffer[5] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[5] = (HBITMAP)LoadImage(NULL, "RES//win2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//플레이어 승리 포즈2
	m_OldBitMap[5] = (HBITMAP)SelectObject(m_hBackBuffer[5], m_BitMap[5]);
	GetObject(m_BitMap[5], sizeof(BITMAP), &m_bitWin);

	m_Winsize.cx = m_bitWin.bmWidth;
	m_Winsize.cy = m_bitWin.bmHeight;

	m_hBackBuffer[6] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[6] = (HBITMAP)LoadImage(NULL, "RES//die.bmp", IMAGE_BITMAP, 0, 0,
	LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//플레이어 죽음
	m_OldBitMap[6] = (HBITMAP)SelectObject(m_hBackBuffer[6], m_BitMap[6]);
	GetObject(m_BitMap[6], sizeof(BITMAP), &m_bitdie);

	m_Diesize.cx = m_bitdie.bmWidth;
	m_Diesize.cy = m_bitdie.bmHeight;

	m_hart.cx = m_bithart.bmWidth;
	m_hart.cy = m_bithart.bmHeight;
	m_MoveSpeed = 1;
	m_rect.left = 100;
	m_rect.top = 450;
	m_ibefore_y = m_rect.top;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.bottom = m_rect.top + m_size.cy;
	m_bJumpcheck = false;
//	SetTimer(m_hWnd, 0, 10000, NULL);
}
void Character::Render(HDC _m_hBuffer)
{
	if (m_state == WALK1)
	{	
		TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx, m_size.cy * 1.5, m_hBackBuffer[0], 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
	}
	else if (m_state == WALK2)
	{	
		TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx, m_size.cy * 1.5, m_hBackBuffer[2], 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
	}
	if (m_state == JUMP) 
	{
		TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx, m_size.cy * 1.5, m_hBackBuffer[1], 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
	}
	
	if (m_iHartcount > 0)
	{
		for (int i = 0; i < m_iHartcount; i++)  //목숨갯수
			TransparentBlt(_m_hBuffer, 1100 + (20 * i), 50, m_hart.cx, m_hart.cy * 1.5, m_hBackBuffer[3], 0, 0, m_hart.cx, m_hart.cy, RGB(255, 0, 255));
	}	
	if (m_state == WIN)
	{
		TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_Winsize.cx, m_Winsize.cy * 1.5, m_hBackBuffer[4], 0, 0, m_Winsize.cx, m_Winsize.cy, RGB(255, 0, 255));
		m_state = WIN2;
	}
	else if (m_state == WIN2)
	{
		TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_Winsize.cx, m_Winsize.cy * 1.5, m_hBackBuffer[5], 0, 0, m_Winsize.cx, m_Winsize.cy, RGB(255, 0, 255));
		m_state = WIN;
	}
	else if (m_state == DIE)
	{
		TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_Diesize.cx, m_Diesize.cy * 1.5, m_hBackBuffer[6], 0, 0, m_Diesize.cx, m_Diesize.cy, RGB(255, 0, 255));
	}
}

void Character::hartbreaker()
{
	if (m_iHartcount > 0)
	{
		m_iHartcount -= 1;
	}
	m_state = DIE;
}

void Character::PlayerKey() //누른 키에 따른 상태 변화
{
	if (GetKeyState(VK_LEFT) & 0x8000 && m_state != JUMP)
	{
		if (m_state == WALK1)
			m_state = WALK2;
		else if (m_state == WALK2)
			m_state = WALK1;
		m_Direction = LEFT;
		if (m_rect.left <= 0)
		{
			m_rect.left = 0;
			m_rect.right = m_rect.left + m_size.cx;
		}
		else
		{
			m_rect.left -= m_MoveSpeed;
			m_rect.right -= m_MoveSpeed;
		}
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000 && m_state != JUMP)
	{
		if (m_state == WALK1)
			m_state = WALK2;
		else if (m_state == WALK2)
			m_state = WALK1;
		m_Direction = RIGHT;
		if (m_rect.right >= 1200)
		{
			m_rect.left = m_rect.right - m_size.cx;;
			m_rect.right = 1200;
		}
		else
		{
			m_rect.left += m_MoveSpeed;
			m_rect.right += m_MoveSpeed;
		}
	}
	else if (m_state != JUMP)
		m_Direction = IDLE;
	if (GetKeyState(VK_SPACE) & 0x8000 && m_state != JUMP)//점프 상태일때는 한번더 점프가 불가능하게 막기위해
	{
		m_bJumpcheck = true;
		m_state = JUMP;
	}
}

void Character::Update()
{
	PlayerKey();	
	if (m_bJumpcheck == true && m_state == JUMP) //점프상태일때
	{
		m_rect.top -= m_MoveSpeed;
		m_rect.bottom -= m_MoveSpeed;
		if (m_Direction == LEFT)
		{
			if (m_rect.left <= 0)
			{
				m_rect.left = 0;
				m_rect.right = m_rect.left + m_size.cx;
			}
			else
			{
				m_rect.left -= m_MoveSpeed;
				m_rect.right -= m_MoveSpeed;
			}
		}
		else if (m_Direction == RIGHT)
		{
			if (m_rect.right >= 1200)
			{
				m_rect.left = m_rect.right - m_size.cx;;
				m_rect.right = 1200;
			}
			else
			{
				m_rect.left += m_MoveSpeed;
				m_rect.right += m_MoveSpeed;
			}
		}
		if (m_rect.top <= m_ibefore_y - 180)
		{
			m_bJumpcheck = false;
		}
	}
	else if(m_bJumpcheck == false && m_state == JUMP) //점프상태일때
	{
		m_rect.top += m_MoveSpeed;
		m_rect.bottom += m_MoveSpeed;
		if (m_Direction == LEFT)
		{
			if (m_rect.left <= 0)
			{
				m_rect.left = 0;
				m_rect.right = m_rect.left + m_size.cx;
			}
			else
			{
				m_rect.left -= m_MoveSpeed;
				m_rect.right -= m_MoveSpeed;
			}
		}
		else if (m_Direction == RIGHT)
		{
			if (m_rect.right >= 1200)
			{
				m_rect.left = m_rect.right - m_size.cx;;
				m_rect.right = 1200;
			}
			else
			{
				m_rect.left += m_MoveSpeed;
				m_rect.right += m_MoveSpeed;
			}
		}
		if (m_rect.top >= m_ibefore_y)
		{
			m_Direction = IDLE;
			m_state = WALK1;
		}
	}	
}

void Character::endlocation(RECT rt)
{
	m_rect.top = m_ibefore_y - ((rt.bottom - rt.top)*1.5);
	m_rect.bottom = m_ibefore_y - ((rt.bottom - rt.top)*1.5);
	m_ibefore_y = m_rect.top;
	m_state = WIN;
}

void Character::replay()
{
	m_state = WALK1;
	m_rect.left = 100;
	m_rect.top = 450;
	m_ibefore_y = m_rect.top;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.bottom = m_rect.top + m_size.cy;
	m_bJumpcheck = false;
}

Character::~Character()
{
}
