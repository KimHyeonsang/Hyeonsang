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
		cout << "1. ���� ����" << endl;
		cout << "2.����" << endl;
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
		if (player.Victory() == true)//�̱涧
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
	map.Restboard();
}

Game::~Game()
{
}
