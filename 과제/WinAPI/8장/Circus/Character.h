#pragma once
#include"mecro.h"
#define PIE 3.141592f
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

	SIZE m_size;
	int m_iHartcount;

	SIZE m_Winsize;
	BITMAP m_bitWin;

	SIZE m_hart;
	BITMAP m_bithart;
	RECT m_rect;

	SIZE m_Diesize;
	BITMAP m_bitdie;

	int m_iJumPower;
	int m_ibefore_x;//이전 x좌표
	DWORD		m_dwLastTime;
	DWORD		m_dwCurTime;
	float		m_fDeltaTime;
public:
	Character();
	void Init(HWND hWnd,HDC _m_hBuffer);
	void Render(HDC _m_hBackBuffer);
	void Update(float time,int miter);
	void PlayerKey(float time,int miter);
	void hartbreaker();
	void endlocation();
	void replay();
	void DamageMotion();
	inline RECT characterlocation()
	{
		return m_rect;
	}
	inline Direction direction()
	{
		return m_Direction;
	}
	inline State state()
	{
		return m_state;
	}
	inline int hartcount()
	{
		return m_iHartcount;
	}
	~Character();
};

