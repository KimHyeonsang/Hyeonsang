#include "BITMAPCLASS.h"


BITMAPCLASS::BITMAPCLASS()
{
	m_HMemDC = NULL;
	m_inx = 0;
	m_iny = 0;
}

void BITMAPCLASS::Init(HDC hdc,HINSTANCE g_hInst,int bitmapnumber)
{
	m_HMemDC = CreateCompatibleDC(hdc);
	m_HmyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(bitmapnumber));//그림그리기
	m_HoldBitmap = (HBITMAP)SelectObject(m_HMemDC, m_HmyBitmap);//복사
}

void BITMAPCLASS::draw(HDC hdc)
{	
	if(m_inx != 0)
		StretchBlt(hdc, m_ix, m_iy, width, height, m_HMemDC, 0, 0, m_inx, m_iny, SRCCOPY);
	else
		BitBlt(hdc, m_ix, m_iy, width, height, m_HMemDC, 0, 0, SRCCOPY);//좌표설정 그리기	
}

void BITMAPCLASS::Information(int x, int y, int w, int h,string Name)
{
	m_ix = x;
	m_iy = y;
	width = w;
	height = h;
	name = Name;
}

void BITMAPCLASS::Information(int x, int y, int w, int h,int nx,int ny, string Name)
{
	m_ix = x;
	m_iy = y;
	width = w;
	height = h;
	m_inx = nx;
	m_iny = ny;
	name = Name;
}
BITMAPCLASS::~BITMAPCLASS()
{
	SelectObject(m_HMemDC, m_HoldBitmap);
	DeleteObject(m_HmyBitmap);
	DeleteDC(m_HMemDC);
}
