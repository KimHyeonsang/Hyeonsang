#include "Game.h"



Game::Game()
{
}

void Game::mainMenu()//메뉴
{
	int select;
	while (1)
	{
		system("cls");
		map.gotoxy(WIDTH*0.5f, HEIGHT *0.2f);
		cout << "1. 게임 시작";
		map.gotoxy(WIDTH*0.5f, HEIGHT *0.3f);
		cout << "2.종료";
		map.gotoxy(WIDTH*0.5f, HEIGHT *0.4f);
		cin >> select;
		switch (select)
		{
		case SELECT_START:
			creatGame();
			Play();
			break;
		case SELECT_END:
			return;
		}
	}
}
void Game::Play()
{
	while (1)
	{
		player.MovePlayer(&map);
		if (map.GameOver() == true)//질때
		{
			GameOver();
			ReSet();
			return;
		}
		if (player.Victory(boom.BoomNumber()) == true)//이길때
		{
			Victory();
			ReSet();
			return;
		}
	}
}
void Game::creatGame()//게임 실행전 셋팅
{
	system("cls");
	map.createOutBox();//외부벽창조
	map.mapdraw();//맵그리기
	boom.BoomSetting(&map);
	map.counttingBoom();
	HelpKey();
}
void Game::GameOver()
{
	system("cls");
	map.gotoxy(WIDTH, HEIGHT / 2);
	cout << "GAME OVER";
	system("pause>null");
}
void Game::Victory()
{
	system("cls");
	map.gotoxy(WIDTH, HEIGHT / 2);
	cout << "Victory";
	system("pause>null");
}
void Game::ReSet()//플레이어 위치,지뢰초기화,
{
	boom.BoomReSet();//폭탄 메모리해제
	player.PlayerSet();//플레이어 초기화
	map.Resetboard();
}
void Game::HelpKey()
{
	map.gotoxy(0, HEIGHT);
	cout << "Left : a ,Right: d, Up : w,Down : s";
	map.gotoxy(0, HEIGHT + 1);
	cout << "Open Box : Enter";
}
Game::~Game()
{
}
