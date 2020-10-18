#include "Bitmap.h"
#include"resource.h"


Bitmap::Bitmap()
{
}
void Bitmap::Init(HDC hdc, HINSTANCE hInst,int x,int y, int imagenumber)
{
	MemDC = CreateCompatibleDC(hdc);
	m_pMyBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(imagenumber));
	m_pOldBitMap = (HBITMAP)SelectObject(MemDC, m_pMyBitMap);

	BITMAP Bit_Info;

	GetObject(m_pMyBitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;

	m_ix = x;
	m_iy = y;
	animal = (ANIMAL)imagenumber;
}
void Bitmap::Draw(HDC hdc, int spX, int spY)
{
	BitBlt(hdc, m_ix, m_iy, m_size.cx, m_size.cy, MemDC, 0, 0, SRCCOPY);

}
void Bitmap::CardCHange()
{

}
Bitmap::~Bitmap()
{
}
