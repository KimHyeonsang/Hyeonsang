#include "GameManager.h"

GameManager* GameManager::m_This = NULL;

GameManager::GameManager()
{
	m_bcrash = false;
	m_icount = 0;
	m_iScore = 0;
}

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	hdc = GetDC(m_hWnd);
	m_hBackBuffer = CreateCompatibleDC(hdc);
	m_hBitMap = CreateCompatibleBitmap(hdc, 1200, 600);
	m_hOldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_hBitMap);
	character = new Character;
	character->Init(m_hWnd, m_hBackBuffer);
	m_ground = new Ground;
	m_ground->Init(0,200,m_hBackBuffer, character->characterlocation());
	m_Crowd[0] = new crowd;
	m_Crowd[0]->Init(0,136,m_hBackBuffer, character->characterlocation());
	m_Crowd[1] = new crowd;
	m_Crowd[1]->Init(1200, 136, m_hBackBuffer, character->characterlocation());
	m_elephant[0] = new Elephant;
	m_elephant[0]->Init(1134,133,m_hBackBuffer, character->characterlocation());
	m_elephant[1] = new Elephant;
	m_elephant[1]->Init(2334, 133, m_hBackBuffer, character->characterlocation());
	m_miter = new Miter;
	m_miter->Init(800,555,m_hBackBuffer, character->characterlocation());
	m_jar = new jar;
	m_jar->Init(m_hBackBuffer, character->characterlocation());
	m_leftring = new LeftFirering;
	m_leftring->Init(m_hBackBuffer, character->characterlocation());
	m_rightring = new RightFirering;
	m_rightring->Init(m_hBackBuffer, character->characterlocation());
	
	m_MoneyFirering = new MoneyFirering;
	m_MoneyFirering->Init(m_hBackBuffer, character->characterlocation());
	m_MoneyleftFirering = new MoneyleftFirering;
	m_MoneyleftFirering->Init(m_hBackBuffer, character->characterlocation());
	m_MoneyrightFirering = new MoneyrightFirering;
	m_MoneyrightFirering->Init(m_hBackBuffer, character->characterlocation());

	m_EndBox = new EndBox;
	m_EndBox->Init(1300, 470, m_hBackBuffer, character->characterlocation());
	SetTimer(m_hWnd, 0, 10000, NULL);
	ReleaseDC(m_hWnd, hdc);
}
void GameManager::Update()
{
	if (character->hartcount() == 0)//목숨이 없을떄 종료
	{
		MessageBox(m_hWnd, TEXT(m_charMiter), TEXT("수고하셨습니다."), MB_OK);
		SendMessage(m_hWnd, WM_DESTROY, 0, 0);
		return;
	}
	else
	{
		if (m_bcrash == true)//재충돌 지연시간
			m_icount++;
		if ((m_state == WIN || m_state == DIE) && m_icount == 150)
		{
			replay();
			m_icount = 0;
			m_iScore = 0;
			m_state = NOMAL;
			return;
		}
		if (m_state == WIN || m_state == DIE)
		{
			return;
		}
		if (m_icount == 300)
		{
			m_icount = 0;
			m_bcrash = false;
		}
		character->Update();
		crash();
		if (m_miter->miter() == 10) //0미터일떄
		{
			m_EndBox->Update(character->characterlocation());

			if (m_EndBox->Endlocation().left > 1180)
			{
				m_jar->Update(character->characterlocation());
				m_miter->Update(character->characterlocation());
			}
		}
		else
		{
			if (character->direction() != IDLE)
			{
				m_Crowd[0]->Update(character->characterlocation());
				m_Crowd[1]->Update(character->characterlocation());
				m_elephant[0]->Update(character->characterlocation());
				m_elephant[1]->Update(character->characterlocation());
				m_jar->Update(character->characterlocation());
				m_miter->Update(character->characterlocation());
			}
		}
		m_leftring->Update();
		m_rightring->Update();

		m_MoneyFirering->Update();
		m_MoneyleftFirering->Update();
		m_MoneyrightFirering->Update();

		Render();
		InvalidateRect(m_hWnd, NULL, false);
	}
}
void GameManager::Score()
{
	m_iScore += m_jar->Score(character->characterlocation().left);
	m_iScore += m_leftring->Score(character->characterlocation().left);
	m_iScore += m_MoneyleftFirering->Score(character->characterlocation().left);
	
	wsprintf(m_charMiter, "%d점", m_iScore);
}
void GameManager::crash()
{
	if (m_bcrash == false)
	{
		if (IntersectRect(&rt, &character->characterlocation(), &m_jar->jarlocation()))//항아리랑 충돌이 되면 목숨이 까진다
		{			
			character->hartbreaker();
			m_bcrash = true;
			m_state = DIE;
		}
		if (IntersectRect(&rt, &character->characterlocation(), &m_EndBox->Endlocation()))//충돌이 캐릭과 단상이면
		{
			character->endlocation(m_EndBox->Endlocation()); //캐릭터모션
			m_Crowd[0]->End();
			m_Crowd[1]->End();
			
			m_state = WIN;
		}
		if (IntersectRect(&rt, &character->characterlocation(), &m_rightring->ringlocation()))//충돌이 캐릭과 일반 오른쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		if (IntersectRect(&rt, &character->characterlocation(), &m_leftring->ringlocation()))//충돌이 캐릭과 일반 왼쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyleftFirering->ringlocation()))//충돌이 캐릭과 돈이있는 왼쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyrightFirering->ringlocation()))//충돌이 캐릭과 돈이있는 오른쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyFirering->money()))//충돌이 캐릭과 돈일떄
		{
			m_iScore += m_MoneyFirering->moneyScore();
			m_bcrash = true;
		}
	}
}

void GameManager::replay()
{
	character->replay();
	m_Crowd[0]->replay(0, 136, character->characterlocation());
	m_Crowd[1]->replay(1200, 136, character->characterlocation());
	m_elephant[0]->replay(1134, 133, character->characterlocation());
	m_elephant[1]->replay(2334, 133, character->characterlocation());
	m_miter->replay(800, 555, character->characterlocation());
	m_jar->replay();
	m_MoneyleftFirering->replay();
	m_MoneyFirering->replay();
	m_leftring->replay();
	m_rightring->replay();
	m_MoneyrightFirering->replay();
}

void GameManager::Render()
{
	hdc = GetDC(m_hWnd);
	m_hBackBuffer = CreateCompatibleDC(hdc);
	m_hBitMap = CreateCompatibleBitmap(hdc, 1200, 600);
	m_hOldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_hBitMap);
	m_ground->Render(m_hBackBuffer);
	m_Crowd[0]->Render(m_hBackBuffer);
	m_Crowd[1]->Render(m_hBackBuffer);
	m_elephant[0]->Render(m_hBackBuffer);
	m_elephant[1]->Render(m_hBackBuffer);
	m_miter->Render(m_hBackBuffer);

	m_MoneyleftFirering->Render(m_hBackBuffer);
	m_MoneyFirering->Render(m_hBackBuffer);
	m_leftring->Render(m_hBackBuffer);
	character->Render(m_hBackBuffer);
	m_rightring->Render(m_hBackBuffer);

	m_MoneyrightFirering->Render(m_hBackBuffer);

	m_jar->Render(m_hBackBuffer);
	if (m_miter->miter() == 10)
	{
		m_EndBox->Render(m_hBackBuffer);		
	}
	Score();
	TextOut(m_hBackBuffer, 550, 50, m_charMiter, lstrlen(m_charMiter));
	BitBlt(hdc, 0, 0, 1200, 650, m_hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
	DeleteDC(m_hBackBuffer);
	DeleteObject(m_hBitMap);
}
GameManager::~GameManager()
{
}
