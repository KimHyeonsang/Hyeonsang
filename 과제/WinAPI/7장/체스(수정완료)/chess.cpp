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
void Phawn::Move(int Team, POINT pt)//기본적으로 앞으로만 전진 대각선에 상대가 있을때는 대각선 이동 가능
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
			}
			else if (pt.y > (Rect.top - m_size.cy) && pt.y < Rect.top)//첫번쨰 칸이면
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
		if (m_bfirstmove == true && ((pt.x >= Rect.left && pt.x <= Rect.right) && pt.y > Rect.bottom))//처음 움직이는것이고 누르는곳이 말보다 작은곳이면
		{
			if (pt.y < (Rect.bottom + m_size.cy * 2) && pt.y > (Rect.bottom + m_size.cy))//누른곳이 두번째 칸이면
			{
				Rect.top += m_size.cy * 2;
				Rect.bottom += m_size.cy * 2;
				m_bfirstmove = false;
			}
			else if (pt.y < (Rect.bottom + m_size.cy) && pt.y > Rect.bottom)//첫번쨰 칸이면
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
bool chess::phawnAtack(RECT POINT_RT, RECT rt, int Team)//true면 이동가능  pt는 내가 갈곳 rt는 모든 말좌표
{	
	if (Team == CHESSPAN_WHITE)
	{
		if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top - m_size.cy)
		{//왼쪽 위
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
		else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top - m_size.cy)
		{//오른쪽 위
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
	}
	else if (Team == CHESSPAN_BLACK)
	{
		if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top + m_size.cy)
		{//왼쪽 아래
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
		else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top + m_size.cy)
		{//오른쪽 아래
			if (POINT_RT.left == rt.left && POINT_RT.top == rt.top)
				return true;
		}
	}
	return false;
}
bool Phawn::MoveCheck(RECT POINT_RT, RECT rt, int Team)//true면 이동가능  pt는 내가 갈곳 rt는 모든 말좌표
{
	if (Team == CHESSPAN_WHITE)
	{
		if (m_bfirstmove == true && POINT_RT.left == Rect.left && POINT_RT.right == Rect.right && POINT_RT.top >= Rect.top - m_size.cy * 2 && POINT_RT.bottom <= Rect.bottom - m_size.cy)
		{//누른곳이 위로 두칸일떄
			if (POINT_RT.top == rt.top * 2 && POINT_RT.top == rt.bottom && POINT_RT.left == rt.left && POINT_RT.left == rt.right)
				return false;
			else
				return true;
		}
		else if (m_bfirstmove == false && POINT_RT.left == Rect.left && POINT_RT.right == Rect.right && POINT_RT.top == Rect.top - m_size.cy && POINT_RT.bottom == Rect.bottom - m_size.cy)
		{//누른곳이 위로 한칸일떄
			if (POINT_RT.top == rt.top  && POINT_RT.left == rt.left)
				return false;
			else
				return true;
		}
	}
	else if (Team == CHESSPAN_BLACK)
	{
		if (m_bfirstmove == true && POINT_RT.left == Rect.left && POINT_RT.right && POINT_RT.top >= Rect.top + m_size.cy && POINT_RT.bottom <= Rect.bottom + m_size.cy * 2)
		{//누른곳이 아래로 두칸일떄
			if (POINT_RT.top == rt.top && POINT_RT.bottom == rt.bottom * 2 && POINT_RT.left == rt.left && POINT_RT.right == rt.right)
				return false;
			else
				return true;
		}
		else if (m_bfirstmove == false && POINT_RT.left == Rect.left && POINT_RT.right && POINT_RT.top == Rect.top + m_size.cy && POINT_RT.bottom == Rect.bottom + m_size.cy)
		{//누른곳이 아래로 한칸일떄
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
void King::Move(int Team, POINT pt)//상하좌우 한칸씩 이동가능 포인트를 찍은 곳이 한칸씩이동 이동 아니면 false
{
	if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) &&(pt.y > Rect.top && pt.y < Rect.bottom ))//왼쪽이동
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top && pt.y < Rect.bottom))//오른쪽이동
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
	else if ((pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//위쪽이동
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left && pt.x < Rect.right))//아랫쪽이동
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
	}
	else if ((pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//왼쪽 위이동
	{
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
	}
	else if ((pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//오른쪽 위이동
	{
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//오른쪽 아래쪽이동
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy; 
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
	else if ((pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//왼쪽 아랫쪽이동
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
}
bool King::MoveCheck(RECT POINT_RT, RECT rt, int Team)//자신이 가는곳은 무조건 true
{
	if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top)//왼쪽이동
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top)//오른쪽이동
		return true;
	else if (POINT_RT.top == Rect.top - m_size.cy  && POINT_RT.left == Rect.left)//위쪽이동
		return true;
	else if (POINT_RT.top == Rect.top + m_size.cy  && POINT_RT.left == Rect.left)//아랫쪽이동
		return true;
	else if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top - m_size.cy)//왼쪽 위이동
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top - m_size.cy)//오른쪽 위이동
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx && POINT_RT.top == Rect.top + m_size.cy)//오른쪽 아래쪽이동
		return true;
	else if (POINT_RT.left == Rect.left - m_size.cx && POINT_RT.top == Rect.top + m_size.cy)//왼쪽 아랫쪽이동
		return true;
	return false;
}

Knight::Knight()
{
	m_iRank = CHESSRANK_KNIGHT;
}
void Knight::Move(int Team, POINT pt)//왼쪽  위 아래 , 오른쪽 위아래, 위 오른 왼, 아래 오른 왼
{
	if ((pt.x > Rect.left - m_size.cx * 2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy))//왼쪽 위
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
	}
	else if ((pt.x > Rect.left - m_size.cx *2 && pt.x < Rect.right - m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//왼쪽 아래
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left -= m_size.cx * 2;
		Rect.right -= m_size.cx * 2;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top + m_size.cy && pt.y < Rect.bottom + m_size.cy))//오른쪽 아래
	{
		Rect.top += m_size.cy;
		Rect.bottom += m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
	}
	else if ((pt.x > Rect.left + m_size.cx * 2 && pt.x < Rect.right + m_size.cx * 2) && (pt.y > Rect.top - m_size.cy && pt.y < Rect.bottom - m_size.cy)) //오른쪽 위
	{
		Rect.top -= m_size.cy;
		Rect.bottom -= m_size.cy;
		Rect.left += m_size.cx * 2;
		Rect.right += m_size.cx * 2;
	}

	if ((pt.y > Rect.top - m_size.cy * 2 && pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//위 오른쪽
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
	if ((pt.y > Rect.top - m_size.cy * 2&& pt.y < Rect.bottom - m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx ))//위 왼쪽
	{
		Rect.top -= m_size.cy * 2;
		Rect.bottom -= m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left - m_size.cx && pt.x < Rect.right - m_size.cx))//아래 왼쪽
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left -= m_size.cx;
		Rect.right -= m_size.cx;
	}
	if ((pt.y > Rect.top + m_size.cy * 2 && pt.y < Rect.bottom + m_size.cy * 2) && (pt.x > Rect.left + m_size.cx && pt.x < Rect.right + m_size.cx))//아래 오른쪽
	{
		Rect.top += m_size.cy * 2;
		Rect.bottom += m_size.cy * 2;
		Rect.left += m_size.cx;
		Rect.right += m_size.cx;
	}
}
bool Knight::MoveCheck(RECT POINT_RT, RECT rt, int Team)//아군을 넘어서 다닐수 있다
{	//자신의 이동거리만 사용
	if (POINT_RT.left == Rect.left - m_size.cx * 2 && POINT_RT.top == Rect.top - m_size.cy )//왼쪽 위
		return true;
	else if (POINT_RT.left == Rect.left - m_size.cx * 2 && POINT_RT.top == Rect.top + m_size.cy)//왼쪽 아래
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx * 2 && POINT_RT.top == Rect.top - m_size.cy)//왼쪽 위
		return true;
	else if (POINT_RT.left == Rect.left + m_size.cx * 2 && POINT_RT.top == Rect.top + m_size.cy)//왼쪽 아래
		return true;
	else if (POINT_RT.top == Rect.top - m_size.cy * 2  && POINT_RT.left == Rect.left + m_size.cx)//위 오른쪽
		return true;
	else if (POINT_RT.top == Rect.top - m_size.cy * 2 && POINT_RT.left == Rect.left - m_size.cx)//위 왼쪽
		return true;
	else if (POINT_RT.top == Rect.top + m_size.cy * 2 && POINT_RT.left == Rect.left + m_size.cx)//위 오른쪽
		return true;
	else if (POINT_RT.top == Rect.top + m_size.cy * 2 && POINT_RT.left == Rect.left - m_size.cx)//위 왼쪽
		return true;
	return false;
}

Rook::Rook()
{
	m_iRank = CHESSRANK_ROOK;
}

void Rook::Move(int Team, POINT pt) //위 아래쪽 이동 상관 없이 옆쪽 거리 상관없이 다만 자신팀이 가는길에 있으면 넘는건 불가능
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
	}
}
bool Rook::MoveCheck(RECT POINT_RT, RECT rt, int Team)//POINT는 내가 누른위치 rt는 팀위치  갈수있으면  true
{
	for (int count = 0; count < 8; count++)
	{
		if (POINT_RT.left == Rect.left)//누른 위치가 x축이 같으면
		{//위 아래
			if (POINT_RT.top < Rect.top - m_size.cy * count && POINT_RT.bottom < Rect.bottom - m_size.cy * count)//누른곳이 위로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
					return false;
			}
			else  if (POINT_RT.top > Rect.top + m_size.cy * count && POINT_RT.bottom > Rect.bottom + m_size.cy * count)//누른곳이 아래로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
					return false;
			}
		}
		else if (POINT_RT.top == Rect.top)//누른 위치가 y축이 같으면
		{//오른쪽 왼쪽
			if (POINT_RT.left < Rect.left - m_size.cx * count && POINT_RT.right < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다	왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
					return false;
			}
			else  if (POINT_RT.left > Rect.left + m_size.cx * count && POINT_RT.right > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
					return false;
			}
		}
		else  if(POINT_RT.left < Rect.left  && POINT_RT.top < Rect.top)//왼위
		{
			return false;
		}
		else  if (POINT_RT.left < Rect.left  && POINT_RT.bottom > Rect.bottom)//왼아래
		{
			return false;
		}
		else  if (POINT_RT.right > Rect.right  && POINT_RT.top < Rect.top)//오른위
		{
			return false;
		}
		else  if (POINT_RT.right > Rect.right  && POINT_RT.bottom > Rect.bottom)//오른아래
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
			}
			else
				count++;
		}
	}
}
bool Queen::MoveCheck(RECT POINT_RT, RECT rt, int Team)
{
	int count = 0;
	while (1)//위, 아래, 오른, 왼쪽 ,오른위 ,오른아래 ,왼쪽위, 왼쪽아래
	{
		if (POINT_RT.left== Rect.left)//누른 위치가 x축이 같으면
		{//위 아래
			if (POINT_RT.top < Rect.top - m_size.cy * count && POINT_RT.bottom < Rect.bottom - m_size.cy * count)//누른곳이 위로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
					return false;
			}
			else  if (POINT_RT.top > Rect.top + m_size.cy * count && POINT_RT.bottom > Rect.bottom + m_size.cy * count)//누른곳이 아래로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
					return false;
			}
			
		}
		else if (POINT_RT.top == Rect.top)//누른 위치가 y축이 같으면
		{//오른쪽 왼쪽
			if (POINT_RT.left < Rect.left - m_size.cx * count && POINT_RT.right < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다	왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
					return false;
			}
			else  if (POINT_RT.left > Rect.left + m_size.cx * count && POINT_RT.right > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
					return false;
			}			
		}
		else if (POINT_RT.top <= Rect.top && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))
		{//왼쪽윗대각선
			if (POINT_RT.top == Rect.top - m_size.cy * count  && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				return false;
		}
		else if ((POINT_RT.top <= Rect.top && POINT_RT.bottom < Rect.bottom) && POINT_RT.left >= Rect.left)
		{//오른쪽위대각선	
			if (POINT_RT.top == Rect.top - m_size.cy * count  && POINT_RT.left == Rect.left + m_size.cx * count)
				return true;			
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				return false;
		}
		else if ((POINT_RT.top >= Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))//누른 위치가 이동캐릭보다 y축이 크다 (아래)
		{//왼쪽아랫대각선
			if (POINT_RT.top == Rect.top + m_size.cy * count  && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;		
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				return false;
		}
		else if ((POINT_RT.top >= Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left > Rect.left && POINT_RT.right > Rect.right))//누른 위치가 이동캐릭보다 y축이 크다 (아래)
		{//오른쪽아래대각선
			if (POINT_RT.top == Rect.top + m_size.cy * count && POINT_RT.left == Rect.left + m_size.cx * count)
				return true;			
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
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
void Bishop::Move(int Team, POINT pt)//대각선 이동
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
			}
			else
				count++;
		}
	}
}
bool Bishop::MoveCheck(RECT POINT_RT, RECT rt, int Team)
{
	int count = 0;
	while (1)//4군대를 한다
	{
		if (POINT_RT.left == Rect.left)//누른 위치가 x축이 같으면
		{//위 아래
			if (POINT_RT.top < Rect.top - m_size.cy * count && POINT_RT.bottom < Rect.bottom - m_size.cy * count)//누른곳이 위로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top - m_size.cy * count && rt.left == Rect.left)//위쪽인데 가는길에 팀이있다.
					return false;
			}
			else  if (POINT_RT.top > Rect.top + m_size.cy * count && POINT_RT.bottom > Rect.bottom + m_size.cy * count)//누른곳이 아래로 올라가는것보다 클경우
			{
				if (rt.top == Rect.top + m_size.cy * count && rt.left == Rect.left)//아래쪽인데 가는길에 팀이있다.
					return false;
			}

		}
		else if (POINT_RT.top == Rect.top)//누른 위치가 y축이 같으면
		{//오른쪽 왼쪽
			if (POINT_RT.left < Rect.left - m_size.cx * count && POINT_RT.right < Rect.right - m_size.cx * count)//누른곳의 x축이 이동캐릭 보다	왼쪽에 있을경우
			{
				if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top) //왼쪽인데 가는길에 팀이있다.
					return false;
			}
			else  if (POINT_RT.left > Rect.left + m_size.cx * count && POINT_RT.right > Rect.right + m_size.cx * count)//누른곳의 x축이 이동캐릭 보다 오른쪽에 있을경우
			{
				if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top)//오른쪽인데 가는길에 팀이있다.
					return false;
			}
		}
		else if ((POINT_RT.top < Rect.top && POINT_RT.bottom < Rect.bottom) && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))
		{//왼쪽윗대각선
			if (POINT_RT.top == Rect.top - m_size.cy * count && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				return false;
		}
		else if ((POINT_RT.top < Rect.top && POINT_RT.bottom < Rect.bottom) && (POINT_RT.left > Rect.left && POINT_RT.right > Rect.right))
		{//오른쪽대각선	
			if (POINT_RT.top == Rect.top - m_size.cy * count && POINT_RT.left == Rect.left + m_size.cx * count )
				return true;
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top - m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				return false;
		}
		else if ((POINT_RT.top > Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left < Rect.left && POINT_RT.right < Rect.right))//누른 위치가 이동캐릭보다 y축이 크다 (아래)
		{//왼쪽아랫대각선
			if (POINT_RT.top == Rect.top + m_size.cy * count  && POINT_RT.left == Rect.left - m_size.cx * count)
				return true;
			else if (rt.left == Rect.left - m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				return false;
		}
		else if ((POINT_RT.top > Rect.top && POINT_RT.bottom > Rect.bottom) && (POINT_RT.left > Rect.left && POINT_RT.right > Rect.right))//누른 위치가 이동캐릭보다 y축이 크다 (아래)
		{//오른쪽아래대각선
			if (POINT_RT.top == Rect.top + m_size.cy * count && (POINT_RT.left == Rect.left + m_size.cx * count))
				return true;
			else if (rt.left == Rect.left + m_size.cx * count && rt.top == Rect.top + m_size.cy * count)//가는길에 움직이는말과 왼쪽축과 위쪽축이 같을경우
				return false;
		}
		if (count > 8)
			return false;
		
		count++;
	}	
}