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
bool Phawn::Move(int Team, POINT pt, vector<chess*>*enemy)//�⺻������ �����θ� ���� �밢���� ��밡 �������� �밢�� �̵� ����
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
				return true;
			}
			else if (pt.y > (Rect.top - m_size.cy) && pt.y < Rect.top)//ù���� ĭ�̸�
			{
				m_bfirstmove = false;
				Rect.top -= m_size.cy;
				Rect.bottom -= m_size.cy;
				return true;
			}
		}
		else if (m_bfirstmove == false && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y < Rect.top && (pt.y > (Rect.top - m_size.cy))))
		{
			Rect.top -= m_size.cy;
			Rect.bottom -= m_size.cy;
			return true;
		}
		//�����̶� ������ ������ ����
		for (enemy_iter = enemy->begin(); enemy_iter != enemy->end(); enemy_iter++)
		{
			m_Enemy = *enemy_iter;
			if (PtInRect(&m_Enemy->Rt(), pt))//����� �ٴ���ġ�߿� ���콺��ġ�� �浹�� �ϸ�
			{
				if (Rect.left - m_size.cx == m_Enemy->Rt_x() && Rect.top - m_size.cy == m_Enemy->Rt_y())
				{
					Rect.top -= m_size.cy;
					Rect.bottom -= m_size.cy;
					Rect.left -= m_size.cx;
					Rect.right -= m_size.cx;
					return true;
				}
				else if (Rect.left + m_size.cx == m_Enemy->Rt_x() && Rect.top - m_size.cy == m_Enemy->Rt_y())
				{
					Rect.top -= m_size.cy;
					Rect.bottom -= m_size.cy;
					Rect.left += m_size.cx;
					Rect.right += m_size.cx;
					return true;
				}								
			}
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
				return true;
			}
			else if (pt.y < (Rect.bottom + m_size.cy) && pt.y > Rect.bottom)//ù���� ĭ�̸�
			{
				m_bfirstmove = false;
				Rect.top += m_size.cy;
				Rect.bottom += m_size.cy;
				return true;
			}
		}
		else if (m_bfirstmove == false && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y > Rect.bottom && (pt.y < (Rect.bottom + m_size.cy))))
		{
			Rect.top += m_size.cy;
			Rect.bottom += m_size.cy;
			return true;
		}
		for (enemy_iter = enemy->begin(); enemy_iter != enemy->end(); enemy_iter++)
		{
			m_Enemy = *enemy_iter;
			if (PtInRect(&m_Enemy->Rt(), pt))//����� �ٴ���ġ�߿� ���콺��ġ�� �浹�� �ϸ�
			{
				if (Rect.left - m_size.cx == m_Enemy->Rt_x() && Rect.top + m_size.cy == m_Enemy->Rt_y())
				{
					Rect.top += m_size.cy;
					Rect.bottom += m_size.cy;
					Rect.left -= m_size.cx;
					Rect.right -= m_size.cx;
					return true;
				}
				else if (Rect.left + m_size.cx == m_Enemy->Rt_x() && Rect.top + m_size.cy == m_Enemy->Rt_y())
				{
					Rect.top += m_size.cy;
					Rect.bottom += m_size.cy;
					Rect.left += m_size.cx;
					Rect.right += m_size.cx;
					return true;
				}				
			}
		}
	}
	return false;
}
bool Phawn::MoveCheck(POINT pt, RECT rt)//true�� �̵��Ұ�  pt�� ���� ���� rt�� ��� ����ǥ
{
	if (pt.x >= Rect.left && pt.x <= Rect.right)//���� ��ġ�� ���� ������ ����x���� ������
	{
		if ((pt.y >= rt.top && pt.y <= rt.bottom) && (pt.x >= rt.left && pt.x <= rt.right))//������ġ�� ������ �ű⿡ ������ 
		{
			return true;
		}		
	}
	else
		return false;
	
}

bool Phawn::checkmateCheck(RECT EnemyKing_rt)
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//���տ� ���±濡 �����̴¸��� ������� �Ʒ������� �������
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//���±濡 �����̴¸��� ������� �Ʒ����� �������
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy)//���±濡 �����̴¸��� ������� �������� �������
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy)//���±濡 �����̴¸��� ������� �������� �������
	{
		return true;
	}
}

bool Phawn::checkmate(RECT EnemyKing_rt, RECT Team_rt)
{
	return false;
}

King::King()
{
	m_iRank = CHESSRANK_KING;
}
bool King::Move(int Team, POINT pt, vector<chess*>*enemy)//�����¿� ��ĭ�� �̵����� ����Ʈ�� ���� ���� ��ĭ���̵� �̵� �ƴϸ� false
{
	if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) &&(pt.y > Rect.top && pt.y < Rect.bottom ))//�����̵�
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top && pt.y < Rect.bottom))//�������̵�
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	else if ((pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//�����̵�
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		return true;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//�Ʒ����̵�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		return true;
	}
	else if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//���� ���̵�
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//������ ���̵�
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		return true;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//������ �Ʒ����̵�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy; 
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//���� �Ʒ����̵�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		return true;
	}
	return false;
}
bool King::MoveCheck(POINT pt, RECT rt)
{
	if (pt.x > rt.left && pt.x < rt.right)//���� ��ġ��x���� ����
	{
		//���� ��ġ�� 
		if (pt.y < Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy)
		{
			if (Rect.top - m_size.cy == rt.top)
			{
				return true;
			}
		}
		else if (pt.y > Rect.top + m_size.cy && pt.y > Rect.bottom + m_size.cy)
		{
			if (Rect.top + m_size.cy == rt.top)
			{
				return true;
			}
		}
	}
	else if (pt.y > rt.top && pt.y < rt.bottom)
	{
		//y���� �ٸ����
		if (pt.x < Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx)
		{
			if (Rect.left - m_size.cx == rt.left)
			{
				return true;
			}
		}
		else if (pt.x > Rect.left + m_size.cx && pt.x > Rect.right + m_size.cx)
		{
			if (Rect.left + m_size.cx == rt.left)
			{
				return true;
			}
		}
	}
	return false;
}

bool King::checkmateCheck(RECT EnemyKing_rt)//������ �����̴¹����ȿ��ִ°�
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//���տ� ���±濡 �����̴¸��� ������� �Ʒ������� �������
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//���±濡 �����̴¸��� ������� �Ʒ����� �������
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy)//���±濡 �����̴¸��� ������� �������� �������
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy)//���±濡 �����̴¸��� ������� �������� �������
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx  && EnemyKing_rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
		{
			return true;
		}
	else if (EnemyKing_rt.top == Rect.top - m_size.cy  && EnemyKing_rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
		{
			return true;
		}
	else if (EnemyKing_rt.top == Rect.top + m_size.cy  && EnemyKing_rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
		{
			return true;
		}
}

bool King::checkmate(RECT EnemyKing_rt, RECT Team_rt)//�����̴¹��⿡ �Ʊ������� �ִ°� ������ üũ����Ʈ â�� ���� �ʴ´�.
{
	return false;
}
Knight::Knight()
{
	m_iRank = CHESSRANK_KNIGHT;
}
bool Knight::Move(int Team, POINT pt, vector<chess*>*enemy)//����  �� �Ʒ� , ������ ���Ʒ�, �� ���� ��, �Ʒ� ���� ��
{
	if ((pt.x > Rect.left - m_size.cx * 2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//���� ��
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
		return true;
	}
	else if ((pt.x > Rect.left - m_size.cx *2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//���� �Ʒ�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//������ �Ʒ�
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy)) //������ ��
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
		return true;
	}

	if ((pt.y > Rect.top - m_size.cy * 2 && pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//�� ������
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	if ((pt.y > Rect.top - m_size.cy * 2&& pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx ))//�� ����
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		return true;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//�Ʒ� ����
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		return true;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//�Ʒ� ������
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	return false;
}
bool Knight::MoveCheck(POINT pt, RECT rt)//�Ʊ��� �Ѿ �ٴҼ� �ִ�
{	//�ڽ��� �̵��Ÿ��� ���
	return false;
}

bool Knight::checkmateCheck(RECT EnemyKing_rt)//������ġ�� ������ �������
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //���� �� ���±濡 �����ִ�.
	{
		return true;
	}
	else if(EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //���� �Ʒ�  ���±濡 �����ִ�.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //������ �Ʒ� ���±濡 �����ִ�.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //������ �� ���±濡 �����ִ�.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //�� �����ε� ���±濡 �����ִ�.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //�� ������ ���±濡 �����ִ�.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //�Ʒ� ���� ���±濡 �����ִ�.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //�Ʒ� ������ ���±濡 �����ִ�.
	{
		return true;
	}
}
bool Knight::checkmate(RECT EnemyKing_rt, RECT Team_rt)
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //���� �� ���±濡 �����ִ�.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //���� �Ʒ�  ���±濡 �����ִ�.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //������ �Ʒ� ���±濡 �����ִ�.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //������ �� ���±濡 �����ִ�.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //�� �����ε� ���±濡 �����ִ�.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //�� ������ ���±濡 �����ִ�.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //�Ʒ� ���� ���±濡 �����ִ�.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //�Ʒ� ������ ���±濡 �����ִ�.
	{
		return false;
	}
}
Rook::Rook()
{
	m_iRank = CHESSRANK_ROOK;
}

bool Rook::Move(int Team, POINT pt, vector<chess*>*enemy) //�� �Ʒ��� �̵� ��� ���� ���� �Ÿ� ������� �ٸ� �ڽ����� ���±濡 ������ �Ѵ°� �Ұ���
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
		return true;
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
		return true;
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
		return true;
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
		return true;
	}
	return false;
}
bool Rook::MoveCheck(POINT pt, RECT rt)//POINT�� ���� ������ġ rt�� ����ġ
{
	int count = 0;
	while (1)//�ݺ��� �ϴ� ������ ���� ������ �Ÿ��� ���� �ִ��� ������ Ȯ���ϱ� ����
	{
		if (pt.x >= rt.left && pt.x <= rt.right)//���� ��ġ��x���� ����
		{
			//���� ��ġ�� 
			if (pt.y < Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count)
			{
				if (Rect.top - m_size.cy * count == rt.top)
				{
					return true;
				}
				count++;
			}
			else if (pt.y > Rect.top + m_size.cy * count && pt.y > Rect.bottom + m_size.cy * count)
			{
				if (Rect.top + m_size.cy * count == rt.top)
				{
					return true;
				}
				count++;
			}
			else if (pt.y >= Rect.top + m_size.cy * count && pt.y <= Rect.bottom + m_size.cy * count)
			{
				return false;
			}
			else if (pt.y >= Rect.top - m_size.cy * count && pt.y <= Rect.bottom - m_size.cy * count)
			{
				return false;
			}
		}
		else if (pt.y >= rt.top && pt.y <= rt.bottom)
		{
			//y���� �ٸ����
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)
			{
				if (Rect.left - m_size.cx * count == rt.left)
				{
					return true;
				}
				count++;
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)
			{
				if (Rect.left + m_size.cx * count == rt.left)
				{
					return true;
				}
				count++;
			}
			else if (pt.x >= Rect.left + m_size.cx * count && pt.x <= Rect.right + m_size.cx * count)
			{
				return false;
			}
			else if (pt.x >= Rect.left - m_size.cx * count && pt.x <= Rect.right - m_size.cx * count)
			{
				return false;
			}
		}
		else
			return false;
	}	
}
bool Rook::checkmateCheck(RECT EnemyKing_rt)
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
		{
			return true;
		}
	}
}
bool Rook::checkmate(RECT EnemyKing_rt, RECT Team_rt)
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left <= Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left >= Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top <= Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
		{
			if (Team_rt.top == Rect.top - m_size.cy * count && Team_rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top >= Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
		{
			if (Team_rt.top == Rect.top + m_size.cy * count && Team_rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
	}
}
Queen::Queen()
{
	m_iRank = CHESSRANK_QUEEN;
}
bool Queen::Move(int Team, POINT pt, vector<chess*>*enemy)
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
		return true;
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
		return true;
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
		return true;
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
		return true;
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
				return true;
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
				return true;
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
				return true;
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
				return true;
			}
			else
				count++;
		}
	}
	return false;
}
bool Queen::MoveCheck(POINT pt, RECT rt)
{
	int count = 0;
	while (1)//��, �Ʒ�, ����, ���� ,������ ,�����Ʒ� ,������, ���ʾƷ�
	{
		if ((pt.x > Rect.left && pt.x < Rect.right))//���� ��ġ�� x���� ������
		{//�� �Ʒ�
			if (pt.y < Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count)//�������� ���� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
				{
					return true;
				}
			}
			else  if (pt.y > Rect.top + m_size.cy * count && pt.y > Rect.bottom + m_size.cy * count)//�������� �Ʒ��� �ö󰡴°ͺ��� Ŭ���
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
				{
					return true;
				}
			}
			
		}
		else if ((pt.y > Rect.top && pt.y < Rect.bottom))//���� ��ġ�� y���� ������
		{//������ ����
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ����	���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
				{
					return true;
				}
			}
			else  if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
				{
					return true;
				}
			}			
			
		}
		else if ((pt.y < Rect.top && pt.y < Rect.bottom))//���� ��ġ�� �̵�ĳ������ y���� �۴� ( ��)
		{//���밢��
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ���� ���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
		}
		else if ((pt.y > Rect.top && pt.y > Rect.bottom))//���� ��ġ�� �̵�ĳ������ y���� ũ�� (�Ʒ�)
		{//�Ʒ��밢��
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ���� ���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
		}

		if (count > 8)
			return false;
		
		count++;
			
	}
}
bool Queen::checkmateCheck(RECT EnemyKing_rt)
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//���տ� ���±濡 �����̴¸��� ������� �Ʒ������� �������
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �Ʒ����� �������
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
		{
			return true;
		}
	}
}
bool Queen::checkmate(RECT EnemyKing_rt, RECT Team_rt)//�Ʊ�,����
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//�����ǿհ� �����̴¸��� ������� �Ʒ������� �������
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//���տ� ���±濡 �����̴¸��� ������� �Ʒ������� �������
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �Ʒ������� �������
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �Ʒ����� �������
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top) //�����ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top)//�������ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top <= Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
		{
			if (Team_rt.top == Rect.top - m_size.cy * count && Team_rt.left == Rect.left)//�����ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top >= Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
		{
			if (Team_rt.top == Rect.top + m_size.cy * count && Team_rt.left == Rect.left)//�Ʒ����ε� ���±濡 �����ִ�.
			{
				return true;
			}
		}
	}
}

Bishop::Bishop()
{
	m_iRank = CHESSRANK_BISHOP;
}
bool Bishop::Move(int Team, POINT pt, vector<chess*>*enemy)//�밢�� �̵�
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
				return true;
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
				return true;
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
				return true;
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
				return true;
			}
			else
				count++;
		}
	}
	return false;
}
bool Bishop::MoveCheck(POINT pt, RECT rt)
{
	int count = 0;
	while (1)//4���븦 �Ѵ�
	{
		if ((pt.y < Rect.top && pt.y < Rect.bottom))//���� ��ġ�� �̵�ĳ������ y���� �۴� ( ��)
		{//���밢��
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ���� ���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
		}
		else if ((pt.y > Rect.top && pt.y > Rect.bottom))//���� ��ġ�� �̵�ĳ������ y���� ũ�� (�Ʒ�)
		{//�Ʒ��밢��
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//�������� x���� �̵�ĳ�� ���� ���ʿ� �������
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//�������� x���� �̵�ĳ�� ���� �����ʿ� �������
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
				{
					return true;
				}
			}
		}
		if (count > 8)
			return false;
		
		count++;
	}	
}
bool Bishop::checkmateCheck(RECT EnemyKing_rt)
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//���տ� ���±濡 �����̴¸��� ������� �Ʒ������� �������
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �Ʒ����� �������
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			return true;
		}
	}
}
bool Bishop::checkmate(RECT EnemyKing_rt, RECT Team_rt)
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//�����ǿհ� �����̴¸��� ������� �Ʒ������� �������
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//���տ� ���±濡 �����̴¸��� ������� �Ʒ������� �������
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �Ʒ������� �������
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//���±濡 �����̴¸��� ������� �Ʒ����� �������
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//���±濡 �����̴¸��� ������� �������� �������
			{
				return true;
			}
		}
	}
}