#pragma once
#include"macro.h"
#include"Mapdraw.h"
#include"Player.h"
#include"Boom.h"

enum SELECT
{
	SELECT_START = 1,
	SELECT_END
};
class Game
{
private:
	Mapdraw map;
	Player player;
	Boom boom;
public:
	void mainMenu();
	void Play();
	void creatGame();
	void GameOver();
	void Victory();
	void ReSet();
	void HelpKey();
	Game();
	~Game();
};

