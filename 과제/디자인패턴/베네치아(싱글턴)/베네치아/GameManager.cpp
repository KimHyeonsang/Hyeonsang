#include "GameManager.h"

GameManager* GameManager::m_This = NULL;

GameManager::GameManager()
{
	srand((unsigned int)time(NULL));
	m_iWith = WIDTH;
	m_iHeight = HEIGHT;
	storycount = 0;
	Name = "? ? ?";
	m_bstory = false;
	m_bStop = false;
	bstage = false;
	bEffect = false;
	m_iwardcount = 0;
	Score = 0;
	life = 9;
	m_istagenumber = 1;
	m_bchect = false;
	m_binterface = false;
}
void GameManager::underinterface() //목숨 ,점수 ,이름
{
	int Life_position = m_iWith * 0.2f + 4;
	in_face.Setcolor(RED, DARKGRAY);
	in_face.DrawMidText("Life : ", m_iWith * 0.2f, m_iHeight + 1);
	for (int i = 0; i < life + 1; i++)
	{
		in_face.Setcolor(DARKGRAY, DARKGRAY);							//그리기
		in_face.DrawMidText("♥", Life_position, m_iHeight + 1);
		Life_position += 2;
	}
	Life_position = m_iWith * 0.2f + 4;
	for (int i = 0; i < life; i++)
	{
		in_face.Setcolor(RED, DARKGRAY);							//그리기
		in_face.DrawMidText("♥", Life_position, m_iHeight + 1);
		Life_position += 2;
	}
	in_face.DrawMidText("Score : ", m_iWith, m_iHeight + 1);
	cout << Score;
	in_face.DrawMidText("Name : ", m_iWith * 1.8f, m_iHeight + 1);
	in_face.Setcolor(RED, DARKGRAY);
	in_face.DrawMidText(Name, m_iWith * 1.9f, m_iHeight + 1);
}


void GameManager::gostory()//countting 추가
{
	m_bstory = true;
	int readtime = clock();
	int endtime;
	int Height = m_iHeight * 0.2f;
	int count[1];
	int countting = 0;
	int number = 0;
	int i = 0;
	ifstream storyLoad;
	storyLoad.open("베네치아_스토리.txt");
	if (storyLoad.is_open())
	{
		while (storyLoad.eof() == false)
		{

			if (number == 0)
			{
				storyLoad >> count[0];
				countting = count[0];
				strStory = new string[countting];
			}

			getline(storyLoad, strStory[number]);
			number++;
		}
		storyLoad.close();
	}
	while (1) //스크롤처럼 보이게하기
	{
		if (Skip() == true)
			break;
		if (clock() - readtime >= 1000)
		{
			if (storycount >= 0 && storycount < 10) //10칸까지
			{
				in_face.Setcolor(BLUE, DARKGRAY);
				in_face.DrawMidText(strStory[i], m_iWith, Height);
				Height++;
				readtime = clock();
				i++;
			}
			else //10칸이후
			{
				if (Skip() == true)
					break;
				Height = m_iHeight * 0.2f;
				if (storycount < countting)
				{
					for (i = storycount - 10; i < storycount; i++)
					{
						in_face.Setcolor(DARKGRAY, DARKGRAY);
						in_face.DrawMidText(strStory[i], m_iWith, Height);
						Height++;
					}
					Height = m_iHeight * 0.2f;
					for (i = storycount - 9; i < storycount; i++)
					{
						in_face.Setcolor(BLUE, DARKGRAY);
						in_face.DrawMidText(strStory[i], m_iWith, Height);
						Height++;
					}
					if (clock() - readtime >= 1000)
					{
						in_face.Setcolor(BLUE, DARKGRAY);
						in_face.DrawMidText(strStory[storycount], m_iWith, Height);
						readtime = clock();
					}
				}
				else
					break;
			}
			storycount++;
		}
	}

}
void GameManager::story_setName()
{
	in_face.Setcolor(GREEN, DARKGRAY);
	in_face.BoxDraw(0, 0, m_iWith, m_iHeight);
	underinterface();
	ORIGINAL
		in_face.Setcolor(BLUE, DARKGRAY);
	in_face.BoxDraw(m_iWith, m_iHeight*0.7f, 20, 5);
	in_face.DrawMidText("Skip : s", m_iWith, m_iHeight *0.7f + 2);
	ORIGINAL
}
char GameManager::Skip()
{
	char Key;
	if (kbhit())
	{
		Key = getch();
		switch (Key)
		{
		case 's':
			return true;
			break;
		}
	}
}
void GameManager::SetName()
{
	system("cls");
	in_face.Setcolor(GREEN, DARKGRAY);
	in_face.BoxDraw(0, 0, m_iWith, m_iHeight);
	underinterface();
	in_face.Setcolor(DARKGRAY, DARKGRAY);
	in_face.DrawMidText(Name, m_iWith * 1.9f, m_iHeight + 1);
	in_face.Setcolor(BLUE, DARKGRAY);
	in_face.DrawMidText("이름 입력", m_iWith, m_iHeight *0.6f);
	in_face.BoxDraw(m_iWith, m_iHeight*0.7f, 20, 5);
	in_face.gotoxy(m_iWith, m_iHeight *0.7f + 2);
	cin >> Name;
	ORIGINAL
}
void GameManager::Play()
{
	int stagetime = clock();
	int itemclock = clock();
	in_face.Setcolor(GREEN, DARKGRAY);
	in_face.BoxDraw(0, 0, m_iWith, m_iHeight);
	while (1)
	{
		stage(stagetime);
		if(m_binterface == false)
			underinterface();//목숨,점수,이름인터페이스
		if (bstage == true) //스테이지 시작
		{
			m_binterface = true;
			ward.SettingWard();//단어셋팅
			ward.dropward();
			if (ward.lifeless(m_iHeight) == true) // 게임오버
			{
				if (life <= 1)
				{
					rank.setRanking(Name, m_istagenumber, Score);
					ward.reset();
					return;
				}
				else
				{
					life--;
					m_binterface = false;
				}
			}
			ward.wardLive(m_iHeight);
			if (m_bStop == false)
				chetting(stagetime);
			else
			{
				if (clock() - stoptime >= 4000)
					m_bStop = false;
			}
			if (bEffect == true)
			{
				ward.reitem(bEffect);
			}
		}
	}
}
void GameManager::chetting(int& stagetime) //단어를 입력
{
	char key;
	in_face.Setcolor(BLUE, DARKGRAY);
	if (m_bchect == false)
		in_face.BoxDraw(m_iWith, m_iHeight*0.7f, 20, 5);
	in_face.DrawMidText(strtemp, m_iWith, m_iHeight *0.7f + 2);
	if (kbhit())
	{
		key = getch();
		if (key == ENTER)
		{
			m_bchect = false;
			m_iwardcount = 0;
			strUser = strtemp;
			strtemp.clear();

			if (ward.Dies(m_iHeight, strUser, this) == true)
			{
				in_face.Setcolor(DARKGRAY, DARKGRAY);
				in_face.DrawMidText(strtemp, m_iWith, m_iHeight *0.7f + 2);
				Score += 100;
				bEffect = true;//효과
				m_binterface = false;
				LevelUp(stagetime);
			}
			else
			{
				in_face.Setcolor(RED, DARKGRAY);
				in_face.DrawMidText("failed compare!!", m_iWith, m_iHeight *0.7f + 2);
				m_bStop = true;
				stoptime = clock();
			}

		}
		if (key >= 'A' && key <= 'Z' || key >= 'a' && key <= 'z')
		{
			m_bchect = true;
			if (m_iwardcount >= 20)
			{
				in_face.Setcolor(BLUE, DARKGRAY);
				in_face.DrawMidText("20글자수 초과", m_iWith, m_iHeight *0.6f);
			}
			else
			{
				strtemp = strtemp + key;
				m_iwardcount++;
			}
		}
		if (key == BACKSPACE)
		{
			if (m_iwardcount <= 0)
				m_iwardcount = 0;
			else
			{
				m_iwardcount--;
				m_bchect = false;
				strtemp.pop_back();
				if (m_iwardcount == 19)
				{
					in_face.Setcolor(DARKGRAY, DARKGRAY);
					in_face.DrawMidText("20글자수 초과", m_iWith, m_iHeight *0.6f);
				}
			}
			fflush(stdout);
		}
	}
}

void GameManager::stage(int stagetime) //스테이지
{
	if (bstage == true)
		return;
	in_face.Setcolor(GREEN, DARKGRAY);
	in_face.BoxDraw(0, 0, m_iWith, m_iHeight);
	in_face.Setcolor(BLUE, DARKGRAY);
	in_face.gotoxy(m_iWith * 0.9f, m_iHeight *0.5f);
	cout << "☆ ★ " << m_istagenumber << " stage ★ ☆";
	if (clock() - stagetime >= 2000)
	{
		in_face.Setcolor(DARKGRAY, DARKGRAY);
		in_face.gotoxy(m_iWith * 0.9f, m_iHeight *0.5f);
		cout << "☆ ★ " << m_istagenumber << " stage ★ ☆";
		bstage = true;
	}
}
void GameManager::LevelUp(int& stagetime)
{
	if (Score == 1000 * m_istagenumber)//일정 점수를 달성하면
	{
		m_istagenumber++;
		bstage = false;
		ward.LevelUp(30);
		stagetime = clock();
	}
}
void GameManager::ScoreItem(int count)
{
	int score = 100;
	score *= count;
	Score += score;
}
void GameManager::reset()
{
	Score = 0;
	life = 9;
	Name = "? ? ?";
}
GameManager::~GameManager()
{
	if (m_bstory == true)
	{
		if (strStory != NULL)
		{
			delete[] strStory;
			strStory = NULL;
		}
	}
}
