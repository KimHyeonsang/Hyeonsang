#pragma once
#include"mecro.h"
#include"BackGround.h"
#include"Character.h"
#include"obstacle.h"

#define MAX 20
class GameManager
{
private:
	HDC hdc;
	HDC m_hBackBuffer;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitMap;
	HWND m_hWnd;
	static GameManager* m_This;
	Ground* m_ground;
	crowd* m_Crowd[MAX];
	Elephant* m_elephant[2];
	Character* character;
	Miter* m_miter;
	jar* m_jar;
	EndBox* m_EndBox;
	LeftFirering* m_leftring[2];
	RightFirering* m_rightring[2];

	MoneyFirering* m_MoneyFirering;
	MoneyleftFirering* m_MoneyleftFirering;
	MoneyrightFirering* m_MoneyrightFirering;
	RECT rt;
	bool m_bcrash;
	int m_icount;

	int m_iScore;
	int m_irandem;
	char m_charMiter[128];
	State m_state;

	DWORD		m_dwLastTime;
	DWORD		m_dwCurTime;
	float		m_fDeltaTime;
public:
	static GameManager* GetInstance()
	{
		if (m_This == NULL)
			m_This = new GameManager;
		return m_This;
	}
	void Init(HWND hWnd);
	void Render();
	void Update();
	void crash();
	void Score();
	void replay();
	GameManager();
	~GameManager();
};

