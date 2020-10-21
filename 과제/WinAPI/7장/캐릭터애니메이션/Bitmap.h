#pragma once
#include<Windows.h>

class Bitmap
{
private:
	static Bitmap* m_pThis;
	HDC MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	SIZE m_size;

	int m_iy;
public:
	Bitmap(); 
	static Bitmap* GeInstans()
	{
		if (m_pThis == NULL)
			m_pThis = new Bitmap;
		return m_pThis;
	}
	void Init(HWND hWnd);
	void Draw(HDC hdc,int x);
	void a(int y);
	~Bitmap();
};

