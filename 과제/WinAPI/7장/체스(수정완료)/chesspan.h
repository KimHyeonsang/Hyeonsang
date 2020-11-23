#pragma once
#include"define.h"

class chesspan
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	SIZE m_size;
	RECT Rect;
public:
	chesspan();
	void Init(HWND hWnd,LPCWSTR FileName, int x, int y);
	void Draw(HDC hdc);
	inline int size_x()
	{
		return m_size.cx;
	}
	inline int size_y()
	{
		return m_size.cy;
	}
	inline RECT Rt()
	{
		return Rect;
	}
	inline int Rt_x()
	{
		return Rect.left;
	}
	inline int Rt_y()
	{
		return Rect.top;
	}
	~chesspan();
};

