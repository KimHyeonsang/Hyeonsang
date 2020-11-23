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
}

void GameManager::Init(HWND hWnd)
{
	chess[CHESSPAN_BLACK]->Init(hWnd, 20, 20);
	chess[CHESSPAN_WHITE]->Init(hWnd, 20, 895);
	TCHAR buf[256];
	int count = 0;

	PickPan = new chesspan;
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

	if (ChessPanPick.size() > 0)
	{
		ChessPan_iter = ChessPanPick.begin();
		PickPan = *ChessPan_iter;
		PickPan->Draw(hdc);
	}
}

bool GameManager::ChessCheck(POINT pt, HWND hWnd)//무슨 말인지 체크를 한다.
{
	for (ChessPan_iter = ChessPan.begin(); ChessPan_iter != ChessPan.end(); ChessPan_iter++)//바닥
	{
		pan = *ChessPan_iter;
		if (PtInRect(&pan->Rt(), pt))//저장된 바닥위치중에 마우스위치와 충돌을 하면
		{
			if (chess[m_iplayer]->check(pan) == true)//이판에 팀이 있는지없는지 체크 없으면 true
			{
				if (chess[m_iplayer]->size() >= 1)
					return true;
				else
					return false;
			}
			else
			{//여기에 누르면 이동위치나와야함
				chess[m_iplayer]->ChessSelect(pt);
				if (chess[m_iplayer]->size() > 1)
					chess[m_iplayer]->temporaryDelete();
				SelectPick(pan->Rt(),hWnd);
				return false;
			}
		}
	}
}

void GameManager::SelectPick(RECT pickpan,HWND hWnd)
{
	PickPan->Init(hWnd, TEXT("Chess//block02.bmp"),pickpan.left, pickpan.top);
	ChessPanPick.push_back(PickPan);
}

void GameManager::checkmate(HWND hWnd, int Team)//다음이동때에 체크메이트인지 확인
{
	chess[m_iplayer]->checkmate(&chess[!m_iplayer]->Attack(),hWnd,Team);//적팀의 벡터를 들고온다.
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

void GameManager::Play(POINT pt, HWND hWnd)//여기에 모으다.  움직임 확인 ,체크메이트 확인
{
	if (ChessCheck(pt, hWnd) == true)//체스체크한다.
	{
		for (ChessPan_iter = ChessPan.begin(); ChessPan_iter != ChessPan.end(); ChessPan_iter++)//바닥
		{
			pan = *ChessPan_iter;
			if (PtInRect(&pan->Rt(), pt))//저장된 바닥위치중에 마우스위치와 충돌을 하면
			{
				if (chess[m_iplayer]->MoveCheck(pan->Rt(), chess[m_iplayer]->Vector(), m_iplayer) == true && chess[!m_iplayer]->MoveCheck(pan->Rt(), chess[m_iplayer]->Vector(), m_iplayer) == true)//가는길에 팀이 있는지 없는지 체크
				{
					chess[m_iplayer]->Move(pt, m_iplayer, &chess[!m_iplayer]->Attack()); //pt 부분을 지정된 바닥부분으로 한다.
					chess[!m_iplayer]->DeleteChess(pt, hWnd);
					promotion(hWnd);
					checkmate(hWnd, m_iplayer);//체크매이트인지 확인
					m_iplayer = !m_iplayer;
					ChessPanPick.clear();
				}
			}
		}
	}
}