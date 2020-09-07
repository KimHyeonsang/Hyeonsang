#include"Mecro.h"
#include"MapDraw.h"
#include"GameManager.h"
#include"Player.h"

void mainview(GameManager* main, GameManager* chacter)
{
	GameManager* DGGM = new DanganMenuManager();
	GameManager* SHOPGM = new ShopMenuManager();
	DGGM->Initialized();
	SHOPGM->Initialized();
	while (1)
	{
		bool batteselect = true;
		bool shop = true;
		main->Menu();
		switch (main->mapSelect(7, 2, WIDTH * 0.35f, HEIGHT*0.38f))
		{
		case 1:
			while (batteselect)
			{
				DGGM->Menu();
				chacter->Dangan(batteselect);
				batteselect = chacter->Battle();
			}
			break;
		case 2:
			chacter->Playinfo();
			break;
		case 3:
			chacter->Monsterinfo();
			break;
		case 4:
			while (shop)
			{
				SHOPGM->Menu();
				chacter->weaponShop();
				shop = chacter->Shop();
			}
			break;
		case 5:
			chacter->playerinveninfo();
			break;
		case 6:
			chacter->LoadSave();
			break;
		case 7:
			return;
		}
	}
}

void main()
{
	GameManager* GM1 =new firstMenu();
	GameManager* GM = new JobManager();
	GameManager* mainGM = new MainMenuManager();
	Player* player = new Knight();
	GM->Initialized();
	GM1->Initialized();
	mainGM->Initialized();
	srand(time(NULL));
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", WIDTH + 1, HEIGHT * 2);
	system(buf);
	int Select;
	
	while (1)
	{		
		GM1->Menu();
		switch (GM1->mapSelect(3, 3, (WIDTH - strlen("Game Exit") / 2 - 3) / 2, HEIGHT* 0.4 + 3))
		{
		case 1: //만약 새로운 게임이면 기본능력치 부여
			GM->Menu();
			GM->SelectJob();
			mainview(mainGM,GM);
			break;
		case 2:
			GM->Loadfile(true);
			GM->LoadSave();
			if (GM->Load() == false)
				mainview(mainGM,GM);
			break;
		case 3:
			return;
		}
	}
}