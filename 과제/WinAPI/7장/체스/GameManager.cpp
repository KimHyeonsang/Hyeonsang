#include "GameManager.h"

GameManager* GameManager::m_pThis = NULL;

GameManager::GameManager()
{
	chess[CHESSPAN_BLACK] = new chessManager('b'); //�渻
	chess[CHESSPAN_WHITE] = new chessManager('w'); //�鸻
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
	for (int i = 1; i <= 64; i++) //�� ����
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
		//���� i�� 8�ϋ� ���� count�� 0
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
void GameManager::ChessCheck(POINT pt, HWND hWnd)//���� ������ üũ�� �Ѵ�.
{
	//���� ���� Ŭ���Ͽ����� üũ
	chess[m_iplayer]->ChessSelect(pt);
	if (chess[m_iplayer]->size() == NULL)
		return;
	//���������Ѱ��� �Ѱ��̰� üũ�� Ʈ�� �̸� �̵�Ȯ��
	if (m_bChessCheck == true && chess[m_iplayer]->size() == 1)
	{
		Move(pt,hWnd);
		return;
	}
	if (chess[m_iplayer]->size() >= 2)
	{
		chess[m_iplayer]->temporaryDelete();//�ն��� ����
	}
	m_bChessCheck = true;
}

void GameManager::Move(POINT pt, HWND hWnd)
{
	//Ŭ���� ������ �ٴڹ����� ��ġ �ϸ� �ϴ� �ٴ��� �ӽú��Ϳ� ������ �ϰ�
	//ü������ �ӽ� ���ͷ� ����Ȱ��� ����� �Ÿ��� �ٸ��� false ������ ����
	for (ChessPan_iter = ChessPan.begin(); ChessPan_iter != ChessPan.end(); ChessPan_iter++)//�ٴ�
	{
		pan = *ChessPan_iter;
		if (PtInRect(&pan->Rt(), pt))//����� �ٴ���ġ�߿� ���콺��ġ�� �浹�� �ϸ�
		{
			if (chess[m_iplayer]->check(pan) == true)//���ǿ� ���� �ִ��������� üũ
			{
				if (chess[m_iplayer]->MoveCheck(pt, chess[!m_iplayer]->Vector()) == true && chess[!m_iplayer]->MoveCheck(pt, chess[m_iplayer]->Vector()) == true)//���±濡 ���� �ִ��� ������ üũ
				{
					if (chess[m_iplayer]->Move(pt, m_iplayer, &chess[!m_iplayer]->Attack()) == true) //pt �κ��� ������ �ٴںκ����� �Ѵ�.
					{
						if (m_iplayer == CHESSPAN_BLACK)
						{
							promotion(hWnd);
							chess[!m_iplayer]->DeleteChess(pt, hWnd);
							checkmate(hWnd);//üũ����Ʈ���� Ȯ��
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

void GameManager::checkmate(HWND hWnd)//�����̵����� üũ����Ʈ���� Ȯ��
{
	chess[m_iplayer]->checkmate(&chess[!m_iplayer]->Attack(),hWnd);//������ ���͸� ���´�.
}

void GameManager::promotion(HWND hWnd)//���⼭ y����ġ�� ������.
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