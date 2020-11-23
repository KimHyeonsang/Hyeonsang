#include "chess.h"



chess::chess()
{
}
void chess::Init(HWND hWnd,int x, int y, LPCWSTR FileName)
{
	HDC hdc = GetDC(hWnd);
	MemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitMap = (HBITMAP)SelectObject(MemDC, m_BitMap);

	BITMAP Bit_Info;

	GetObject(m_BitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;

	Rect.left = x;
	Rect.top = y;
	Rect.right = x + m_size.cx;
	Rect.bottom = y +  m_size.cy;
}

void chess::Draw(HDC hdc)
{
	TransparentBlt(hdc, Rect.left, Rect.top, m_size.cx, m_size.cy,
		MemDC, 0 , 0, m_size.cx , m_size.cy, RGB(255, 0, 255));
}
chess::~chess()
{
}

Phawn::Phawn()
{
	m_iRank = CHESSRANK_PHAWN;
	m_bfirstmove = true;
}
void Phawn::promotion()
{
	
}
void Phawn::Move(int Team, POINT pt)//�⺻������ �����θ� ���� �밢���� ��밡 �������� �밢�� �̵� ����
{
	if (Team == CHESSPAN_WHITE)
	{
		if (m_bfirstmove == true && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y < Rect.top))//ó�� �����̴°��̰� �����°��� ������ �������̸�
		{
			if (pt.y > (Rect.top - m_size.cy * 2) && pt.y < (Rect.top - m_size.cy))//�������� �ι�° ĭ�̸�
			{
				Rect.top -= m_size.cy * 2;
				Rect.bottom -= m_size.cy * 2;
				m_bfirstmove = false;
			}
			else if (pt.y > (Rect.top - m_size.cy) && pt.y < Rect.top)//ù���� ĭ�̸�
			{
				m_bfirstmove = false;
				Rect.top -= m_size.cy;
				Rect.bottom -= m_size.cy;
			}
		}
		else if (m_bfirstmove == false && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y < Rect.top && (pt.y > (Rect.top - m_size.cy))))
		{
			Rect.top -= m_size.cy;
			Rect.bottom -= m_size.cy;
		}
		else if ((pt.x >= Rect.left - m_size.cx && pt.x <= Rect.right - m_size.cx) && (pt.y > (Rect.top - m_size.cy)))
		{
			Rect.top -= m_size.cy;
			Rect.bottom -= m_size.cy;
			Rect.left -= m_size.cx;
			Rect.right -= m_size.cx;
		}
		else if ((pt.x >= Rect.left + m_size.cx && pt.x <= Rect.right + m_size.cx) && (pt.y > (Rect.top - m_size.cy)))
		{
			Rect.top -= m_size.cy;
			Rect.bottom -= m_size.cy;
			Rect.left += m_size.cx;
			Rect.right += m_size.cx;
		}
	}
	else if (Team == CHESSPAN_BLACK)
	{
		if (m_bfirstmove == true && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y > Rect.bottom))//ó�� �����̴°��̰� �����°��� ������ �������̸�
		{
			if (pt.y < (Rect.bottom + m_size.cy * 2) && pt.y > (Rect.bottom + m_size.cy))//�������� �ι�° ĭ�̸�
			{
				Rect.top += m_size.cy * 2;
				Rect.bottom += m_size.cy * 2;
				m_bfirstmove = false;
			}
			else if (pt.y < (Rect.bottom + m_size.cy) && pt.y > Rect.bottom)//ù���� ĭ�̸�
			{
				m_bfirstmove = false;
				Rect.top += m_size.cy;
				Rect.bottom += m_size.cy;
			}
		}
		else if (m_bfirstmove == false && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y > Rect.bottom && (pt.y < (Rect.bottom + m_size.cy))))
		{
			Rect.top += m_size.cy;
			Rect.bottom += m_size.cy;
		}
		else if ((pt.x >= Rect.left - m_size.cx && pt.x <= Rect.right - m_size.cx) && (pt.y > (Rect.top + m_size.cy)))
		{
			Rect.top += m_size.cy;
			Rect.bottom += m_size.cy;
			Rect.left -= m_size.cx;
			Rect.right -= m_size.cx;
		}
		else if ((pt.x >= Rect.left + m_size.cx && pt.x <= Rect.right + m_size.cx)  && (pt.y > (Rect.top + m_size.cy)))
		{
			Rect.top += m_size.cy;
			Rect.bottom += m_size.cy;
			Rect.left += m_size.cx;
			Rect.right += m_size.cx;
		}
	}
}
bool chess::phawnAtack(RECT POINT_RT, RECT rt, int Team)//true�� �̵�����  pt�� ���� ���� rt�� ��� ����ǥ
{	
	if (Team == CHESSPAN_WHITE)
	{
		if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top - m_size.cy)
		{//���� ��
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
		else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top - m_size.cy)
		{//������ ��
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
	}
	else if (Team == CHESSPAN_BLACK)
	{
		if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top + m_size.cy)
		{//���� �Ʒ�
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
		else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top + m_size.cy)
		{//������ �Ʒ�
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
	}
	return false;
}
bool Phawn::MoveCheck(RECT POINT_RT, RECT rt, int Team)//true�� �̵�����  pt�� ���� ���� rt�� ��� ����ǥ
{
	if (Team == CHESSPAN_WHITE)
	{
		if (m_bfirstmove == true && POINT_RT.left == Rect.left && POINT_RT.right == Rect.right && POINT_RT.top >= Rect.top - m_size.cy * 2 && POINT_RT.bottom <= Rect.bottom - m_size.cy)
		{//�������� ���� ��ĭ�ϋ�
			if (POINT_RT.top == rt.top * 2 && POINT_RT.top == rt.bottom && POINT_RT.left == rt.left && POINT_RT.left == rt.right)
				return false;
			else
				return true;
		}
		else if (m_bfirstmove == false && POINT_RT.left == Rect.left && POINT_RT.right == Rect.right && POINT_RT.top == Rect.top - m_size.cy && POINT_RT.bottom == Rect.bottom - m_size.cy)
		{//�������� ���� ��ĭ�ϋ�
			if (POINT_RT.top == rt.top  && POINT_RT.left == rt.left)
				return false;
			else
				return true;
		}
	}
	else if (Team == CHESSPAN_BLACK)
	{
		if (m_bfirstmove == true && POINT_RT.left == Rect.left && POINT_RT.right && POINT_RT.top >= Rect.top + m_size.cy && POINT_RT.bottom <= Rect.bottom + m_size.cy * 2)
		{//�������� �Ʒ��� ��ĭ�ϋ�
			if (POINT_RT.top == rt.top && POINT_RT.bottom == rt.bottom * 2 && POINT_RT.left == rt.left && POINT_RT.right == rt.right)
				return false;
			else
				return true;
		}
		else if (m_bfirstmove == false && POINT_RT.left == Rect.left && POINT_RT.right && POINT_RT.top == Rect.top + m_size.cy && POINT_RT.bottom == Rect.bottom + m_size.cy)
		{//�������� �Ʒ��� ��ĭ�ϋ�
			if (POINT_RT.top == rt.top  && POINT_RT.left == rt.left)
				return false;
			else
				return true;
		}
	}	
	return false;
}


King::King()
{
	m_iRank = CHESSRANK_KING;
}
void King::Move(int Team, POINT pt)//�����¿� ��ĭ�� �̵����� ����Ʈ�� ���� ���� ��ĭ���̵� �̵� �ƴϸ� false
{
	if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) &&(pt.y > Rect.top && pt.y < Rect.bottom ))//�����̵�
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top && pt.y < Rect.bottom))//�������̵�
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
	else if ((pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//�����̵�
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//�Ʒ����̵�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
	}
	else if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//���� ���̵�
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//������ ���̵�
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//������ �Ʒ����̵�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy; 
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//���� �Ʒ����̵�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
}
bool King::MoveCheck(RECT POINT_RT, RECT rt, int Team)//�ڽ��� ���°��� ������ true
{
	if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top)//�����̵�
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top)//�������̵�
		return true;
	else if (POINT_RT.top == Rect.top - m_size.cy  && POINT_RT.left == Rect.left)//�����̵�
		return true;
	else if (POINT_RT.top == Rect.top + m_size.cy  && POINT_RT.left == Rect.left)//�Ʒ����̵�
		return true;
	else if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top - m_size.cy)//���� ���̵�
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top - m_size.cy)//������ ���̵�
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top + m_size.cy)//������ �Ʒ����̵�
		return true;
	else if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top + m_size.cy)//���� �Ʒ����̵�
		return true;
	return false;
}

Knight::Knight()
{
	m_iRank = CHESSRANK_KNIGHT;
}
void Knight::Move(int Team, POINT pt)//����  �� �Ʒ� , ������ ���Ʒ�, �� ���� ��, �Ʒ� ���� ��
{
	if ((pt.x > Rect.left - m_size.cx * 2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//���� ��
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
	}
	else if ((pt.x > Rect.left - m_size.cx *2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//���� �Ʒ�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//������ �Ʒ�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy)) //������ ��
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
	}

	if ((pt.y > Rect.top - m_size.cy * 2 && pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//�� ������
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
	if ((pt.y > Rect.top - m_size.cy * 2&& pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx ))//�� ����
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//�Ʒ� ����
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//�Ʒ� ������
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
}
bool Knight::MoveCheck(RECT POINT_RT, RECT rt, int Team)//�Ʊ��� �Ѿ �ٴҼ� �ִ�
{	//�ڽ��� �̵��Ÿ��� ���
	if (POINT_RT.left == Rect.left - m_size.cx * 2 && POINT_RT.top == Rect.top - m_size.cy )//���� ��
		return true;
	else if (POINT_RT.left == Rect.left - m_size.cx * 2 && POINT_RT.top == Rect.top + m_size.cy)//���� �Ʒ�
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx * 2 && POINT_RT.top == Rect.top - m_size.cy)//���� ��
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx * 2 && POINT_RT.top == Rect.top + m_size.cy)//���� �Ʒ�
		return true;
	else if (POINT_RT.top == Rect.top - m_size.cy * 2  && POINT_RT.left == Rect.left + m_size.cx)//�� ������
		return true;
	else if (POINT_RT.top == Rect.top - m_size.cy * 2 && POINT_RT.left == Rect.left - m_size.cx)//�� ����
		return true;
	else if (POINT_RT.top == Rect.top + m_size.cy * 2 && POINT_RT.left == Rect.left + m_size.cx)//�� ������
		return true;
	else if (POINT_RT.top == Rect.top + m_size.cy * 2 && POINT_RT.left == Rect.left - m_size.cx)//�� ����
		return true;
	return false;
}

Rook::Rook()
{
	m_iRank = CHESSRANK_ROOK;
}

void Rook::Move(int Team, POINT pt) //�� �Ʒ��� �̵� ��� ���� ���� �Ÿ� ������� �ٸ� �ڽ����� ���±濡 ������ �Ѵ°� �Ұ���
{
	int count = 1;
	if (pt.x < Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//�����̵�
	{
		for (int i = 0; i < 8; i++)
		{
			if (pt.x > Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)
			{
				Rect.left -= m_size.cx * count;
				Rect.right -= m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if (pt.x > Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//�������̵�
	{
		for (int i = 0; i < 8; i++)
		{
			if (pt.x > Rect.left + m_size.cx * count && pt.x < Rect.right + m_size.cx * count)
			{
				Rect.left += m_size.cx * count;
				Rect.right += m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if (pt.y < Rect.top && (pt.x > Rect.left && pt.x < Rect.right))//�����̵�
	{
		for (int i = 0; i < 8; i++)
		{			
			if (pt.y > Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count)
			{
				Rect.top -= m_size.cy * count;
				Rect.bottom -= m_size.cy * count;
			}
			else
				count++;
		}
	}
	else if (pt.y > Rect.bottom && (pt.x > Rect.left && pt.x < Rect.right))//�Ʒ����̵�
	{
		for (int i = 0; i < 8; i++)
		{
			if (pt.y > Rect.top + m_size.cy * count && pt.y < Rect.bottom + m_size.cy * count)
			{
				Rect.top += m_size.cy * count;
				Rect.bottom += m_size.cy * count;
			}
			else
				count++;
		}
	}
}
bool Rook::MoveCheck(RECT POINT_RT, RECT rt, int Team)//POINT�� ���� ������ġ rt�� ����ġ  ����������  true
{
	for (int count = 0; count < 8; count++)
	{
		if (POINT_RT.left == Rect.left)//���� ��ġ�� x���� ������
		{//�� �Ʒ�
			if (POINT_RT.top < Rect.top - m_size.cy * count && POINT_RT.bottom < Rect.bottom - m_size.cy * count)//�������� ���� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
					return false;
			}
			else  if (POINT_RT.top > Rect.top + m_size.cy * count && POINT_RT.bottom > Rect.bottom + m_size.cy * count)//�������� �Ʒ��� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
					return false;
			}
		}
		else if (POINT_RT.top == Rect.top)//���� ��ġ�� y���� ������
		{//������ ����
			if (POINT_RT.left < Rect.left - m_size.cx * count && POINT_RT.right < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ����	���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
					return false;
			}
			else  if (POINT_RT.left > Rect.left + m_size.cx * count && POINT_RT.right > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
					return false;
			}
		}
		else  if(POINT_RT.left < Rect.left  && POINT_RT.top < Rect.top)//����
		{
			return false;
		}
		else  if (POINT_RT.left < Rect.left  && POINT_RT.bottom > Rect.bottom)//�޾Ʒ�
		{
			return false;
		}
		else  if (POINT_RT.right > Rect.right  && POINT_RT.top < Rect.top)//������
		{
			return false;
		}
		else  if (POINT_RT.right > Rect.right  && POINT_RT.bottom > Rect.bottom)//�����Ʒ�
		{
			return false;
		}
	}
	return true;
}

Queen::Queen()
{
	m_iRank = CHESSRANK_QUEEN;
}
void Queen::Move(int Team, POINT pt)
{
	int count = 0;
	if (pt.x < Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//�����̵�
	{
		for (int i = 0; i < 8; i++)
		{

			if (pt.x > Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)
			{
				Rect.left -= m_size.cx * count;
				Rect.right -= m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if (pt.x > Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//�������̵�
	{
		for (int i = 0; i < 8; i++)
		{

			if (pt.x > Rect.left + m_size.cx * count && pt.x < Rect.right + m_size.cx * count)
			{
				Rect.left += m_size.cx * count;
				Rect.right += m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if (pt.y < Rect.top && (pt.x > Rect.left && pt.x < Rect.right))//�����̵�
	{
		for (int i = 0; i < 8; i++)
		{

			if (pt.y > Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count)
			{
				Rect.top -= m_size.cy * count;
				Rect.bottom -= m_size.cy * count;
			}
			else
				count++;
		}
	}
	else if (pt.y > Rect.bottom && (pt.x > Rect.left && pt.x < Rect.right))//�Ʒ����̵�
	{
		for (int i = 0; i < 8; i++)
		{
			if (pt.y > Rect.top + m_size.cy * count && pt.y < Rect.bottom + m_size.cy * count)
			{
				Rect.top += m_size.cy * count;
				Rect.bottom += m_size.cy * count;
			}
			else
				count++;
		}
	}
	if ((pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count) && (pt.y > Rect.top + m_size.cy * count && pt.y > Rect.bottom + m_size.cy*count))
	{//�����Ʒ�
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left + m_size.cx * count && pt.x < Rect.right + m_size.cx * count) && (pt.y > Rect.top + m_size.cy * count && pt.y < Rect.bottom + m_size.cy * count))
			{
				Rect.top += m_size.cy * count;
				Rect.bottom += m_size.cy * count;
				Rect.left += m_size.cx * count;
				Rect.right += m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if ((pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count) && (pt.y < Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy*count))
	{//������
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left + m_size.cx * count && pt.x < Rect.right + m_size.cx * count) && (pt.y > Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count))
			{
				Rect.top -= m_size.cy * count;
				Rect.bottom -= m_size.cy * count;
				Rect.left += m_size.cx * count;
				Rect.right += m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if ((pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y < Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count))
	{//������
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y > Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count))
			{
				Rect.top -= m_size.cy * count;
				Rect.bottom -= m_size.cy * count;
				Rect.left -= m_size.cx * count;
				Rect.right -= m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if ((pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y > Rect.top - m_size.cy * count && pt.y > Rect.bottom - m_size.cy * count))
	{//���ʾƷ�
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y > Rect.top + m_size.cy * count && pt.y < Rect.bottom + m_size.cy * count))
			{
				Rect.top += m_size.cy * count;
				Rect.bottom += m_size.cy * count;
				Rect.left -= m_size.cx * count;
				Rect.right -= m_size.cx * count;
			}
			else
				count++;
		}
	}
}
bool Queen::MoveCheck(RECT POINT_RT, RECT rt, int Team)
{
	int count = 0;
	while (1)//��, �Ʒ�, ����, ���� ,������ ,�����Ʒ� ,������, ���ʾƷ�
	{
		if (POINT_RT.left== Rect.left)//���� ��ġ�� x���� ������
		{//�� �Ʒ�
			if (POINT_RT.top < Rect.top - m_size.cy * count && POINT_RT.bottom < Rect.bottom - m_size.cy * count)//�������� ���� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
					return false;
			}
			else  if (POINT_RT.top > Rect.top + m_size.cy * count && POINT_RT.bottom > Rect.bottom + m_size.cy * count)//�������� �Ʒ��� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
					return false;
			}
			
		}
		else if (POINT_RT.top == Rect.top)//���� ��ġ�� y���� ������
		{//������ ����
			if (POINT_RT.left < Rect.left - m_size.cx * count && POINT_RT.right < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ����	���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
					return false;
			}
			else  if (POINT_RT.left > Rect.left + m_size.cx * count && POINT_RT.right > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
					return false;
			}			
		}
		else if (POINT_RT.top <= Rect.top && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))
		{//�������밢��
			if (POINT_RT.top == Rect.top - m_size.cy * count  && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		else if ((POINT_RT.top <= Rect.top && POINT_RT.bottom < Rect.bottom) && POINT_RT.left >= Rect.left)
		{//���������밢��	
			if (POINT_RT.top == Rect.top - m_size.cy * count  && POINT_RT.left == Rect.left + m_size.cx * count)
				return true;			
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		else if ((POINT_RT.top >= Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))//���� ��ġ�� �̵�ĳ������ y���� ũ�� (�Ʒ�)
		{//���ʾƷ��밢��
			if (POINT_RT.top == Rect.top + m_size.cy * count  && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;		
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		else if ((POINT_RT.top >= Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left > Rect.left && POINT_RT.right > Rect.right))//���� ��ġ�� �̵�ĳ������ y���� ũ�� (�Ʒ�)
		{//�����ʾƷ��밢��
			if (POINT_RT.top == Rect.top + m_size.cy * count && POINT_RT.left == Rect.left + m_size.cx * count)
				return true;			
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		if (count > 8)
			return true;
		
		count++;
			
	}
}

Bishop::Bishop()
{
	m_iRank = CHESSRANK_BISHOP;
}
void Bishop::Move(int Team, POINT pt)//�밢�� �̵�
{
	int count = 0;
	if ((pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count) && (pt.y > Rect.top + m_size.cy * count && pt.y > Rect.bottom + m_size.cy*count))
	{//�����Ʒ�
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left + m_size.cx * count && pt.x < Rect.right + m_size.cx * count) && (pt.y > Rect.top + m_size.cy * count && pt.y < Rect.bottom + m_size.cy * count))
			{
				Rect.top += m_size.cy * count;
				Rect.bottom += m_size.cy * count;
				Rect.left  += m_size.cx * count;
				Rect.right += m_size.cx * count;
			}
			else
				count++;
		}		
	}
	else if ((pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count) && (pt.y < Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy*count))
	{//������
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left + m_size.cx * count && pt.x < Rect.right + m_size.cx * count) && (pt.y > Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count))
			{
				Rect.top -= m_size.cy * count;
				Rect.bottom -= m_size.cy * count;
				Rect.left += m_size.cx * count;
				Rect.right += m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if ((pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y < Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count))
	{//������
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y > Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count))
			{
				Rect.top -= m_size.cy * count;
				Rect.bottom -= m_size.cy * count;
				Rect.left -= m_size.cx * count;
				Rect.right -= m_size.cx * count;
			}
			else
				count++;
		}
	}
	else if ((pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y > Rect.top - m_size.cy * count && pt.y > Rect.bottom - m_size.cy * count))
	{//���ʾƷ�
		for (int i = 0; i < 8; i++)
		{
			if ((pt.x > Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count) && (pt.y > Rect.top + m_size.cy * count && pt.y < Rect.bottom + m_size.cy * count))
			{
				Rect.top += m_size.cy * count;
				Rect.bottom += m_size.cy * count;
				Rect.left -= m_size.cx * count;
				Rect.right -= m_size.cx * count;
			}
			else
				count++;
		}
	}
}
bool Bishop::MoveCheck(RECT POINT_RT, RECT rt, int Team)
{
	int count = 0;
	while (1)//4���븦 �Ѵ�
	{
		if (POINT_RT.left == Rect.left)//���� ��ġ�� x���� ������
		{//�� �Ʒ�
			if (POINT_RT.top < Rect.top - m_size.cy * count && POINT_RT.bottom < Rect.bottom - m_size.cy * count)//�������� ���� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
					return false;
			}
			else  if (POINT_RT.top > Rect.top + m_size.cy * count && POINT_RT.bottom > Rect.bottom + m_size.cy * count)//�������� �Ʒ��� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
					return false;
			}

		}
		else if (POINT_RT.top == Rect.top)//���� ��ġ�� y���� ������
		{//������ ����
			if (POINT_RT.left < Rect.left - m_size.cx * count && POINT_RT.right < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ����	���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
					return false;
			}
			else  if (POINT_RT.left > Rect.left + m_size.cx * count && POINT_RT.right > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
					return false;
			}
		}
		else if ((POINT_RT.top < Rect.top && POINT_RT.bottom < Rect.bottom) && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))
		{//�������밢��
			if (POINT_RT.top == Rect.top - m_size.cy * count && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		else if ((POINT_RT.top < Rect.top && POINT_RT.bottom < Rect.bottom) && (POINT_RT.left > Rect.left && POINT_RT.right > Rect.right))
		{//�����ʴ밢��	
			if (POINT_RT.top == Rect.top - m_size.cy * count && POINT_RT.left == Rect.left + m_size.cx * count )
				return true;
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		else if ((POINT_RT.top > Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))//���� ��ġ�� �̵�ĳ������ y���� ũ�� (�Ʒ�)
		{//���ʾƷ��밢��
			if (POINT_RT.top == Rect.top + m_size.cy * count  && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		else if ((POINT_RT.top > Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left > Rect.left && POINT_RT.right > Rect.right))//���� ��ġ�� �̵�ĳ������ y���� ũ�� (�Ʒ�)
		{//�����ʾƷ��밢��
			if (POINT_RT.top == Rect.top + m_size.cy * count && (POINT_RT.left == Rect.left + m_size.cx * count))
				return true;
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				return false;
		}
		if (count > 8)
			return false;
		
		count++;
	}	
}