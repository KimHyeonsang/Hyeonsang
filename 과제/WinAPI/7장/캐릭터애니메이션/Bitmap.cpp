#include "Bitmap.h"

Bitmap* Bitmap::m_pThis = NULL;

Bitmap::Bitmap()
{
}

void Bitmap::Init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	MemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImage(NULL,TEXT("image.bmp"),IMAGE_BITMAP,0,0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	m_OldBitMap = (HBITMAP)SelectObject(MemDC, m_BitMap);

	BITMAP Bit_Info;

	GetObject(m_BitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;
}

void Bitmap::Draw(HDC hdc, int x,int y,int location)
{
	TransparentBlt(hdc, x, y, m_size.cx / 4, m_size.cy / 4,
		MemDC, (m_size.cx / 4) * m_iy, (m_size.cy / 4) * location, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
}
void Bitmap::location_y(int y)
{
	m_iy = y;
}
Bitmap::~Bitmap()
{
}
