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
	
	//ü���� ����
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

void chessManager::Draw(HDC hdc)//�ǰ� �򸻰� �������� �׷���
{
	m_hdc = hdc;
	for (temporary_Chess_piece_iter = Chess_piece.begin(); temporary_Chess_piece_iter != Chess_piece.end(); temporary_Chess_piece_iter++)
	{
		makechess = *temporary_Chess_piece_iter;
		makechess->Draw(hdc);
	}
}
bool chessManager::MoveCheck(RECT rt, vector<chess*> v,int Team)//�� ��ǥ�� ������ �ִ��� ������ Ȯ�� (������ �ӽú����� �״�� ���� ������� ���ҋ��� �ڽ��ǰͽ����)
{
	int count = 0;	
	int phawncount = 0;
	temporary_Chess_piece = v;

	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //�ӽú��� ���� Ŭ���� ��
		temporary_makechess = *temporary_Chess_piece_iter;

		if (temporary_makechess != makechess)
		{			
			if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
			{
				if (temporary_makechess->phawnAtack(rt, makechess->Rt(), Team) == true)
					phawncount++;
				if (temporary_makechess->MoveCheck(rt, makechess->Rt(), Team) == false)//���� �ִ°��� Ʈ���̸� true ���������� false
					count++;
			}
			else
			{
				if (temporary_makechess->MoveCheck(rt, makechess->Rt(), Team) == false)//���� �ִ°��� Ʈ���̸� true ���������� false
					count++;
			}
		}
	}
	if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
	{
		if (Chess_piece.size() - 1 == count)
		{
			if (phawncount == 0 && count > 1)//�밢������ �̵��Ұ�,�յ� �̵��Ұ�
				return true;
		}
		if (phawncount == 0 && count >= 1)//�밢������ �̵��Ұ�,�յ� �̵��Ұ�
			return false;
		else if (phawncount == 0 && count == 0)//�밢������ �̵��Ұ�,���� �̵�����
			return true;
		else if (phawncount >= 1)//�밢���̵�����
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
		if (PtInRect(&makechess->Rt(), pt))//����� ��ġ�߿� ���콺��ġ�� �浹�� �ϸ�
		{
			temporary_Chess_piece.push_back(makechess); //�ӽ� ü�� ����
			return;
		}
	}
}
void chessManager::temporaryDelete()
{
	Chess_piece_iter = temporary_Chess_piece.begin();
	Chess_piece_iter = temporary_Chess_piece.erase(Chess_piece_iter);
}
void chessManager::Move(POINT pt, int Team, vector<chess*>*enemy)//���� ���� �ٸ���
{

	temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //�ӽú��� ���� Ŭ���� ��
	temporary_makechess = *temporary_Chess_piece_iter;
	//�ϴ� �ӽ� ���Ͷ� �������� ����ִ°Ŷ� ������..
	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		if (temporary_makechess == makechess)//������ �����ϼ��ִ��� ������ Ȯ���� �Ѵ�.
		{
			switch (makechess->Rank())//���� ������ Ȯ���� �ϰ�
			{
			case CHESSRANK_PHAWN:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // �ӽ� �������
				temporary_Chess_piece.push_back(makechess);//�̵��� �� ����
				break;
			case CHESSRANK_KNIGHT:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // �ӽ� �������
				temporary_Chess_piece.push_back(makechess);//�̵��� �� ����
				break;
			case CHESSRANK_BISHOP:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // �ӽ� �������
				temporary_Chess_piece.push_back(makechess);//�̵��� �� ����
				break;
			case CHESSRANK_ROOK:
				//�̵��������� üũ�� �ϰ� ���긦 Ȯ���Ѵ�.
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // �ӽ� �������
				temporary_Chess_piece.push_back(makechess);//�̵��� �� ����
				break;
			case CHESSRANK_KING:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // �ӽ� �������
				temporary_Chess_piece.push_back(makechess);//�̵��� �� ����
				break;
			case CHESSRANK_QUEEN:
				makechess->Move(Team, pt);
				temporary_Chess_piece.clear(); // �ӽ� �������
				temporary_Chess_piece.push_back(makechess);//�̵��� �� ����
				break;
			}
			
		}
	}
}
vector<chess*> chessManager::Attack()//�� ����
{
	return Chess_piece;
}
void chessManager::DeleteChess(POINT pt, HWND hWnd)
{
	for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)
	{
		makechess = *Chess_piece_iter;
		if (PtInRect(&makechess->Rt(), pt))//����� ��ġ�߿� ���콺��ġ�� �浹�� �ϸ�
		{
			if (makechess->Rank() == CHESSRANK_KING)
			{
				MessageBox(hWnd, TEXT("�¸� �ϼ̽��ϴ�."), TEXT("�����մϴ�."), MB_OK);
				SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
			Chess_piece_iter = Chess_piece.erase(Chess_piece_iter);
			return;
		}
	}

	temporary_Chess_piece.clear(); //�ӽú��� �����
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
		if (pan->Rt_x() == makechess->Rt_x() && pan->Rt_y() == makechess->Rt_y())//�� �ǿ� ĳ���Ͱ� ������..
		{
			return false;
		}
	}
	return true;
}
void chessManager::promotion(HWND hWnd,int y)//���� ���⼭ �ӽú����� ������Ű������ 
{
	int Rank = CHESSRANK_KNIGHT;
	temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //�ӽú��� �̵��� ��
	temporary_makechess = *temporary_Chess_piece_iter;
	if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
	{
		TCHAR buf[256];
		for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)//���Ʊ���
		{
			makechess = *Chess_piece_iter;

			if (temporary_makechess == makechess)
			{
				if (y == makechess->Rt_y())//y���� ������ ����
				{
					while (1)
					{
						switch (Rank)
						{
						case CHESSRANK_KNIGHT:
							if (MessageBox(hWnd, TEXT("����Ʈ�� �ٲٽðڽ��ϴ�."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("����Ʈ�� �Ǿ����ϴ�."), TEXT("�±�"), NULL);
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
							if (MessageBox(hWnd, TEXT("������� �ٲٽðڽ��ϴ�."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("����� �Ǿ����ϴ�."), TEXT("�±�"), NULL);
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
							if (MessageBox(hWnd, TEXT("������ �ٲٽðڽ��ϴ�."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("���� �Ǿ����ϴ�."), TEXT("�±�"), NULL);
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
							if (MessageBox(hWnd, TEXT("������ �ٲٽðڽ��ϴ�."), TEXT("promotion"), MB_ICONQUESTION | MB_YESNO) == IDYES)
							{
								MessageBox(hWnd, TEXT("���� �Ǿ����ϴ�."), TEXT("�±�"), NULL);
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
	//������ �� ������ ã�´�.
	for (m_Enemy_Chess_piece_iter = enemy->begin(); m_Enemy_Chess_piece_iter != enemy->end(); m_Enemy_Chess_piece_iter++)//������ã��
	{
		m_EnemyKing = *m_Enemy_Chess_piece_iter;
		if (m_EnemyKing->Rank() == CHESSRANK_KING)
		{
			break;//ã���� ����
		}
	}
	int count = 0;
	int phawncount = 0;
	temporary_Chess_piece_iter = temporary_Chess_piece.begin(); //�ӽú��� �̵��� ��
	temporary_makechess = *temporary_Chess_piece_iter;
	for (m_Enemy_Chess_piece_iter = enemy->begin(); m_Enemy_Chess_piece_iter != enemy->end(); m_Enemy_Chess_piece_iter++)//���������
	{
		m_Enemy = *m_Enemy_Chess_piece_iter;
		if (temporary_makechess->Rank() == CHESSRANK_PHAWN)
		{
			if (temporary_makechess->phawnAtack(m_EnemyKing->Rt(), m_Enemy->Rt(), Team) == true)
				phawncount++;
		}
		if (temporary_makechess->MoveCheck(m_EnemyKing->Rt(), m_Enemy->Rt(), Team) == true)
			count++;
		for (Chess_piece_iter = Chess_piece.begin(); Chess_piece_iter != Chess_piece.end(); Chess_piece_iter++)//���Ʊ���
		{
			makechess = *Chess_piece_iter;

			if (temporary_makechess != makechess)
			{
				if (count == enemy->size() && temporary_makechess->MoveCheck(m_EnemyKing->Rt(), makechess->Rt(), Team) == true)
				{//���հ� �����̴� �����̿� ������ �ְų� �Ʊ���������
					MessageBox(hWnd, TEXT("üũ����Ʈ�Դϴ�."), TEXT("MessageBox"), MB_OK);
					temporary_Chess_piece.clear();
					return;
				}
				else if (phawncount == 1)
				{
					MessageBox(hWnd, TEXT("üũ����Ʈ�Դϴ�."), TEXT("MessageBox"), MB_OK);
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
