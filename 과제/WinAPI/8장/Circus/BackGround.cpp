#include "BackGround.h"

void BackGround::End()
{
	m_state = WIN;
}


void Ground::Init(int x, int y, HDC _m_hBuffer, RECT player_rt)
{
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//back.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//바닥
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);
	GetObject(m_BitMap, sizeof(BITMAP), &m_bit);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_icount = 0;
	m_rect.left = x;
	m_rect.top = y;
	m_Charactor_rt = player_rt;
}
void Ground::Render(HDC _m_hBuffer)
{
	StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, 1200, 355, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}

void crowd::Init(int x, int y, HDC _m_hBuffer, RECT player_rt)
{
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//back_normal.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//관중
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);

	m_hBackBuffer2 = CreateCompatibleDC(_m_hBuffer);
	m_BitMap2 = (HBITMAP)LoadImage(NULL, "RES//back_normal2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//관중2
	m_OldBitMap2 = (HBITMAP)SelectObject(m_hBackBuffer2, m_BitMap2);
	GetObject(m_BitMap2, sizeof(BITMAP), &m_bit);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_rect.left = x;
	m_rect.top = y;
	m_rect.right = m_rect.left + m_bit.bmWidth;
	m_rect.bottom = m_rect.top + m_bit.bmHeight;
	m_icount = 0;
	m_Charactor_rt = player_rt;
	m_state = NOMAL;
}

void crowd::Update(RECT rt)
{
	if (m_Charactor_rt.left < 100)
	{
		m_icount++;
		if (m_icount == 2)
		{
			m_rect.left += 1;
			m_rect.right += 1;
			m_icount = 0;
		}
	}
	else
	{
		m_rect.left -= 1;
		m_rect.right -= 1;
		if (m_rect.left <= -1200)
		{
			m_rect.left = 1200;
			m_rect.right = m_rect.left + m_bit.bmWidth;
		}
	}
	m_Charactor_rt = rt;

}
void crowd::Render(HDC _m_hBuffer)
{
	if (m_state == WIN)
	{
		for (int i = 0; i < 18; i++)
			StretchBlt(_m_hBuffer, m_rect.left + (m_bit.bmWidth * i), m_rect.top, m_size.cx, m_size.cy, m_hBackBuffer2, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
		m_state = WIN2;
	}
	else if(m_state == WIN2 || m_state == NOMAL)
	{
		for (int i = 0; i < 18; i++)
			StretchBlt(_m_hBuffer, m_rect.left + (m_bit.bmWidth * i), m_rect.top, m_size.cx, m_size.cy, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
		if (m_state == WIN2)
			m_state = WIN;
	}
}
void crowd::replay(int x, int y, RECT player_rt)
{
	m_rect.left = x;
	m_rect.top = y;
	m_icount = 0;
	m_Charactor_rt = player_rt;
	m_state = NOMAL;
}

void Elephant::Init(int x, int y, HDC _m_hBuffer, RECT player_rt)
{	
	m_hBackBuffer = CreateCompatibleDC(_m_hBuffer);
	m_BitMap = (HBITMAP)LoadImage(NULL, "RES//back_deco.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//코끼리	
	m_OldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_BitMap);
	GetObject(m_BitMap, sizeof(BITMAP), &m_bit);
	m_size.cx = m_bit.bmWidth;
	m_size.cy = m_bit.bmHeight;
	m_icount = 0;
	m_rect.left = x;
	m_rect.top = y;
	m_Charactor_rt = player_rt;
}
void Elephant::Update(RECT rt)
{
	if (m_Charactor_rt.left < 100)
	{
		m_icount++;
		if (m_icount == 2)
		{
			m_rect.left += 1;
			m_rect.right += 1;
			m_icount = 0;
		}
	}
	else
	{
		m_rect.left -= 1;
		m_rect.right -= 1;
		if (m_rect.left <= -1200)
		{
			m_rect.left = 1200;
			m_rect.right = m_rect.left + m_bit.bmWidth;
		}
	}
	m_Charactor_rt = rt;
}

void Elephant::Render(HDC _m_hBuffer)
{
	StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx, m_size.cy, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}

void Elephant::replay(int x, int y, RECT player_rt)
{
	m_rect.left = x;
	m_rect.top = y;
	m_icount = 0;
	m_Charactor_rt = player_rt;
}

void Miter::Init(int x, int y, HDC _m_hBuffer, RECT player_rt)
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
	m_icount = 0;
	m_Charactor_rt = player_rt;
	m_imitercount = 0;
	wsprintf(m_charMiter, "%d", 100 - (10 * m_imitercount));
}

void Miter::Update(RECT rt)
{
	if (m_Charactor_rt.left < 100)
	{
		m_icount++;
		if (m_icount == 2)
		{
			m_rect.left += 1;
			m_rect.right += 1;
			m_icount = 0;
		}
	}
	else
	{
		m_rect.left -= 1;
		m_rect.right -= 1;
		if (m_rect.left <= -200)
		{
			m_rect.left = 1200;
			m_rect.right = m_rect.left + m_bit.bmWidth;
			m_imitercount++;
			wsprintf(m_charMiter, "%d", 100 - (10* m_imitercount));
		}
	}
	m_Charactor_rt = rt;
}

void Miter::Render(HDC _m_hBuffer)
{
	StretchBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx * 1.5, m_size.cy * 1.5, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
	TextOut(_m_hBuffer, m_rect.left + 50, m_rect.top + 10, m_charMiter, lstrlen(m_charMiter));
}

void Miter::replay(int x, int y, RECT player_rt)
{
	m_rect.left = x;
	m_rect.top = y;
	m_icount = 0;
	m_Charactor_rt = player_rt;
	m_imitercount = 0;
	wsprintf(m_charMiter, "%d", 100 - (10 * m_imitercount));
}

void EndBox::Init(int x, int y, HDC _m_hBuffer, RECT player_rt)
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
	m_rect.right = m_rect.left + m_bit.bmWidth;
	m_rect.bottom = m_rect.top + m_bit.bmHeight;
	m_icount = 0;
	m_Charactor_rt = player_rt;
}

void EndBox::Update(RECT rt)
{
	if (m_Charactor_rt.left < 100)
	{
		m_icount++;
		if (m_icount == 2)
		{
			m_rect.left += 1;
			m_rect.right += 1;
			m_icount = 0;
		}
	}
	else
	{
		if (m_rect.left >= 1080)
		{
			m_rect.left -= 1;
			m_rect.right -= 1;
		}
	}
	m_Charactor_rt = rt;

}
void EndBox::Render(HDC _m_hBuffer)
{
	TransparentBlt(_m_hBuffer, m_rect.left, m_rect.top, m_size.cx * 1.5, m_size.cy * 1.5, m_hBackBuffer, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
}