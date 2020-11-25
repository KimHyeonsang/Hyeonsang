#include "DubleBuffering.h"

DubleBuffering* DubleBuffering::m_pThis = NULL;

DubleBuffering::DubleBuffering()
{
}

void DubleBuffering::Init(HDC hdc,HWND hWnd)
{
	g_MemDC[0] = CreateCompatibleDC(hdc);
	g_hBitMap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
	g_btOldBItMap[0] = (HBITMAP)SelectObject(g_MemDC[0], g_hBitMap[0]);


	g_MemDC[1] = CreateCompatibleDC(hdc);
	g_hBitMap[1] = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	g_btOldBItMap[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitMap[1]);

	g_MemDC[2] = CreateCompatibleDC(hdc);
	g_hBitMap[2] = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	g_btOldBItMap[2] = (HBITMAP)SelectObject(g_MemDC[2], g_hBitMap[2]);

	GetObject(g_hBitMap[1], sizeof(g_mapInfo), &g_mapInfo);

	g_size.cx = g_mapInfo.bmWidth;
	g_size.cy = g_mapInfo.bmHeight;
	ReleaseDC(hWnd, hdc);
}

void DubleBuffering::Draw(HDC Hdc)
{	
	StretchBlt(g_MemDC[0], 0, 0, 1024, 768, g_MemDC[2], 0, 0, 102, 768, SRCCOPY);
	TransparentBlt(g_MemDC[0], x, y, g_size.cx / 4, g_size.cy / 4, g_MemDC[1], (g_size.cx / 4) * walking, (g_size.cy / 4) * location, g_size.cx / 4, g_size.cy / 4, RGB(255, 0, 255));
	BitBlt(Hdc, 0, 0, 1024, 768, g_MemDC[0], 0, 0, SRCCOPY);
}

void DubleBuffering::move()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		walking++;
		if (walking == 4)
			walking = 0;

		location = 2;

		if (x <= 0)
			x = 0;
		else
			x -= 10;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		walking++;
		if (walking == 4)
			walking = 0;
		location = 3;

		if (x >= 960)
			x = 960;
		else
			x += 10;
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		walking++;
		if (walking == 4)
			walking = 0;
		location = 1;
		if (y <= 0)
			y = 0;
		else
			y -= 10;
		jump = y;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		walking++;
		if (walking == 4)
			walking = 0;
		location = 0;
		if (y >= 660)
			y = 660;
		else
			y += 10;
		jump = y;
	}
	if (jump <= y)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (location == 2 || location == 3)
			{
				walking = 0;
				y -= 40;
			}
			else
			{
				walking = 0;
				y -= 40;
			}
		}
	}
	else if (jump > y)
	{
		walking = 0;
		y += 3;
	}

}

DubleBuffering::~DubleBuffering()
{
}
