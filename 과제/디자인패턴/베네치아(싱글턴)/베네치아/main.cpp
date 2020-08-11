#include"macro.h"
#include"GameManager.h"
#include"Interface.h"
#include"Rank.h"
#include<crtdbg.h>


void main()
{
	//_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_crtBreakAlloc = 739;
	Interface in_face;
	Rank rank;
	int Width = WIDTH;
	int Height = HEIGHT;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height + 4, Width * 2);
	system(buf);
	bool gameover = true;
	while (gameover)
	{
		in_face.Setcolor(GREEN, DARKGRAY);
		in_face.BoxDraw(0, 0, Width, Height); //테두리
		in_face.Setcolor(BLUE, DARKGRAY);
		in_face.DrawMidText("☆ ★ 베 네 치 아 ★  ☆", Width, Height * 0.2f);
		in_face.DrawMidText("1. Game Start", Width, Height * 0.4f);
		in_face.DrawMidText("2. Rank", Width, Height * 0.4f + 3);
		in_face.DrawMidText("3. Exit", Width, Height * 0.4f + 6);
		GameManager::GetInstance()->underinterface();
		switch (in_face.MenuSelectCursor(3, 3, Width *0.4f, Height * 0.4f))
		{
		case MAINSELECT_GAMESTART:
			GameManager::GetInstance()->story_setName();
			GameManager::GetInstance()->gostory();
			GameManager::GetInstance()->SetName();
			GameManager::GetInstance()->Play();
			GameManager::GetInstance()->reset();
			break;
		case MAINSELECT_RANK:
			rank.Ranking();
			rank.Rankingsystem(Width, Height);
			break;
		case MAINSELECT_EXIT:
			gameover = false;
			break;
		}
	}
}