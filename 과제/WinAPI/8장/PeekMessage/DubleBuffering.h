#pragma once
#include<Windows.h>

class DubleBuffering
{
private:
	static DubleBuffering* m_pThis;
	HDC g_MemDC[3];
	HBITMAP g_hBitMap[3];
	HBITMAP g_btOldBItMap[3];
	BITMAP g_mapInfo;
	SIZE g_size;
//	HDC hdc;
	int x = 300;
	int y = 500;
	int jump = 500;
	int location = 0;//»óÇÏÁÂ¿ì
	int walking = 0;//°È±â
public:
	DubleBuffering();
	static DubleBuffering* GetInstans()
	{
		if (m_pThis == NULL)
			m_pThis = new DubleBuffering;
		return m_pThis;
	}
	void Init(HDC hdc,HWND hWnd);
	void Draw(HDC Hdc);
	void move();
	~DubleBuffering();
};

