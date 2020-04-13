#include "Game.h"



Game::Game()
{
}

void Game::mainMenu()//�޴�
{
	int select;
	while (1)
	{
		system("cls");
		map.gotoxy(WIDTH*0.5f, HEIGHT *0.2f);
		cout << "1. ���� ����";
		map.gotoxy(WIDTH*0.5f, HEIGHT *0.3f);
		cout << "2.����";
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
		if (map.GameOver() == true)//����
		{
			GameOver();
			ReSet();
			return;
		}
		if (player.Victory(boom.BoomNumber()) == true)//�̱涧
		{
			Victory();
			ReSet();
			return;
		}
	}
}
void Game::creatGame()//���� ������ ����
{
	system("cls");
	map.createOutBox();//�ܺκ�â��
	map.mapdraw();//�ʱ׸���
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
void Game::ReSet()//�÷��̾� ��ġ,�����ʱ�ȭ,
{
	boom.BoomReSet();//��ź �޸�����
	player.PlayerSet();//�÷��̾� �ʱ�ȭ
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
