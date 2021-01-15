#include "GameManager.h"

GameManager* GameManager::m_This = NULL;

GameManager::GameManager()
{
	m_bcrash = false;
	m_icount = 0;
	m_iScore = 0;
	m_irandem = 0;
	m_dwLastTime = GetTickCount();
	m_dwCurTime = GetTickCount();
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
	m_ground->Init(0,200,m_hBackBuffer);
	for (int i = 0; i < MAX; i++)
	{
		m_Crowd[i] = new crowd;
		m_Crowd[i]->Init(64 * i, 136, m_hBackBuffer);
	}
	m_elephant[0] = new Elephant;
	m_elephant[0]->Init(1134,133,m_hBackBuffer);
	m_elephant[1] = new Elephant;
	m_elephant[1]->Init(2334, 133, m_hBackBuffer);
	m_miter = new Miter;
	m_miter->Init(800,555,m_hBackBuffer);
	m_jar = new jar;
	m_jar->Init(700,470,m_hBackBuffer);

	m_leftring[0] = new LeftFirering;
	m_leftring[0]->Init(1300, 210, m_hBackBuffer);
	m_rightring[0] = new RightFirering;
	m_rightring[0]->Init(1335, 210, m_hBackBuffer);

	m_leftring[1] = new LeftFirering;
	m_leftring[1]->Init(1800, 210, m_hBackBuffer);
	m_rightring[1] = new RightFirering;
	m_rightring[1]->Init(1835, 210, m_hBackBuffer);

	
	m_MoneyFirering = new MoneyFirering;
	m_MoneyFirering->Init(1820, 270 ,m_hBackBuffer);
	m_MoneyleftFirering = new MoneyleftFirering;
	m_MoneyleftFirering->Init(1800,210,m_hBackBuffer);
	m_MoneyrightFirering = new MoneyrightFirering;
	m_MoneyrightFirering->Init(1835, 210,m_hBackBuffer);

	m_EndBox = new EndBox;
	m_EndBox->Init(1300, 470, m_hBackBuffer);
	SetTimer(m_hWnd, 0, 10000, NULL);
	ReleaseDC(m_hWnd, hdc);
}
void GameManager::Update()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwLastTime) / 500.0f;

	if (m_state == DIE)
	{
		if (m_fDeltaTime >= 2)
		{
			replay();
			m_state = NOMAL;
			m_icount = 0;
			m_iScore = 0;
		}			
	}
	else if (m_fDeltaTime >= 0.08f)
	{
		if (character->hartcount() == 0)//목숨이 없을떄 종료
		{
			if (MessageBox(m_hWnd, TEXT(m_charMiter), TEXT("수고하셨습니다."), MB_OK) == IDOK)
			{
				character->replay();
				replay();
			}
		}
		else
		{
			if (m_bcrash == true)//재충돌 지연시간
				m_icount++;
			if (m_state == WIN )
			{
				m_icount = 0;
				m_iScore = 0;
				Render();
				return;
			}
			if (m_icount == 10)
			{
				m_icount = 0;
				m_bcrash = false;
			}

			character->Update(m_fDeltaTime, m_miter->miter());
			crash();
			if (m_miter->miter() == 0) //0미터일떄
			{
				m_EndBox->Update(character->direction(), m_fDeltaTime);

				if (m_EndBox->Endlocation().left > 1180)
				{
					m_jar->Update(character->direction(), m_fDeltaTime);
					m_miter->Update(character->direction(), m_fDeltaTime);
				}
			}
			else
			{
				if (character->direction() != IDLE)
				{
					for (int i = 0; i < MAX; i++)
						m_Crowd[i]->Update(character->direction(), m_fDeltaTime);
					m_elephant[0]->Update(character->direction(), m_fDeltaTime);
					m_elephant[1]->Update(character->direction(), m_fDeltaTime);
					m_jar->Update(character->direction(), m_fDeltaTime);
					m_miter->Update(character->direction(), m_fDeltaTime);
				}
			}
			m_leftring[0]->Update(m_fDeltaTime);
			m_rightring[0]->Update(m_fDeltaTime);

			if (m_rightring[1]->randommoneyring() == 1) //랜덤숫자가 1일때
			{
				m_MoneyFirering->Update(m_fDeltaTime);
				m_MoneyleftFirering->Update(m_fDeltaTime);
				m_MoneyrightFirering->Update(m_fDeltaTime);

				if (m_MoneyrightFirering->ringlocation().left <= -100) 
				{
					m_rightring[1]->RandomCountReset(1);
				}
			}
			else
			{
				m_leftring[1]->Update(m_fDeltaTime);
				m_rightring[1]->Update(m_fDeltaTime);
			}

			Score();
			Render();
			InvalidateRect(m_hWnd, NULL, false);
		}
		m_dwLastTime = m_dwCurTime;
	}
}
void GameManager::Score()
{
	m_iScore += m_jar->Score(character->characterlocation().left, character->state());
	m_iScore += m_leftring[0]->Score(character->characterlocation().left, character->state());
	m_iScore += m_leftring[1]->Score(character->characterlocation().left, character->state());
	m_iScore += m_MoneyleftFirering->Score(character->characterlocation().left, character->state());
	
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
		else if (IntersectRect(&rt, &character->characterlocation(), &m_EndBox->Endlocation()))//충돌이 캐릭과 단상이면
		{
			character->endlocation(m_EndBox->Endlocation()); //캐릭터모션
			for(int i=0;i<MAX;i++)
				m_Crowd[i]->End();
			
			m_state = WIN;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_rightring[0]->ringlocation()))//충돌이 캐릭과 일반 오른쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_leftring[0]->ringlocation()))//충돌이 캐릭과 일반 왼쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_rightring[1]->ringlocation()))//충돌이 캐릭과 일반 오른쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_leftring[1]->ringlocation()))//충돌이 캐릭과 일반 왼쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}		
		else if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyleftFirering->ringlocation()))//충돌이 캐릭과 돈이있는 왼쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyrightFirering->ringlocation()))//충돌이 캐릭과 돈이있는 오른쪽불타는링일떄
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyFirering->money()))//충돌이 캐릭과 돈일떄
		{
			m_iScore += m_MoneyFirering->moneyScore();
			m_bcrash = true;
		}
	}
}

void GameManager::replay()
{
	character->Motion();
	for (int i = 0; i < MAX; i++)
		m_Crowd[i]->replay(64 * i, 136);

	m_elephant[0]->replay(1134, 133);
	m_elephant[1]->replay(2334, 133);
	m_miter->replay(800, 555);
	m_jar->replay(700,470);
	m_MoneyleftFirering->replay(1300,210);
	m_MoneyFirering->replay(1320,270);	
	m_leftring[0]->replay(1300, 210);
	m_rightring[0]->replay(1335, 210);
	m_leftring[1]->replay(1800, 210);
	m_rightring[1]->replay(1835, 210);	
	m_MoneyrightFirering->replay(1335,210);
}

void GameManager::Render()
{
	hdc = GetDC(m_hWnd);
	m_hBackBuffer = CreateCompatibleDC(hdc);
	m_hBitMap = CreateCompatibleBitmap(hdc, 1200, 600);
	m_hOldBitMap = (HBITMAP)SelectObject(m_hBackBuffer, m_hBitMap);
	m_ground->Render(m_hBackBuffer);
	for (int i = 0; i < MAX; i++)
		m_Crowd[i]->Render(m_hBackBuffer);
	m_elephant[0]->Render(m_hBackBuffer);
	m_elephant[1]->Render(m_hBackBuffer);
	m_miter->Render(m_hBackBuffer);

	m_MoneyleftFirering->Render(m_hBackBuffer);
	m_MoneyFirering->Render(m_hBackBuffer);
	m_leftring[0]->Render(m_hBackBuffer);
	m_leftring[1]->Render(m_hBackBuffer);
	character->Render(m_hBackBuffer);
	m_rightring[0]->Render(m_hBackBuffer);
	m_rightring[1]->Render(m_hBackBuffer);

	m_MoneyrightFirering->Render(m_hBackBuffer);

	m_jar->Render(m_hBackBuffer);
	if (m_miter->miter() == 10)
	{
		m_EndBox->Render(m_hBackBuffer);		
	}

	TextOut(m_hBackBuffer, 550, 50, m_charMiter, lstrlen(m_charMiter));
	BitBlt(hdc, 0, 0, 1200, 650, m_hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
	DeleteDC(m_hBackBuffer);
	DeleteObject(m_hBitMap);
}
GameManager::~GameManager()
{
}
