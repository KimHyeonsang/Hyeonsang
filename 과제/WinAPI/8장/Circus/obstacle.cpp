#include "obstacle.h"



jar::jar()
{
	m_efire = burn1;
	m_rect[0].left = 700;
	m_rect[0].top = 470;
	m_count = 0;
	m_bScorecheck = true;
}

void jar::Init(HDC _m_hBuffer,RECT player_rt)
{
	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//front.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 항아리
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	GetObject(m_BitMap[0], sizeof(BITMAP), &m_bit[0]);
	m_size[0].cx = m_bit[0].bmWidth;
	m_size[0].cy = m_bit[0].bmHeight;
	m_rect[0].right = m_rect[0].left + m_size[0].cx;
	m_rect[0].bottom = m_rect[0].top + m_size[0].cy;

	m_hBackBuffer[1] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, "RES//front2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 항아리
	m_OldBitMap[1] = (HBITMAP)SelectObject(m_hBackBuffer[1], m_BitMap[1]);
	m_Charactor_rt = player_rt;
}

void jar::Render(HDC _m_hBuffer)
{
	if (m_efire == burn1)
	{
		TransparentBlt(_m_hBuffer, m_rect[0].left, m_rect[0].top, m_size[0].cx*1.5, m_size[0].cy*1.5, m_hBackBuffer[0], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		m_efire = burn2;
	}
	else if (m_efire == burn2)
	{
		TransparentBlt(_m_hBuffer, m_rect[0].left, m_rect[0].top, m_size[0].cx*1.5, m_size[0].cy*1.5, m_hBackBuffer[1], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		m_efire = burn1;
	}
	
}
void jar::Update(RECT rt)
{
	
	if (m_Charactor_rt.left < 100)
	{
		m_count++;
		if (m_count == 2)
		{
			m_rect[0].left += 1;
			m_rect[0].right += 1;
			m_count = 0;
		}
	}
	else
	{
		m_rect[0].left -= 1;
		m_rect[0].right -= 1;
		if (m_rect[0].left <= -200)
		{
			m_bScorecheck = true;
			m_rect[0].left = 1200;
			m_rect[0].right = m_rect[0].left + m_bit[0].bmWidth;
		}
	}
	m_Charactor_rt = rt;
}
int jar::Score(int player_x)
{
	if (player_x > m_rect[0].left && m_bScorecheck == true)
	{
		m_iScore = 50;
		m_bScorecheck = false;
		return m_iScore;
	}
	else
	{
		m_iScore = 0;
		return m_iScore;
	}
}

void jar::replay()
{
	m_efire = burn1;
	m_rect[0].left = 700;
	m_rect[0].top = 470;
	m_rect[0].right = m_rect[0].left + m_size[0].cx;
	m_rect[0].bottom = m_rect[0].top + m_size[0].cy;
	m_count = 0;
	m_bScorecheck = true;
}

jar::~jar()
{
}

LeftFirering::LeftFirering()
{
	m_efire = burn1;
	m_rect[0].left = 1300;
	m_rect[0].top = 210;
	m_rect[1].left = 1300;
	m_rect[1].top = 210;

	m_bScorecheck = true;
	m_crash.left = m_rect[0].left + 20;
}

void LeftFirering::Init(HDC _m_hBuffer, RECT player_rt)
{
	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//enemy_b.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 링
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	GetObject(m_BitMap[0], sizeof(BITMAP), &m_bit[0]);
	m_size[0].cx = m_bit[0].bmWidth;
	m_size[0].cy = m_bit[0].bmHeight;
	m_rect[0].right = m_rect[0].left + m_size[0].cx;
	m_rect[0].bottom = m_rect[0].top + m_size[0].cy;

	m_hBackBuffer[1] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, "RES//enemy_1b.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 링
	m_OldBitMap[1] = (HBITMAP)SelectObject(m_hBackBuffer[1], m_BitMap[1]);
	GetObject(m_BitMap[1], sizeof(BITMAP), &m_bit[1]);
	m_size[1].cx = m_bit[1].bmWidth;
	m_size[1].cy = m_bit[1].bmHeight;
	m_rect[1].right = m_rect[1].left + m_size[1].cx;
	m_rect[1].bottom = m_rect[1].top + m_size[1].cy;

	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 2);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + (m_size[0].cx * 0.5);
}

void LeftFirering::Update()
{
if (m_rect[0].left == -200 && m_rect[1].left == -200)
	{
		m_rect[0].left = 1335;
		m_rect[1].left = 1335;
		m_bScorecheck = true;
		m_crash.left = m_rect[0].left + 20;
		m_crash.right = m_crash.left + (m_size[0].cx);
	}
	else
	{
		m_rect[0].left -= 1;
		m_rect[0].right -= 1;
		m_rect[1].left -= 1;
		m_rect[1].right -= 1;

		m_crash.left -= 1;
		m_crash.right -= 1;
	}
}
void LeftFirering::Render(HDC _m_hBuffer)
{
	if (m_efire == burn1)
	{
		TransparentBlt(_m_hBuffer, m_rect[0].left, m_rect[0].top, m_size[0].cx*1.5, m_size[0].cy*2, m_hBackBuffer[0], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		m_efire = burn2;
	}
	else if (m_efire == burn2)
	{
		TransparentBlt(_m_hBuffer, m_rect[1].left, m_rect[1].top, m_size[1].cx*1.5, m_size[1].cy*2, m_hBackBuffer[1], 0, 0, m_size[1].cx, m_size[1].cy, RGB(255, 0, 255));
		m_efire = burn1;
	}

}
int LeftFirering::Score(int player_x)
{
	if (player_x > m_crash.left && m_bScorecheck == true)
	{
		m_iScore = 100;
		m_bScorecheck = false;
		return m_iScore;
	}
	else
	{
		m_iScore = 0;
		return m_iScore;
	}
}

void LeftFirering::replay()
{
	m_efire = burn1;
	m_rect[0].left = 1300;
	m_rect[0].top = 210;
	m_rect[0].right = m_rect[0].left + m_size[0].cx;
	m_rect[0].bottom = m_rect[0].top + m_size[0].cy;
	m_rect[1].left = 1300;
	m_rect[1].top = 210;
	m_rect[1].right = m_rect[1].left + m_size[1].cx;
	m_rect[1].bottom = m_rect[1].top + m_size[1].cy;

	m_bScorecheck = true;
	m_crash.left = m_rect[0].left + 20;
	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 2);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + (m_size[0].cx * 0.5);
}

LeftFirering::~LeftFirering()
{
}

RightFirering::RightFirering()
{
	m_efire = burn1;
	m_rect[0].left = 1335;
	m_rect[0].top = 210;
	m_rect[1].left = 1335;
	m_rect[1].top = 210;

	m_crash.left = m_rect[0].left;
}

void RightFirering::Init(HDC _m_hBuffer, RECT player_rt)
{
	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//enemy_f.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 링
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	GetObject(m_BitMap[0], sizeof(BITMAP), &m_bit[0]);
	m_size[0].cx = m_bit[0].bmWidth;
	m_size[0].cy = m_bit[0].bmHeight;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 2);

	m_hBackBuffer[1] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, "RES//enemy_1f.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 링
	m_OldBitMap[1] = (HBITMAP)SelectObject(m_hBackBuffer[1], m_BitMap[1]);
	GetObject(m_BitMap[1], sizeof(BITMAP), &m_bit[1]);
	m_size[1].cx = m_bit[1].bmWidth;
	m_size[1].cy = m_bit[1].bmHeight;
	m_rect[1].right = m_rect[1].left + (m_size[1].cx * 1.5);
	m_rect[1].bottom = m_rect[1].top + (m_size[1].cy * 2);

	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 2);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + (m_size[0].cx * 0.5);
}
void RightFirering::Update()
{
	if (m_rect[0].left == -200 && m_rect[1].left == -200)
	{
		m_rect[0].left = 1335;
		m_rect[1].left = 1335;

		m_crash.left = 1335;
		m_crash.right = m_crash.left + (m_size[0].cx * 1.5);
	}
	else
	{
		m_rect[0].left -= 1;
		m_rect[0].right -= 1;
		m_rect[1].left -= 1;
		m_rect[1].right -= 1;

		m_crash.left -= 1;
		m_crash.right -= 1;
	}
}
void RightFirering::Render(HDC _m_hBuffer)
{
	if (m_efire == burn1)
	{
		TransparentBlt(_m_hBuffer, m_rect[0].left, m_rect[0].top, m_size[0].cx*1.5, m_size[0].cy*2, m_hBackBuffer[0], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
		m_efire = burn2;
	}
	else if (m_efire == burn2)
	{
		TransparentBlt(_m_hBuffer, m_rect[1].left, m_rect[1].top, m_size[1].cx*1.5, m_size[1].cy*2, m_hBackBuffer[1], 0, 0, m_size[1].cx, m_size[1].cy, RGB(255, 0, 255));
		m_efire = burn1;
	}

}
void RightFirering::replay()
{
	m_efire = burn1;
	m_rect[0].left = 1335;
	m_rect[0].top = 210;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 2);
	m_rect[1].left = 1335;
	m_rect[1].top = 210;
	m_rect[1].right = m_rect[1].left + (m_size[1].cx * 1.5);
	m_rect[1].bottom = m_rect[1].top + (m_size[1].cy * 2);

	m_crash.left = m_rect[0].left;
	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 2);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + (m_size[0].cx * 0.5);
}

RightFirering::~RightFirering()
{
}

MoneyFirering::MoneyFirering()
{
	m_bScorecheck = true;
	m_rect[0].left = 1780;
	m_rect[0].top = 270;
	m_iScore = 1000;
}

void MoneyFirering::Init(HDC _m_hBuffer, RECT player_rt)
{
	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//cash.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//돈다발
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	GetObject(m_BitMap[0], sizeof(BITMAP), &m_bit[0]);
	m_size[0].cx = m_bit[0].bmWidth;
	m_size[0].cy = m_bit[0].bmHeight;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 2);
}

void MoneyFirering::Update()
{
	if (m_rect[0].left == -200)
	{
		m_bScorecheck = true;
		m_rect[0].left = 1600;
		m_rect[0].right = m_rect[0].left+ (m_size[0].cx * 1.5);
	}
	else
	{
		m_rect[0].left -= 1;
		m_rect[0].right -= 1;
	}
}

void MoneyFirering::Render(HDC _m_hBuffer)
{
	if (m_bScorecheck == true)
	{
		TransparentBlt(_m_hBuffer, m_rect[0].left, m_rect[0].top, m_size[0].cx*1.5, m_size[0].cy * 2.5,
			m_hBackBuffer[0], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
	}	
}

int MoneyFirering::moneyScore()
{
	m_bScorecheck = false;
	return m_iScore;
}
void MoneyFirering::replay()
{
	m_bScorecheck = true;
	m_rect[0].left = 1780;
	m_rect[0].top = 270;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 2);
}

MoneyFirering::~MoneyFirering()
{

}

MoneyrightFirering::MoneyrightFirering()
{
	m_rect[0].left = 1800;
	m_rect[0].top = 210;

	m_crash.left = m_rect[0].left;

}
void MoneyrightFirering::Init(HDC _m_hBuffer, RECT player_rt)
{	

	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//enemy_1f.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 링
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	GetObject(m_BitMap[0], sizeof(BITMAP), &m_bit[0]);
	m_size[0].cx = m_bit[0].bmWidth;
	m_size[0].cy = m_bit[0].bmHeight;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 1.8);

	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 1.8);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + m_size[0].cx;
}

void MoneyrightFirering::Update()
{
	if (m_rect[0].left == -200)
	{
		m_rect[0].left = 1600;
		m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);

		m_crash.left = 1600;
		m_crash.right = m_crash.left + (m_size[0].cx * 1.5);
	}
	else
	{
		m_rect[0].left -= 1;
		m_rect[0].right -= 1;
		m_crash.left -= 1;
		m_crash.right -= 1;
	}
}
void MoneyrightFirering::Render(HDC _m_hBuffer)
{
	TransparentBlt(_m_hBuffer, m_rect[0].left, m_rect[0].top, m_size[0].cx*1.5, m_size[0].cy * 1.8,
		m_hBackBuffer[0], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
}

void MoneyrightFirering::replay()
{
	m_rect[0].left = 1800;
	m_rect[0].top = 210;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 1.8);

	m_crash.left = m_rect[0].left;
	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 1.8);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + m_size[0].cx;
}

MoneyrightFirering::~MoneyrightFirering()
{

}

MoneyleftFirering::MoneyleftFirering()
{
	m_rect[0].left = 1770;
	m_rect[0].top = 210;

	m_crash.left = m_rect[0].left;
	m_bScorecheck = true;
}
void MoneyleftFirering::Init(HDC _m_hBuffer, RECT player_rt)
{
	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//enemy_1b.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//불나는 링
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	GetObject(m_BitMap[0], sizeof(BITMAP), &m_bit[0]);
	m_size[0].cx = m_bit[0].bmWidth;
	m_size[0].cy = m_bit[0].bmHeight;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 1.8);

	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 1.8);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + (m_size[0].cx * 1.5);
}

void MoneyleftFirering::Update()
{
	if (m_rect[0].left == -200)
	{
		m_rect[0].left = 1600;
		m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
		m_bScorecheck = true;
		m_crash.left = 1600;
		m_crash.right = m_crash.left + (m_size[0].cx * 1.5);
	}
	else
	{
		m_rect[0].left -= 1;
		m_rect[0].right -= 1;
		m_crash.left -= 1;
		m_crash.right -= 1;
	}
}

void MoneyleftFirering::Render(HDC _m_hBuffer)
{
	TransparentBlt(_m_hBuffer, m_rect[0].left, m_rect[0].top, m_size[0].cx*1.5, m_size[0].cy * 1.8, 
		m_hBackBuffer[0], 0, 0, m_size[0].cx, m_size[0].cy, RGB(255, 0, 255));
}
int MoneyleftFirering::Score(int player_x)
{
	if (player_x > m_crash.left && m_bScorecheck == true)
	{
		m_iScore = 150;
		m_bScorecheck = false;
		return m_iScore;
	}
	else
	{
		m_iScore = 0;
		return m_iScore;
	}
}

void MoneyleftFirering::replay()
{
	m_rect[0].left = 1770;
	m_rect[0].top = 210;

	m_crash.left = m_rect[0].left;
	m_bScorecheck = true;
	m_rect[0].right = m_rect[0].left + (m_size[0].cx * 1.5);
	m_rect[0].bottom = m_rect[0].top + (m_size[0].cy * 1.8);

	m_crash.bottom = m_rect[0].top + (m_size[0].cy * 1.8);
	m_crash.top = m_crash.bottom - (m_size[0].cy / 3);
	m_crash.right = m_crash.left + (m_size[0].cx * 1.5);
}

MoneyleftFirering::~MoneyleftFirering()
{

}