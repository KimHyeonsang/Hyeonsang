#include "GameManager.h"

GameManager* GameManager::m_pThis = NULL;

GameManager::GameManager()
{
	chess[CHESSPAN_BLACK] = new chessManager('b'); //흑말
	chess[CHESSPAN_WHITE] = new chessManager('w'); //백말
	srand(time(NULL));
	m_ix = 20;
	m_iy = 20;
	m_iplayer = CHESSPAN_WHITE;
	m_bChessCheck = false;
}

void GameManager::Init(HWND hWnd)
{
	chess[CHESSPAN_BLACK]->Init(hWnd, 20, 20);
	chess[CHESSPAN_WHITE]->Init(hWnd, 20, 895);
	TCHAR buf[256];
	int count = 0;
	for (int i = 1; i <= 64; i++) //판 셋팅
	{
		pan = new chesspan;
		wsprintf(buf, L"Chess//block0%d.bmp", count);
		pan->Init(hWnd, buf, m_ix, m_iy);
		m_ix += pan->size_x();
		if (m_ix > pan->size_x() * 8)
		{
			m_iy += pan->size_y();
			m_ix = 20;
		}
		//만약 i가 8일떄 만약 count가 0
		if (i % 8 == 0)
		{
			if (count != 1)
				count = 0;
			else if (count == 0)
				count++;
		}
		else
		{
			if (count >= 1)
				count = 0;
			else
				count++;
		}
		ChessPan.push_back(pan);
	}
}

GameManager::~GameManager()
{

}

void GameManager::Draw(HDC hdc)
{
	for (ChessPan_iter = ChessPan.begin(); ChessPan_iter != ChessPan.end(); ChessPan_iter++)
	{
		pan = *ChessPan_iter;
		pan->Draw(hdc);
	}
	chess[CHESSPAN_BLACK]->Draw(hdc);
	chess[CHESSPAN_WHITE]->Draw(hdc);
}
void GameManager::ChessCheck(POINT pt, HWND hWnd)//무슨 말인지 체크를 한다.
{
	//무슨 말을 클릭하였는지 체크
	chess[m_iplayer]->ChessSelect(pt);
	if (chess[m_iplayer]->size() == NULL)
		return;
	//만약저장한곳이 한개이고 체크가 트루 이면 이동확인
	if (m_bChessCheck == true && chess[m_iplayer]->size() == 1)
	{
		Move(pt,hWnd);
		return;
	}
	if (chess[m_iplayer]->size() >= 2)
	{
		chess[m_iplayer]->temporaryDelete();//앞라인 제거
	}
	m_bChessCheck = true;
}

void GameManager::Move(POINT pt, HWND hWnd)
{
	//클릭한 범위가 바닥범위랑 일치 하면 일단 바닥을 임시벡터에 저장을 하고
	//체스말을 임시 벡터로 저장된것의 무브와 거리가 다르면 false 같으면 저장
	for (ChessPan_iter = ChessPan.begin(); ChessPan_iter != ChessPan.end(); ChessPan_iter++)//바닥
	{
		pan = *ChessPan_iter;
		if (PtInRect(&pan->Rt(), pt))//저장된 바닥위치중에 마우스위치와 충돌을 하면
		{
			if (chess[m_iplayer]->check(pan) == true)//이판에 팀이 있는지없는지 체크
			{
				if (chess[m_iplayer]->MoveCheck(pt, chess[!m_iplayer]->Vector()) == true && chess[!m_iplayer]->MoveCheck(pt, chess[m_iplayer]->Vector()) == true)//가는길에 팀이 있는지 없는지 체크
				{
					if (chess[m_iplayer]->Move(pt, m_iplayer, &chess[!m_iplayer]->Attack()) == true) //pt 부분을 지정된 바닥부분으로 한다.
					{
						if (m_iplayer == CHESSPAN_BLACK)
						{
							promotion(hWnd);
							chess[!m_iplayer]->DeleteChess(pt, hWnd);
							checkmate(hWnd);//체크매이트인지 확인
							m_iplayer = CHESSPAN_WHITE;	
						}
						else
						{
							promotion(hWnd);
							chess[!m_iplayer]->DeleteChess(pt, hWnd);
							checkmate(hWnd);
							m_iplayer = CHESSPAN_BLACK;
						}
						m_bChessCheck = false;
					}					
				}				
			}
			return;
		}

	}
}

void GameManager::checkmate(HWND hWnd)//다음이동때에 체크메이트인지 확인
{
	chess[m_iplayer]->checkmate(&chess[!m_iplayer]->Attack(),hWnd);//적팀의 벡터를 들고온다.
}

void GameManager::promotion(HWND hWnd)//여기서 y축위치만 보낸다.
{
	if (m_iplayer == CHESSPAN_BLACK)
	{		 
		m_iy = 895;
		chess[m_iplayer]->promotion(hWnd, m_iy);
	}
	else if (m_iplayer == CHESSPAN_WHITE)
	{		
		m_iy = 20; 
		chess[m_iplayer]->promotion(hWnd, m_iy);
	}
}