#include "GameManager.h"

GameManager* GameManager::m_This = NULL;

GameManager::GameManager()
{
	m_bcrash = false;
	m_iInvincibilityTime = 0;
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
		if (i == 10)
		{
			back = new Elephant;
			back->Init(62 * i, 133, m_hBackBuffer);
			background.push_back(back);
		}
		else
		{
			back = new crowd;
			back->Init(62 * i, 136, m_hBackBuffer);
			background.push_back(back);
		}		
	}
	m_Crowd[0] = new crowd;
	m_Crowd[0]->Init(0, 136, m_hBackBuffer);
	m_Crowd[1] = new crowd;
	m_Crowd[1]->Init(1136, 136, m_hBackBuffer);
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

	if (m_state == DIE) //����� ��������
	{
		if (m_fDeltaTime >= 0.1f)
		{
			m_iInvincibilityTime++;
			character->DamageMotion();
			Render();

			if (m_iInvincibilityTime == 3)
			{
				
				m_state = NOMAL;
				m_iInvincibilityTime = 0;
			}
			m_dwLastTime = m_dwCurTime;
		}
	}
	else if (m_fDeltaTime >= 0.08f)
	{
		if (character->hartcount() == 0)//����� ������ ����
		{
			if (MessageBox(m_hWnd, TEXT(m_charMiter), TEXT("�����ϼ̽��ϴ�."), MB_OK) == IDOK)
			{
				character->replay();
				replay();
			}
		}
		else
		{
			if (m_bcrash == true)//���浹 �����ð�(�����ð�)
				m_iInvincibilityTime++;
			if (m_state == WIN )
			{
				m_iInvincibilityTime = 0;
				Render();
				m_dwLastTime = m_dwCurTime;
				return;
			}
			if (m_iInvincibilityTime == CRASH_TIME)
			{
				m_iInvincibilityTime = 0;
				m_bcrash = false;
			}

			character->Update(m_fDeltaTime, m_miter->miter());
			m_leftring[0]->Update(character->direction(), m_fDeltaTime);
			m_rightring[0]->Update(character->direction(), m_fDeltaTime);

			if (m_rightring[1]->randommoneyring() == RANDOM) //�������ڰ� 1�϶�
			{
				m_MoneyFirering->Update(character->direction(), m_fDeltaTime);
				m_MoneyleftFirering->Update(character->direction(), m_fDeltaTime);
				m_MoneyrightFirering->Update(character->direction(), m_fDeltaTime);

				if (m_MoneyrightFirering->ringlocation().left <= -100)
				{
					m_rightring[1]->RandomCountReset(1);
				}
			}
			else
			{
				m_leftring[1]->Update(character->direction(), m_fDeltaTime);
				m_rightring[1]->Update(character->direction(), m_fDeltaTime);
			}
			crash();
			if (m_miter->miter() == FINISH) //0�����ϋ�
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
					for (background_iter = background.begin();background_iter != background.end(); background_iter++)
					{
						back = *background_iter;
						back->Update(character->direction(), m_fDeltaTime);
					}
					m_jar->Update(character->direction(), m_fDeltaTime);
					m_miter->Update(character->direction(), m_fDeltaTime);					
				}
			}
			Score();
			Render();
			m_dwLastTime = m_dwCurTime;
			InvalidateRect(m_hWnd, NULL, false);
		}
	}
}
void GameManager::Score()
{
	m_iScore += m_jar->Score(character->characterlocation().left, character->state());
	m_iScore += m_leftring[0]->Score(character->characterlocation().left, character->state());
	m_iScore += m_leftring[1]->Score(character->characterlocation().left, character->state());
	m_iScore += m_MoneyleftFirering->Score(character->characterlocation().left, character->state());
	wsprintf(m_charMiter, "%d��", m_iScore);
}
void GameManager::crash()
{
	if (m_bcrash == false)
	{
		if (IntersectRect(&rt, &character->characterlocation(), &m_jar->jarlocation()))//�׾Ƹ��� �浹�� �Ǹ� ����� ������
		{			
			character->hartbreaker();
			m_bcrash = true;
			m_state = DIE;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_EndBox->Endlocation()))//�浹�� ĳ���� �ܻ��̸�
		{
			character->endlocation(); //ĳ���͸��
			for (background_iter = background.begin();background_iter != background.end(); background_iter++)
			{
				back = *background_iter;
				back->End();
			}
			m_Crowd[0]->End();
			m_Crowd[1]->End();
			m_state = WIN;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_rightring[0]->ringlocation()))//�浹�� ĳ���� �Ϲ� �����ʺ�Ÿ�¸��ϋ�
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_leftring[0]->ringlocation()))//�浹�� ĳ���� �Ϲ� ���ʺ�Ÿ�¸��ϋ�
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_rightring[1]->ringlocation()))//�浹�� ĳ���� �Ϲ� �����ʺ�Ÿ�¸��ϋ�
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_leftring[1]->ringlocation()))//�浹�� ĳ���� �Ϲ� ���ʺ�Ÿ�¸��ϋ�
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}		
		else if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyleftFirering->ringlocation()))//�浹�� ĳ���� �����ִ� ���ʺ�Ÿ�¸��ϋ�
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyrightFirering->ringlocation()))//�浹�� ĳ���� �����ִ� �����ʺ�Ÿ�¸��ϋ�
		{
			character->hartbreaker();
			m_state = DIE;
			m_bcrash = true;
		}
		else if (IntersectRect(&rt, &character->characterlocation(), &m_MoneyFirering->money()))//�浹�� ĳ���� ���ϋ�
		{
			m_iScore += m_MoneyFirering->moneyScore();
			m_bcrash = true;
		}
	}
}

void GameManager::replay()
{
	character->DamageMotion();
	int number = 0;
	for (background_iter = background.begin();background_iter != background.end(); background_iter++)
	{
		back = *background_iter;
		if (number == 10)
		{
			back->replay(62 * number, 133);
		}
		else
		{
			back->replay(62 * number, 136);
		}
		number++;
	}
	m_miter->replay(800, 555);
	m_jar->replay(700,470);
	m_MoneyleftFirering->replay(1300,210);
	m_MoneyFirering->replay(1320,270);	
	m_leftring[0]->replay(1300, 210);
	m_rightring[0]->replay(1335, 210);
	m_leftring[1]->replay(1800, 210);
	m_rightring[1]->replay(1835, 210);	
	m_MoneyrightFirering->replay(1335,210);
	m_EndBox->replay(1300, 470);
	m_iScore = 0;
	m_state = NOMAL;
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
	for (background_iter = background.begin();background_iter != background.end(); background_iter++)
	{
		back = *background_iter;
		back->Render(m_hBackBuffer);
	}	
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
	if (m_miter->miter() == FINISH)
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
