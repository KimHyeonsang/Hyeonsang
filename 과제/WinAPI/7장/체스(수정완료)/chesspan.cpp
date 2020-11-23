#include "chesspan.h"



chesspan::chesspan()
{
}
void chesspan::Init(HWND hWnd, LPCWSTR FileName, int x, int y)
{
	HDC hdc = GetDC(hWnd);
	MemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitMap = (HBITMAP)SelectObject(MemDC, m_BitMap);

	BITMAP Bit_Info;

	GetObject(m_BitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;

	Rect.left = x;
	Rect.top = y;
	Rect.right = x + m_size.cx;
	Rect.bottom = y + m_size.cy;
}

void chesspan::Draw(HDC hdc)
{
	TransparentBlt(hdc, Rect.left, Rect.top, m_size.cx, m_size.cy,
		MemDC, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
}

chesspan::~chesspan()
{
}
