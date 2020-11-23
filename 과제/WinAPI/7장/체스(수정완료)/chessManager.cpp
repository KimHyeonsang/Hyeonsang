#include "chessManager.h"



chessManager::chessManager(char team)
{
	m_cteam = team;
}

void chessManager::Init(HWND hWnd,int x,int y) 
{
	m_ix = x;
	m_iy = y;
	TCHAR buf[256];
	
	//체스말 셋팅
	makechess = new Rook;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix += makechess->size_x();
	
	makechess = new Knight;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix += makechess->size_x();
	
	makechess = new Bishop;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix += makechess->size_x();
	
	makechess = new Queen;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix += makechess->size_x();
	
	makechess = new King;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix += makechess->size_x();
	
	makechess = new Bishop;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix += makechess->size_x();
	
	makechess = new Knight;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix += makechess->size_x();
	
	makechess = new Rook;
	wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
	makechess->Init(hWnd, m_ix, m_iy, buf);
	Chess_piece.push_back(makechess);
	m_ix = 20;
	m_iy += makechess->size_y();
	if (m_iy > makechess->size_y() * 8)
	{
		m_iy -= makechess->size_y() * 2;
		for (int i = 0; i < 8; i++)
		{

			makechess = new Phawn;
			wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
			makechess->Init(hWnd, m_ix, m_iy, buf);
			Chess_piece.push_back(makechess);
			m_ix += makechess->size_x();
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{

			makechess = new Phawn;
			wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
			makechess->Init(hWnd, m_ix, m_iy, buf);
			Chess_piece.push_back(makechess);
			m_ix += makechess->size_x();
		}
	}
	

}

void chessManager::Draw(HDC hdc)//판과 흰말과 검은말을 그려라
{
	m_hdc = hdc;
	for (temporary_Chess_piece_iter = Chess_piece.begin(); temporary_Chess_piece_iter != Chess_piece.end(); temporary_Chess_piece_iter++)
	{
		makechess = *temporary_Chess_piece_iter;
		makechess->Draw(hdc);
	}
}
bool chessManager::MoveCheck(RECT rt, vector<chess*> v,int Team)//갈 좌표에 울팀이 있는지 없는지 확인 (내팀의 임시변수는 그대로 쓰되 상대팀꺼 비교할떄는 자신의것써야함)
{
	int count = 0;	
	int phawncount = 0;
	temporary_Chess_piece = v;

	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //임시벡터 내가 클릭한 말
		temporary_makechess = *temporary_Chess_piece_iter;

		if (temporary_makechess != makechess)
		{			
			if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
			{
				if (temporary_makechess->phawnAtack(rt, makechess->Rt(), Team) == true)
					phawncount++;
				if (temporary_makechess->MoveCheck(rt, makechess->Rt(), Team) == false)//갈수 있는곳이 트루이면 true 갈수없으면 false
					count++;
			}
			else
			{
				if (temporary_makechess->MoveCheck(rt, makechess->Rt(), Team) == false)//갈수 있는곳이 트루이면 true 갈수없으면 false
					count++;
			}
		}
	}
	if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
	{
		if (Chess_piece.size() - 1 == count)
		{
			if (phawncount == 0 && count > 1)//대각선으로 이동불가,앞도 이동불가
				return true;
		}
		if (phawncount == 0 && count >= 1)//대각선으로 이동불가,앞도 이동불가
			return false;
		else if (phawncount == 0 && count == 0)//대각선으로 이동불가,앞은 이동가능
			return true;
		else if (phawncount >= 1)//대각선이동가능
			return true;
	}
	else
	{
		if (count == 0)
			return true;
		else
			return false;
	}

}
void chessManager::ChessSelect(POINT pt)
{
	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		if (PtInRect(&makechess->Rt(), pt))//저장된 위치중에 마우스위치가 충돌을 하면
		{
			temporary_Chess_piece.push_back(makechess); //임시 체스 저장
			return;
		}
	}
}
void chessManager::temporaryDelete()
{
	Chess_piece_iter = temporary_Chess_piece.begin();
	Chess_piece_iter = temporary_Chess_piece.erase(Chess_piece_iter);
}
void chessManager::Move(POINT pt, int Team, vector<chess*>*enemy)//팀에 따라 다르다
{

	temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //임시벡터 내가 클릭한 말
	temporary_makechess = *temporary_Chess_piece_iter;
	//일단 임시 벡터랑 본내용이 들어있는거랑 같으면..
	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		if (temporary_makechess == makechess)//같으면 움직일수있는지 없는지 확인을 한다.
		{
			switch (makechess->Rank())//무슨 말인지 확인을 하고
			{
			case CHESSRANK_PHAWN:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // 임시 저장삭제
				temporary_Chess_piece.push_back(makechess);//이동된 말 저장
				break;
			case CHESSRANK_KNIGHT:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // 임시 저장삭제
				temporary_Chess_piece.push_back(makechess);//이동된 말 저장
				break;
			case CHESSRANK_BISHOP:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // 임시 저장삭제
				temporary_Chess_piece.push_back(makechess);//이동된 말 저장
				break;
			case CHESSRANK_ROOK:
				//이동가능한지 체크를 하고 무브를 확인한다.
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // 임시 저장삭제
				temporary_Chess_piece.push_back(makechess);//이동된 말 저장
				break;
			case CHESSRANK_KING:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // 임시 저장삭제
				temporary_Chess_piece.push_back(makechess);//이동된 말 저장
				break;
			case CHESSRANK_QUEEN:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // 임시 저장삭제
				temporary_Chess_piece.push_back(makechess);//이동된 말 저장
				break;
			}
			
		}
	}
}
vector<chess*> chessManager::Attack()//적 벡터
{
	return Chess_piece;
}
void chessManager::DeleteChess(POINT pt, HWND hWnd)
{
	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		if (PtInRect(&makechess->Rt(), pt))//저장된 위치중에 마우스위치가 충돌을 하면
		{
			if (makechess->Rank() == CHESSRANK_KING)
			{
				MessageBox(hWnd, TEXT("승리 하셨습니다."), TEXT("축하합니다."), MB_OK);
				SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
			Chess_piece_iter = Chess_piece.erase(Chess_piece_iter);
			return;
		}
	}

	temporary_Chess_piece.clear(); //임시변수 지우기
}

vector<chess*>chessManager::Vector()
{
	return temporary_Chess_piece;
}

bool chessManager::check(chesspan* pan)
{
	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		if (pan->Rt_x() == makechess->Rt_x() && pan->Rt_y() == makechess->Rt_y())//그 판에 캐릭터가 있으면..
		{
			return false;
		}
	}
	return true;
}
void chessManager::promotion(HWND hWnd,int y)//만약 여기서 임시변수를 삭제시키기전에 
{
	int Rank = CHESSRANK_KNIGHT;
	temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //임시벡터 이동된 말
	temporary_makechess = *temporary_Chess_piece_iter;
	if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
	{
		TCHAR buf[256];
		for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)//모든아군비교
		{
			makechess = *Chess_piece_iter;

			if (temporary_makechess == makechess)
			{
				if (y == makechess->Rt_y())//y축이 같으면 변신
				{
					while (1)
					{
						switch (Rank)
						{
						case CHESSRANK_KNIGHT:
							if (MessageBox(hWnd, TEXT("나이트로 바꾸시겠습니다."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("나이트가 되었습니다."), TEXT("승급"), NULL);
								m_ix = makechess->Rt_x();
								m_iy = makechess->Rt_y();
								Chess_piece_iter = Chess_piece.erase(Chess_piece_iter);
								makechess = new Knight;
								wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
								makechess->Init(hWnd, m_ix, m_iy, buf);
								Chess_piece.push_back(makechess);
								temporary_Chess_piece.clear();
								temporary_Chess_piece.push_back(makechess);
								return;
							}
							else
							{
								Rank++;
							}
							break;
						case CHESSRANK_BISHOP:
							if (MessageBox(hWnd, TEXT("비숍으로 바꾸시겠습니다."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("비숍이 되었습니다."), TEXT("승급"), NULL);
								m_ix = makechess->Rt_x();
								m_iy = makechess->Rt_y();
								Chess_piece_iter = Chess_piece.erase(Chess_piece_iter);
								makechess = new Bishop;
								wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
								makechess->Init(hWnd, m_ix, m_iy, buf);
								Chess_piece.push_back(makechess);
								temporary_Chess_piece.clear();
								temporary_Chess_piece.push_back(makechess);
								return;
							}
							else
								Rank++;
							break;
						case CHESSRANK_ROOK:
							if (MessageBox(hWnd, TEXT("룩으로 바꾸시겠습니다."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("룩이 되었습니다."), TEXT("승급"), NULL);
								m_ix = makechess->Rt_x();
								m_iy = makechess->Rt_y();
								Chess_piece_iter = Chess_piece.erase(Chess_piece_iter);
								makechess = new Rook;
								wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
								makechess->Init(hWnd, m_ix, m_iy, buf);
								Chess_piece.push_back(makechess);
								temporary_Chess_piece.clear();
								temporary_Chess_piece.push_back(makechess);
								return;
							}
							else
								Rank++;
							break;
						case CHESSRANK_QUEEN:
							if (MessageBox(hWnd, TEXT("퀸으로 바꾸시겠습니다."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("퀸이 되었습니다."), TEXT("승급"), NULL);
								m_ix = makechess->Rt_x();
								m_iy = makechess->Rt_y();
								Chess_piece_iter = Chess_piece.erase(Chess_piece_iter);
								makechess = new Queen;
								wsprintf(buf, L"Chess//block_%c_0%d.bmp", m_cteam, makechess->Rank());
								makechess->Init(hWnd, m_ix, m_iy, buf);
								Chess_piece.push_back(makechess);
								temporary_Chess_piece.clear();
								temporary_Chess_piece.push_back(makechess);
								return;
							}
							else
								Rank = CHESSRANK_KNIGHT;
							break;
						}
					}
					
					
				}
			}
		}
	}
	
}

void chessManager::checkmate(vector<chess*>*enemy, HWND hWnd,int Team)
{	
	//적팀의 왕 정보를 찾는다.
	for (m_Enemy_Chess_piece_iter = enemy->begin(); m_Enemy_Chess_piece_iter != enemy->end(); m_Enemy_Chess_piece_iter++)//적군왕찾기
	{
		m_EnemyKing = *m_Enemy_Chess_piece_iter;
		if (m_EnemyKing->Rank() == CHESSRANK_KING)
		{
			break;//찾으면 종료
		}
	}
	int count = 0;
	int phawncount = 0;
	temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //임시벡터 이동된 말
	temporary_makechess = *temporary_Chess_piece_iter;
	for (m_Enemy_Chess_piece_iter = enemy->begin(); m_Enemy_Chess_piece_iter != enemy->end(); m_Enemy_Chess_piece_iter++)//모든적군비교
	{
		m_Enemy = *m_Enemy_Chess_piece_iter;
		if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
		{
			if (temporary_makechess->phawnAtack(m_EnemyKing->Rt(), m_Enemy->Rt(), Team) == true)
				phawncount++;
		}
		if (temporary_makechess->MoveCheck(m_EnemyKing->Rt(), m_Enemy->Rt(), Team) == true)
			count++;
		for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)//모든아군비교
		{
			makechess = *Chess_piece_iter;

			if (temporary_makechess != makechess)
			{
				if (count == enemy->size() && temporary_makechess->MoveCheck(m_EnemyKing->Rt(), makechess->Rt(), Team) == true)
				{//적왕과 움직이는 말사이에 적군이 있거나 아군이있을떄
					MessageBox(hWnd, TEXT("체크메이트입니다."), TEXT("MessageBox"), MB_OK);
					temporary_Chess_piece.clear();
					return;
				}
				else if (phawncount == 1)
				{
					MessageBox(hWnd, TEXT("체크메이트입니다."), TEXT("MessageBox"), MB_OK);
					temporary_Chess_piece.clear();
					return;
				}
			}
		}
	}
	temporary_Chess_piece.clear();
}

chessManager::~chessManager()
{
}
