#pragma once
#include"mecro.h"

class Character
{
private:
	float m_MoveSpeed;//움직이는속도
	HWND m_hWnd;
	HDC m_hBackBuffer[7];
	HBITMAP m_BitMap[7];
	HBITMAP m_OldBitMap[7];
	State m_state;
	Direction m_Direction;
	bool m_bJumpcheck;

	SIZE m_size;
	int m_iHartcount;
	int m_ibefore_y;

	SIZE m_Winsize;
	BITMAP m_bitWin;

	SIZE m_hart;
	BITMAP m_bithart;
	RECT m_rect;

	SIZE m_Diesize;
	BITMAP m_bitdie;
public:
	Character();
	void Init(HWND hWnd,HDC _m_hBuffer);
	void Render(HDC _m_hBackBuffer);
	void Update();
	void PlayerKey();
	void hartbreaker();
	void endlocation(RECT rt);
	void replay();
	inline RECT characterlocation()
	{
		return m_rect;
	}
	inline Direction direction()
	{
		return m_Direction;
	}
	inline int hartcount()
	{
		return m_iHartcount;
	}
	~Character();
};

