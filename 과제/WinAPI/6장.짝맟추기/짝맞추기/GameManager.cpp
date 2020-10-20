#include "GameManager.h"

GameManager* GameManager::m_pThis = NULL;

GameManager::GameManager()
{
	m_ix = 20;
	m_iy = 20;
	srand(time(NULL));
}

void GameManager::Init(HWND hWnd, HINSTANCE hInst)//생성
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
	for (int i = 0; i < 20; i++) //뒷면
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
	for (iter = m_v.begin() ; iter != m_v.end(); iter++) //전체그리기.
	{
		m_btmap = *iter;
		if(m_btmap->Animal() == 111) //뒷면만 그린다.
			m_btmap->Draw(hdc);
		for (open = m_vtemporaryOpen.begin(); open != m_vtemporaryOpen.end(); open++) //오픈한거 그리기
		{
			m_btmapOpen = *open;
			if(m_btmapOpen->Animal() == m_btmap->Animal() && (m_btmapOpen->Getx() == m_btmap->Getx()) && (m_btmapOpen->Gety() == m_btmap->Gety()))
				m_btmap->Draw(hdc);
		}
	}
}
void GameManager::Click(int x,int y, HWND hWnd)//클릭을 화면 뒷면을 삭제 시킨다.(저장) 1순위
{
	for (iter = m_v.begin(); iter != m_v.end(); iter++)
	{
		m_btmap = *iter;
		if ((x > m_btmap->Getx() && x < m_btmap->Getx() + m_btmap->GetWIDH()) && (y > m_btmap->Gety() && y < m_btmap->Gety() + m_btmap->GetHeight()) && m_btmap->Animal() == 111)//x좌표가 비트맵 크기 안에 있을떄
		{
			m_vClose.push_back(m_btmap);//첫번째 뒷면 저장
			iter = m_v.erase(iter);//첫번쨰 뒷면 삭제를 저장
			return;
		}
		else if ((x > m_btmap->Getx() && x < m_btmap->Getx() + m_btmap->GetWIDH()) && (y > m_btmap->Gety() && y < m_btmap->Gety() + m_btmap->GetHeight()) && m_btmap->Animal() != 111)
		{//만약 open과 iter가 다를경우
			m_vOpen.push_back(m_btmap); //앞면카드 저장
			m_vtemporaryOpen.push_back(m_btmap);
		}
	}
	//이미 오픈된건 지워야한다.
	if (m_vClose.size() != m_vOpen.size())
	{
		m_vOpen.pop_back();
	}
}
void GameManager::ClickCheck(HWND hWnd)//클릭을 화면 뒷면을 삭제 시킨다.(비교) 2순위
{
	if (m_vClose.size() > 2 && m_vOpen.size() > 2) //비교를 하는데 저장이 하나라도 되어있으면 비교
	{
		iter = m_vOpen.begin();
		m_btmap = *iter;			
		open = m_vOpen.begin() + 1;
		m_btmapOpen = *open;
		if (m_btmapOpen->Animal() != m_btmap->Animal())//다르다면 검은거 돌리기
		{
			for (iter = m_vClose.begin(); iter != m_vClose.begin() + 2; iter++)
			{
				m_btmap = *iter;
				m_v.push_back(m_btmap);
			}
			open = m_vClose.erase(m_vClose.begin(), m_vClose.begin() + 2);//지우기
			open = m_vOpen.erase(m_vOpen.begin(), m_vOpen.begin() + 2);//지우기
			if(m_vtemporaryOpen.size() > 3)
				open = m_vtemporaryOpen.erase(m_vtemporaryOpen.end() - 3, m_vtemporaryOpen.end() - 1);//지우기
			else
			{
				open = m_vtemporaryOpen.erase(m_vtemporaryOpen.begin(), m_vtemporaryOpen.begin() + 2);//지우기
			}
		}
		else if (m_btmapOpen->Animal() == m_btmap->Animal())//같으면 
		{
			open = m_vClose.erase(m_vClose.begin(), m_vClose.begin() + 2);//지우기
			open = m_vOpen.erase(m_vOpen.begin(), m_vOpen.begin() + 2);//지우기
		}
	}	
}
int GameManager::Random()//랜덤으로 숫자를 하는데 2개 이상이면 다시 돌리기
{
	//어떤 동물이 었을떄에 몇마리인지
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
		MessageBox(hWnd, TEXT("수고하셨습니다."), TEXT("끝났습니다."), MB_OK);
}

void GameManager::TimeCheck()//1.5초뒤
{
	if (m_vOpen.size() >= 2)
	{
		iter = m_vOpen.begin();
		m_btmap = *iter;
		open = m_vOpen.begin() + 1;
		m_btmapOpen = *open;
		if (m_btmapOpen->Animal() != m_btmap->Animal())//다르다면 검은거 돌리기
		{
			for (iter = m_vClose.begin(); iter != m_vClose.begin() + 2; iter++)
			{
				m_btmap = *iter;
				m_v.push_back(m_btmap);
			}
			m_vClose.clear();//지우기
			m_vOpen.clear();//지우기
	
			open = m_vtemporaryOpen.erase(m_vtemporaryOpen.end() - 2, m_vtemporaryOpen.end());//지우기
		}
	}
}
void GameManager::Release()
{
	delete(m_pThis);
}
GameManager::~GameManager()
{
	delete(m_btmap);
}
