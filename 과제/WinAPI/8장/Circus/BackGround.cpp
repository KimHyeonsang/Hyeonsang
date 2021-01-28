#include "BackGround.h"

void BackGround::End()
{
	m_state = WIN;
}


void Ground::Init(int x, int y, HDC _m_hBuffer)
{
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//back.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//바닥
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);
	GetObject(m_BitMap, sizeof(BITMAP), &m_bit);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_rect.left = x;
	m_rect.top = y;
}
void Ground::Render(HDC _m_hBuffer)
{
	StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, 1200, 355, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}

void crowd::Init(int x, int y, HDC _m_hBuffer)
{
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//back_normal.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//관중
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);
	GetObject(m_BitMap, sizeof(BITMAP), &m_bit);

	m_hBackBuffer2 = CreateCompatibleDC(_m_hBuffer);
	m_BitMap2 = (HBITMAP)LoadImage(NULL, "RES//back_normal2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//관중2
	m_OldBitMap2 = (HBITMAP)SelectObject(m_hBackBuffer2, m_BitMap2);
	GetObject(m_BitMap2, sizeof(BITMAP), &m_bit2);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_rect.left = x;
	m_rect.top = y;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.bottom = m_rect.top + m_size.cy;
	m_state = NOMAL;

	m_ispeed = 40;
}

void crowd::Update(Direction direction, float time)
{	
	if (direction == LEFT)
	{
		m_rect.left += m_ispeed * time;
		m_rect.right += m_ispeed * time;
		if (m_rect.right >= 1200)
		{
			m_rect.left = 0;
			m_rect.right = m_rect.left + m_size.cx;
		}
	}
	else if(direction == RIGHT)
	{
		if (m_rect.left <= 0)
		{
			m_rect.left = 1135;
			m_rect.right = m_rect.left + m_bit.bmWidth;
		}
		m_rect.left -= m_ispeed * time;
		m_rect.right -= m_ispeed * time;
	}
}

void crowd::Render(HDC _m_hBuffer)
{
	if (m_state == WIN)
	{
		StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx, m_size.cy, m_hBackBuffer2, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
		m_state = WIN2;
	}
	else if(m_state == WIN2 || m_state == NOMAL)
	{
		StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx, m_size.cy, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
		if (m_state == WIN2)
			m_state = WIN;
	}
}

void crowd::replay(int x, int y)
{
	m_rect.left = x;
	m_rect.top = y;
	m_rect.right = m_rect.left + m_bit.bmWidth;
	m_rect.bottom = m_rect.top + m_bit.bmHeight;
	m_state = NOMAL;
}

void Elephant::Init(int x, int y, HDC _m_hBuffer)
{	
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//back_deco.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//코끼리	
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);
	GetObject(m_BitMap, sizeof(BITMAP), &m_bit);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_rect.left = x;
	m_rect.top = y;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.bottom = m_rect.top + m_size.cy;
	m_ispeed = 40;
}

void Elephant::Update(Direction direction, float time)
{
	if (direction == LEFT)
	{
		m_rect.left += m_ispeed * time;
		m_rect.right += m_ispeed * time;
		if (m_rect.right >= 1200)
		{
			m_rect.left = 0;
			m_rect.right = m_rect.left + m_size.cx;
		}
	}
	else if(direction == RIGHT)
	{
		if (m_rect.left <= 0)
		{
			m_rect.left = 1135;
			m_rect.right = m_rect.left + m_bit.bmWidth;
		}
		m_rect.left -= m_ispeed * time;
		m_rect.right -= m_ispeed * time;
		
	}
}

void Elephant::Render(HDC _m_hBuffer)
{
	StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx, m_size.cy, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}

void Elephant::replay(int x, int y)
{
	m_rect.left = x;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.top = y;
	m_rect.bottom = m_rect.top + m_size.cy;
}

void Miter::Init(int x, int y, HDC _m_hBuffer)
{
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//miter.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//미터기
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);
	GetObject(m_BitMap, sizeof(BITMAP), &m_bit);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_rect.left = x;
	m_rect.top = y;
	m_imitercount = 10;
	wsprintf(m_charMiter, "%d", 10 * m_imitercount);
	m_ispeed = 40;
}

void Miter::Update(Direction direction, float time)
{
	if (direction == LEFT)
	{
		m_rect.left += m_ispeed * time;
		m_rect.right += m_ispeed * time;
	}
	else if (direction == RIGHT)
	{
		m_rect.left -= m_ispeed * time;
		m_rect.right -= m_ispeed * time;
		if (m_rect.left <= -200)
		{
			m_rect.left = 1200;
			m_rect.right = m_rect.left + m_bit.bmWidth;
			m_imitercount--;
			wsprintf(m_charMiter, "%d", 10 * m_imitercount);
		}
	}
}

void Miter::Render(HDC _m_hBuffer)
{
	StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx * 1.5, m_size.cy * 1.5, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
	TextOut(_m_hBuffer, m_rect.left + 50, m_rect.top + 10, m_charMiter, lstrlen(m_charMiter));
}

void Miter::replay(int x, int y)
{
	m_rect.left = x;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.top = y;
	m_rect.bottom = m_rect.top + m_size.cy;
	m_imitercount = 10;
	wsprintf(m_charMiter, "%d", 10 * m_imitercount);
}

void EndBox::Init(int x, int y, HDC _m_hBuffer)
{
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//end.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//무대
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);
	GetObject(m_BitMap, sizeof(BITMAP), &m_bit);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_rect.left = x;
	m_rect.top = y;
	m_rect.right = m_rect.left + m_size.cx * 1.5;
	m_rect.bottom = m_rect.top + m_size.cy * 1.5;
	m_ispeed = 40;
}

void EndBox::Update(Direction direction, float time)
{
	if (direction == RIGHT)
	{
		if (m_rect.left >= 1080)
		{
			m_rect.left -= m_ispeed * time;
			m_rect.right -= m_ispeed * time;
		}
	}
}

void EndBox::Render(HDC _m_hBuffer)
{
	TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx * 1.5, m_size.cy * 1.5, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
}

void EndBox::replay(int x, int y)
{
	m_rect.left = x;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.top = y;
	m_rect.bottom = m_rect.top + m_size.cy;
}

