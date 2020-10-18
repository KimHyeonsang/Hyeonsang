#include "GameManager.h"

GameManager* GameManager::m_pThis = NULL;

GameManager::GameManager()
{
	m_ix = 20;
	m_iy = 20;
	srand(time(NULL));
}

void GameManager::Init(HWND hWnd, HINSTANCE hInst)//����
{
	HDC hdc = GetDC(hWnd);
	int random;
	for (int i = 0; i < 20; i++)
	{
		random = Random();
		m_btmap = new Bitmap;
		if (m_ix > 745)
		{
			m_iy += 240;
			m_ix = 20;
			m_btmap->Init(hdc, hInst, m_ix, m_iy, random);
			m_v.push_back(m_btmap);
			m_ix += 150;
		}
		else
		{
			m_btmap->Init(hdc, hInst, m_ix, m_iy, random);
			m_v.push_back(m_btmap);
			m_ix += 150;
		}
	}
	
}

void GameManager::BakcInit(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	m_ix = 20;
	m_iy = 20;
	for (int i = 0; i < 20; i++) //�޸�
	{
		m_btmap = new Bitmap;
		if (m_ix > 725)
		{
			m_iy += 240;
			m_ix = 20;
			m_btmap->Init(hdc, hInst, m_ix, m_iy, 111);
			m_v.push_back(m_btmap);
			m_ix += 150;
		}
		else
		{
			m_btmap->Init(hdc, hInst, m_ix, m_iy, 111);
			m_v.push_back(m_btmap);
			m_ix += 150;
		}
	}
}
void GameManager::Draw(HDC hdc)
{
	for (iter = m_v.begin(); iter != m_v.end(); iter++) //��ü�׸���.
	{
		m_btmap = *iter;
		m_btmap->Draw(hdc);
	}
}
void GameManager::Click(int x,int y, HWND hWnd)//Ŭ���� ȭ�� �޸��� ���� ��Ų��.(����) 1����
{
	for (iter = m_v.begin(); iter != m_v.end(); iter++)
	{
		m_btmap = *iter;
		if ((x > m_btmap->Getx() && x < m_btmap->Getx() + m_btmap->GetWIDH()) && (y > m_btmap->Gety() && y < m_btmap->Gety() + m_btmap->GetHeight()) && m_btmap->Animal() == 111)//x��ǥ�� ��Ʈ�� ũ�� �ȿ� ������
		{
			m_vClose.push_back(m_btmap);//ù��° �޸� ����
			iter = m_v.erase(iter);//ù���� �޸� ������ ����
			return;
		}
		else if ((x > m_btmap->Getx() && x < m_btmap->Getx() + m_btmap->GetWIDH()) && (y > m_btmap->Gety() && y < m_btmap->Gety() + m_btmap->GetHeight()) && m_btmap->Animal() != 111)
		{//���� open�� iter�� �ٸ����
			m_vOpen.push_back(m_btmap); //�ո�ī�� ����

		}
	}
	//�̹� ���µȰ� �������Ѵ�.
	if (m_vClose.size() != m_vOpen.size())
	{
		m_vOpen.pop_back();
	}
}
void GameManager::ClickCheck(HWND hWnd)//Ŭ���� ȭ�� �޸��� ���� ��Ų��.(��) 2����
{
	m_iOpenSize = m_vOpen.size();
	m_iCloseSize = m_vClose.size();
	if (m_iOpenSize > 2 && m_iCloseSize>2) //�񱳸� �ϴµ� ������ �ϳ��� �Ǿ������� ��
	{
		iter = m_vOpen.begin();
		m_btmap = *iter;			
		open = m_vOpen.begin() + 1;
		m_btmapOpen = *open;
		if (m_btmapOpen->Animal() != m_btmap->Animal())//�ٸ��ٸ� ������ ������
		{
			for (iter = m_vClose.begin(); iter != m_vClose.begin() + 2; iter++)
			{
				m_btmap = *iter;
				m_v.push_back(m_btmap);
			}
			open = m_vClose.erase(m_vClose.begin(), m_vClose.begin()+2);//�����
			open = m_vOpen.erase(m_vOpen.begin(), m_vOpen.begin() + 2);//�����
		}
		else if (m_btmapOpen->Animal() == m_btmap->Animal())//������ 
		{
			open = m_vClose.erase(m_vClose.begin(), m_vClose.begin() + 2);//�����
			open = m_vOpen.erase(m_vOpen.begin(), m_vOpen.begin() + 2);//�����
		}
	}	
}
int GameManager::Random()//�������� ���ڸ� �ϴµ� 2�� �̻��̸� �ٽ� ������
{
	//� ������ �������� �������
	while (1)
	{
		int randam = rand() % 10 + 101;
		int count = 0;
		for (iter = m_v.begin(); iter != m_v.end(); iter++)
		{
			m_btmap = *iter;
			if (m_btmap->Animal() == randam)
			{
				count++;
			}
		}
		if (count < 2)
			return randam;
	}
	
}
void GameManager::victory(HWND hWnd)
{
	if (m_v.size() != 20)
		return;
	if (m_v.size() == 20)
		MessageBox(hWnd, TEXT("�����ϼ̽��ϴ�."), TEXT("�������ϴ�."), MB_OK);
}
void GameManager::Release()
{
	delete(m_pThis);
}
GameManager::~GameManager()
{
	delete(m_btmap);
}
