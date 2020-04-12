#pragma once
#include"macro.h"
#include"Mapdraw.h"
typedef struct Bomb
{
	int x;
	int y;
}BombList;

class Boom
{
private:
	int m_iBoomNumber;
	BombList* *m_bomlist;
public:
	Boom();
	void BoomSetting(Mapdraw* map);
	void BoomReSet();
	~Boom();
};

