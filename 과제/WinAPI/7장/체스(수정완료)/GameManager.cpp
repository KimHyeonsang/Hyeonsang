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
}

void GameManager::Init(HWND hWnd)
{
	chess[CHESSPAN_BLACK]->Init(hWnd, 20, 20);
	chess[CHESSPAN_WHITE]->Init(hWnd, 20, 895);
	TCHAR buf[256];
	int count = 0;

	PickPan = new chesspan;
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

	if (ChessPanPick.size() > 0)
	{
		ChessPan_iter = ChessPanPick.begin();
		PickPan = *ChessPan_iter;
		PickPan->Draw(hdc);
	}
}

bool GameManager::ChessCheck(POINT pt, HWND hWnd)//���� ������ üũ�� �Ѵ�.
{
	for (ChessPan_iter = ChessPan.begin(); ChessPan_iter != ChessPan.end(); ChessPan_iter++)//�ٴ�
	{
		pan = *ChessPan_iter;
		if (PtInRect(&pan->Rt(), pt))//����� �ٴ���ġ�߿� ���콺��ġ�� �浹�� �ϸ�
		{
			if (chess[m_iplayer]->check(pan) == true)//���ǿ� ���� �ִ��������� üũ ������ true
			{
				if (chess[m_iplayer]->size() >= 1)
					return true;
				else
					return false;
			}
			else
			{//���⿡ ������ �̵���ġ���;���
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

void GameManager::checkmate(HWND hWnd, int Team)//�����̵����� üũ����Ʈ���� Ȯ��
{
	chess[m_iplayer]->checkmate(&chess[!m_iplayer]->Attack(),hWnd,Team);//������ ���͸� ���´�.
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

void GameManager::Play(POINT pt, HWND hWnd)//���⿡ ������.  ������ Ȯ�� ,üũ����Ʈ Ȯ��
{
	if (ChessCheck(pt, hWnd) == true)//ü��üũ�Ѵ�.
	{
		for (ChessPan_iter = ChessPan.begin(); ChessPan_iter != ChessPan.end(); ChessPan_iter++)//�ٴ�
		{
			pan = *ChessPan_iter;
			if (PtInRect(&pan->Rt(), pt))//����� �ٴ���ġ�߿� ���콺��ġ�� �浹�� �ϸ�
			{
				if (chess[m_iplayer]->MoveCheck(pan->Rt(), chess[m_iplayer]->Vector(), m_iplayer) == true && chess[!m_iplayer]->MoveCheck(pan->Rt(), chess[m_iplayer]->Vector(), m_iplayer) == true)//���±濡 ���� �ִ��� ������ üũ
				{
					chess[m_iplayer]->Move(pt, m_iplayer, &chess[!m_iplayer]->Attack()); //pt �κ��� ������ �ٴںκ����� �Ѵ�.
					chess[!m_iplayer]->DeleteChess(pt, hWnd);
					promotion(hWnd);
					checkmate(hWnd, m_iplayer);//üũ����Ʈ���� Ȯ��
					m_iplayer = !m_iplayer;
					ChessPanPick.clear();
				}
			}
		}
	}
}