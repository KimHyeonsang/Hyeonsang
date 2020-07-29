#pragma once
#include"macro.h"
#include"Ward.h"
#include<string>
class GameManager;
class WardManager
{
private:
	int m_iWardnumber;
	Ward* ward;
	string strWard;
	int startward;
	bool m_bspeedchange;
	bool m_bspeedstop;
	bool m_bclear;
	bool m_bwardblind;
	int m_inumber;
	int itemtme;
	int Scorecount;
	list<Ward*> List;
	list<Ward*>::iterator iter;
	GameManager* GM;
public:
	void SettingWard();
	void dropward();
	bool Dies(int Height, string str, GameManager* game);
	void wardLive(int Height);
	void LevelUp(int number);
	bool lifeless(int height);
	void reset();
	void ActivateItemEffect(WARDEFFET Effet, GameManager* game);
	void ItemEffectOff(WARDEFFET Effet);
	void reitem(bool& bEffect);
	inline bool blind()
	{
		return m_bwardblind;
	}
	WardManager();
	~WardManager();
};

