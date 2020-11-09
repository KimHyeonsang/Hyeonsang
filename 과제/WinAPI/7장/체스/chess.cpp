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
bool Phawn::Move(int Team, POINT pt, vector<chess*>*enemy)//기본적으로 앞으로만 전진 대각선에 상대가 있을때는 대각선 이동 가능
{
	if (Team == CHESSPAN_WHITE)
	{
		if (m_bfirstmove == true && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y < Rect.top))//처음 움직이는것이고 누르는곳이 말보다 작은곳이면
		{
			if (pt.y > (Rect.top - m_size.cy * 2) && pt.y < (Rect.top - m_size.cy))//누른곳이 두번째 칸이면
			{
				Rect.top -= m_size.cy * 2;
				Rect.bottom -= m_size.cy * 2;
				m_bfirstmove = false;
				return true;
			}
			else if (pt.y > (Rect.top - m_size.cy) && pt.y < Rect.top)//첫번쨰 칸이면
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
		//적팀이랑 갈곳에 같으면 삭제
		for (enemy_iter = enemy->begin(); enemy_iter != enemy->end(); enemy_iter++)
		{
			m_Enemy = *enemy_iter;
			if (PtInRect(&m_Enemy->Rt(), pt))//저장된 바닥위치중에 마우스위치와 충돌을 하면
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
		if (m_bfirstmove == true && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y > Rect.bottom))//처음 움직이는것이고 누르는곳이 말보다 작은곳이면
		{
			if (pt.y < (Rect.bottom + m_size.cy * 2) && pt.y > (Rect.bottom + m_size.cy))//누른곳이 두번째 칸이면
			{
				Rect.top += m_size.cy * 2;
				Rect.bottom += m_size.cy * 2;
				m_bfirstmove = false;
				return true;
			}
			else if (pt.y < (Rect.bottom + m_size.cy) && pt.y > Rect.bottom)//첫번쨰 칸이면
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
			if (PtInRect(&m_Enemy->Rt(), pt))//저장된 바닥위치중에 마우스위치와 충돌을 하면
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
bool Phawn::MoveCheck(POINT pt, RECT rt)//true면 이동불가  pt는 내가 갈곳 rt는 모든 말좌표
{
	if (pt.x >= Rect.left && pt.x <= Rect.right)//누른 위치랑 내가 움직을 말의x축이 같을떄
	{
		if ((pt.y >= rt.top && pt.y <= rt.bottom) && (pt.x >= rt.left && pt.x <= rt.right))//누른위치와 팀원이 거기에 있으면 
		{
			return true;
		}		
	}
	else
		return false;
	
}

bool Phawn::checkmateCheck(RECT EnemyKing_rt)
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//적왕에 가는길에 움직이는말과 왼쪽축과 아래쪽축이 같을경우
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//가는길에 움직이는말과 오른축과 아래쪽이 같을경우
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
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
bool King::Move(int Team, POINT pt, vector<chess*>*enemy)//상하좌우 한칸씩 이동가능 포인트를 찍은 곳이 한칸씩이동 이동 아니면 false
{
	if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) &&(pt.y > Rect.top && pt.y < Rect.bottom ))//왼쪽이동
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top && pt.y < Rect.bottom))//오른쪽이동
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	else if ((pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//위쪽이동
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		return true;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//아랫쪽이동
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		return true;
	}
	else if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//왼쪽 위이동
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//오른쪽 위이동
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		return true;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//오른쪽 아래쪽이동
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy; 
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//왼쪽 아랫쪽이동
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
	if (pt.x > rt.left && pt.x < rt.right)//가는 위치의x축이 같고
	{
		//나의 위치가 
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
		//y축이 다를경우
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

bool King::checkmateCheck(RECT EnemyKing_rt)//상대왕이 움직이는범위안에있는가
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//적왕에 가는길에 움직이는말과 왼쪽축과 아래쪽축이 같을경우
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy)//가는길에 움직이는말과 오른축과 아래쪽이 같을경우
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx  && EnemyKing_rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
		{
			return true;
		}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
		{
			return true;
		}
	else if (EnemyKing_rt.top == Rect.top - m_size.cy  && EnemyKing_rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
		{
			return true;
		}
	else if (EnemyKing_rt.top == Rect.top + m_size.cy  && EnemyKing_rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
		{
			return true;
		}
}

bool King::checkmate(RECT EnemyKing_rt, RECT Team_rt)//움직이는방향에 아군적군이 있는가 있으면 체크메이트 창이 뜨지 않는다.
{
	return false;
}
Knight::Knight()
{
	m_iRank = CHESSRANK_KNIGHT;
}
bool Knight::Move(int Team, POINT pt, vector<chess*>*enemy)//왼쪽  위 아래 , 오른쪽 위아래, 위 오른 왼, 아래 오른 왼
{
	if ((pt.x > Rect.left - m_size.cx * 2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//왼쪽 위
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
		return true;
	}
	else if ((pt.x > Rect.left - m_size.cx *2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//왼쪽 아래
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//오른쪽 아래
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
		return true;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy)) //오른쪽 위
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
		return true;
	}

	if ((pt.y > Rect.top - m_size.cy * 2 && pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//위 오른쪽
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	if ((pt.y > Rect.top - m_size.cy * 2&& pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx ))//위 왼쪽
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		return true;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//아래 왼쪽
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		return true;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//아래 오른쪽
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		return true;
	}
	return false;
}
bool Knight::MoveCheck(POINT pt, RECT rt)//아군을 넘어서 다닐수 있다
{	//자신의 이동거리만 사용
	return false;
}

bool Knight::checkmateCheck(RECT EnemyKing_rt)//다음위치에 보스가 있을경우
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //왼쪽 위 가는길에 팀이있다.
	{
		return true;
	}
	else if(EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //왼쪽 아래  가는길에 팀이있다.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //오른쪽 아래 가는길에 팀이있다.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //오른쪽 위 가는길에 팀이있다.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //위 왼쪽인데 가는길에 팀이있다.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //위 오른쪽 가는길에 팀이있다.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //아래 왼쪽 가는길에 팀이있다.
	{
		return true;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //아래 오른쪽 가는길에 팀이있다.
	{
		return true;
	}
}
bool Knight::checkmate(RECT EnemyKing_rt, RECT Team_rt)
{
	if (EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //왼쪽 위 가는길에 팀이있다.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //왼쪽 아래  가는길에 팀이있다.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top + m_size.cy) //오른쪽 아래 가는길에 팀이있다.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx * 2 && EnemyKing_rt.top == Rect.top - m_size.cy) //오른쪽 위 가는길에 팀이있다.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx  && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //위 왼쪽인데 가는길에 팀이있다.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top - m_size.cy * 2) //위 오른쪽 가는길에 팀이있다.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left - m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //아래 왼쪽 가는길에 팀이있다.
	{
		return false;
	}
	else if (EnemyKing_rt.left == Rect.left + m_size.cx && EnemyKing_rt.top == Rect.top + m_size.cy * 2) //아래 오른쪽 가는길에 팀이있다.
	{
		return false;
	}
}
Rook::Rook()
{
	m_iRank = CHESSRANK_ROOK;
}

bool Rook::Move(int Team, POINT pt, vector<chess*>*enemy) //위 아래쪽 이동 상관 없이 옆쪽 거리 상관없이 다만 자신팀이 가는길에 있으면 넘는건 불가능
{
	int count = 1;
	if (pt.x < Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//왼쪽이동
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
	else if (pt.x > Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//오른쪽이동
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
	else if (pt.y < Rect.top && (pt.x > Rect.left && pt.x < Rect.right))//위쪽이동
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
	else if (pt.y > Rect.bottom && (pt.x > Rect.left && pt.x < Rect.right))//아랫쪽이동
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
bool Rook::MoveCheck(POINT pt, RECT rt)//POINT는 내가 누른위치 rt는 팀위치
{
	int count = 0;
	while (1)//반복을 하는 이유는 내가 가야할 거리에 팀이 있는지 없는지 확인하기 위해
	{
		if (pt.x >= rt.left && pt.x <= rt.right)//가는 위치의x축이 같고
		{
			//나의 위치가 
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
			//y축이 다를경우
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
		if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
		{
			return true;
		}
	}
}
bool Rook::checkmate(RECT EnemyKing_rt, RECT Team_rt)
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left <= Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left >= Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top <= Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.top == Rect.top - m_size.cy * count && Team_rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top >= Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.top == Rect.top + m_size.cy * count && Team_rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
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
	if (pt.x < Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//왼쪽이동
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
	else if (pt.x > Rect.left && (pt.y >= Rect.top && pt.y <= Rect.bottom))//오른쪽이동
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
	else if (pt.y < Rect.top && (pt.x > Rect.left && pt.x < Rect.right))//위쪽이동
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
	else if (pt.y > Rect.bottom && (pt.x > Rect.left && pt.x < Rect.right))//아랫쪽이동
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
	{//오른아래
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
	{//오른위
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
	{//왼쪽위
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
	{//왼쪽아래
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
	while (1)//위, 아래, 오른, 왼쪽 ,오른위 ,오른아래 ,왼쪽위, 왼쪽아래
	{
		if ((pt.x > Rect.left && pt.x < Rect.right))//누른 위치가 x축이 같으면
		{//위 아래
			if (pt.y < Rect.top - m_size.cy * count && pt.y < Rect.bottom - m_size.cy * count)//누른곳이 위로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
				{
					return true;
				}
			}
			else  if (pt.y > Rect.top + m_size.cy * count && pt.y > Rect.bottom + m_size.cy * count)//누른곳이 아래로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
				{
					return true;
				}
			}
			
		}
		else if ((pt.y > Rect.top && pt.y < Rect.bottom))//누른 위치가 y축이 같으면
		{//오른쪽 왼쪽
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다	왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
				{
					return true;
				}
			}
			else  if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
				{
					return true;
				}
			}			
			
		}
		else if ((pt.y < Rect.top && pt.y < Rect.bottom))//누른 위치가 이동캐릭보다 y축이 작다 ( 위)
		{//윗대각선
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				{
					return true;
				}
			}
		}
		else if ((pt.y > Rect.top && pt.y > Rect.bottom))//누른 위치가 이동캐릭보다 y축이 크다 (아래)
		{//아랫대각선
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
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
		if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//적왕에 가는길에 움직이는말과 왼쪽축과 아래쪽축이 같을경우
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 오른축과 아래쪽이 같을경우
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
		{
			return true;
		}
		else if (EnemyKing_rt.top == Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
		{
			return true;
		}
	}
}
bool Queen::checkmate(RECT EnemyKing_rt, RECT Team_rt)//아군,적군
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//적팀의왕과 움직이는말과 왼쪽축과 아래쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//적왕에 가는길에 움직이는말과 왼쪽축과 아래쪽축이 같을경우
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//가는길에 움직이는말과 오른축과 아래쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 오른축과 아래쪽이 같을경우
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//가는길에 움직이는말과 오른축과 위쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top <= Rect.top - m_size.cy * count && EnemyKing_rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.top == Rect.top - m_size.cy * count && Team_rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
			{
				return true;
			}
		}
		else if (EnemyKing_rt.top >= Rect.top + m_size.cy * count && EnemyKing_rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
		{
			if (Team_rt.top == Rect.top + m_size.cy * count && Team_rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
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
bool Bishop::Move(int Team, POINT pt, vector<chess*>*enemy)//대각선 이동
{
	int count = 0;
	if ((pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count) && (pt.y > Rect.top + m_size.cy * count && pt.y > Rect.bottom + m_size.cy*count))
	{//오른아래
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
	{//오른위
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
	{//왼쪽위
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
	{//왼쪽아래
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
	while (1)//4군대를 한다
	{
		if ((pt.y < Rect.top && pt.y < Rect.bottom))//누른 위치가 이동캐릭보다 y축이 작다 ( 위)
		{//윗대각선
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				{
					return true;
				}
			}
		}
		else if ((pt.y > Rect.top && pt.y > Rect.bottom))//누른 위치가 이동캐릭보다 y축이 크다 (아래)
		{//아랫대각선
			if (pt.x < Rect.left - m_size.cx * count && pt.x < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				{
					return true;
				}
			}
			else if (pt.x > Rect.left + m_size.cx * count && pt.x > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
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
		if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//적왕에 가는길에 움직이는말과 왼쪽축과 아래쪽축이 같을경우
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 오른축과 아래쪽이 같을경우
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left - m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			return true;
		}
		else if (EnemyKing_rt.left == Rect.left + m_size.cx * count && EnemyKing_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			return true;
		}
	}
}
bool Bishop::checkmate(RECT EnemyKing_rt, RECT Team_rt)
{
	for (int count = 0; count < 8; count++)
	{
		if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//적팀의왕과 움직이는말과 왼쪽축과 아래쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//적왕에 가는길에 움직이는말과 왼쪽축과 아래쪽축이 같을경우
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top > Rect.top + m_size.cy * count)//가는길에 움직이는말과 오른축과 아래쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 오른축과 아래쪽이 같을경우
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left < Rect.left - m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left - m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
			{
				return true;
			}
		}
		else if (EnemyKing_rt.left > Rect.left + m_size.cx * count && EnemyKing_rt.top < Rect.top - m_size.cy * count)//가는길에 움직이는말과 오른축과 위쪽축이 같을경우
		{
			if (Team_rt.left == Rect.left + m_size.cx * count && Team_rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
			{
				return true;
			}
		}
	}
}