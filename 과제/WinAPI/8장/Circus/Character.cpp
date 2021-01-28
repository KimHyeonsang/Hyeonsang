#include "Character.h"



Character::Character()
{
	m_state = WALK1;
	m_iHartcount = 3;
	m_iJumPower = 25;
	m_dwLastTime = GetTickCount();;
	m_dwCurTime = GetTickCount();;
	m_fDeltaTime;
}

void Character::Init(HWND hWnd,HDC _m_hBuffer)
{
	m_hWnd = hWnd;
	m_hBackBuffer[0] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[0] = (HBITMAP)LoadImage(NULL, "RES//player0.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//�÷��̾�
	m_OldBitMap[0] = (HBITMAP)SelectObject(m_hBackBuffer[0], m_BitMap[0]);
	BITMAP bit;
	GetObject(m_BitMap[0], sizeof(BITMAP), &bit);
	m_size.cx = bit.bmWidth;
	m_size.cy = bit.bmHeight;

	m_hBackBuffer[1] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[1] = (HBITMAP)LoadImage(NULL, "RES//player2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//�÷��̾� ����
	m_OldBitMap[1] = (HBITMAP)SelectObject(m_hBackBuffer[1], m_BitMap[1]);
	GetObject(m_BitMap[1], sizeof(BITMAP), &bit);
	m_size.cx = bit.bmWidth;
	m_size.cy = bit.bmHeight;

	m_hBackBuffer[2] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[2] = (HBITMAP)LoadImage(NULL, "RES//player1.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//�÷��̾� �޸���
	m_OldBitMap[2] = (HBITMAP)SelectObject(m_hBackBuffer[2], m_BitMap[2]);
	GetObject(m_BitMap[2], sizeof(BITMAP), &bit);
	m_size.cx = bit.bmWidth;
	m_size.cy = bit.bmHeight;

	m_hBackBuffer[3] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[3] = (HBITMAP)LoadImage(NULL, "RES//icon.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//�÷��̾���
	m_OldBitMap[3] = (HBITMAP)SelectObject(m_hBackBuffer[3], m_BitMap[3]);
	GetObject(m_BitMap[3], sizeof(BITMAP), &m_bithart);

	m_hBackBuffer[4] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[4] = (HBITMAP)LoadImage(NULL, "RES//win.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//�÷��̾� �¸� ����1
	m_OldBitMap[4] = (HBITMAP)SelectObject(m_hBackBuffer[4], m_BitMap[4]);
	GetObject(m_BitMap[4], sizeof(BITMAP), &m_bitWin);

	m_hBackBuffer[5] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[5] = (HBITMAP)LoadImage(NULL, "RES//win2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//�÷��̾� �¸� ����2
	m_OldBitMap[5] = (HBITMAP)SelectObject(m_hBackBuffer[5], m_BitMap[5]);
	GetObject(m_BitMap[5], sizeof(BITMAP), &m_bitWin);

	m_Winsize.cx = m_bitWin.bmWidth;
	m_Winsize.cy = m_bitWin.bmHeight;

	m_hBackBuffer[6] = CreateCompatibleDC(_m_hBuffer);
	m_BitMap[6] = (HBITMAP)LoadImage(NULL, "RES//die.bmp", IMAGE_BITMAP, 0, 0,
	LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);//�÷��̾� ����
	m_OldBitMap[6] = (HBITMAP)SelectObject(m_hBackBuffer[6], m_BitMap[6]);
	GetObject(m_BitMap[6], sizeof(BITMAP), &m_bitdie);

	m_Diesize.cx = m_bitdie.bmWidth;
	m_Diesize.cy = m_bitdie.bmHeight;

	m_hart.cx = m_bithart.bmWidth;
	m_hart.cy = m_bithart.bmHeight;
	m_MoveSpeed = 40;
	m_rect.left = 100;
	m_rect.top = 450;
	m_rect.right = m_rect.left + m_size.cx;
	m_rect.bottom = m_rect.top + m_size.cy;
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
		for (int i = 0; i < m_iHartcount; i++)  //�������
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

void Character::PlayerKey(float time,int miter) //���� Ű�� ���� ���� ��ȭ
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
		if (miter == FINISH)
		{
			m_rect.left -= m_MoveSpeed * time;
			m_rect.right -= m_MoveSpeed * time;
			m_ibefore_x = m_rect.left;
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
			m_rect.left = m_rect.right - m_size.cx;
			m_rect.right = 1200;
		}
		if (miter == FINISH || m_rect.left <= 100)
		{
			m_rect.left += m_MoveSpeed * time;
			m_rect.right += m_MoveSpeed * time;
			m_ibefore_x = m_rect.left;
		}
	}
	else if (m_state != JUMP)
		m_Direction = IDLE;
	if (GetKeyState(VK_SPACE) & 0x8000 && m_state != JUMP)//���� �����϶��� �ѹ��� ������ �Ұ����ϰ� ��������
	{
		m_state = JUMP;
	}
}

void Character::Update(float time,int miter)
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwLastTime) / 150.0f;
	PlayerKey(time, miter);
	if (m_state == JUMP)
	{
		if (m_rect.top <= 450)
		{
			m_rect.top = m_fDeltaTime * m_fDeltaTime - m_iJumPower * m_fDeltaTime + 450;
			m_rect.bottom = m_fDeltaTime * m_fDeltaTime - m_iJumPower * m_fDeltaTime + m_rect.top + m_size.cy;
		}
		else if (m_rect.top >= 450)
		{
			m_rect.top = 450;
			m_rect.bottom = m_rect.top + +m_size.cy;
			m_state = WALK1;
			m_dwLastTime = m_dwCurTime;
		}		

		if (m_Direction == LEFT)
		{
			if (m_rect.left <= 0)
			{
				m_rect.left = 0;
				m_rect.right = m_rect.left + m_size.cx;
			}
		}
		else if (m_Direction == RIGHT)
		{
			if (m_rect.right >= 1200)
			{
				m_rect.left = m_rect.right - m_size.cx;
				m_rect.right = 1200;
			}
			if (miter == FINISH)
			{
				m_rect.left += m_MoveSpeed * time;
				m_rect.right += m_MoveSpeed * time;
			}
		}
	}
	else
	{
		m_dwLastTime = m_dwCurTime;
	}
}

void Character::endlocation()//��������ġ
{
	m_rect.top -= 60;
	m_rect.bottom -= 60;
	m_state = WIN;
}

void Character::replay()
{
	m_iHartcount = 3;
	m_state = WALK1;
	m_rect.left = 100;
	m_rect.right = m_rect.left + m_size.cx;
}

void Character::DamageMotion()//ü���� �������� �ൿ
{
	//�ڷ� ������� �̵��ϸ� �������

	if(m_rect.left <= 50 || m_rect.left + 80 <= m_ibefore_x) //�̰Ÿ� �Ʒ��ϋ� �������
		m_state = WALK1;
	m_rect.top = 450;
	if (m_rect.left >= 50) //�̰Ÿ� �̻��ϋ� ����
	{
		m_rect.left -= m_MoveSpeed;
		m_rect.right -= m_MoveSpeed;
	}	
	m_rect.bottom = m_rect.top + m_size.cy;
}

Character::~Character()
{
}
