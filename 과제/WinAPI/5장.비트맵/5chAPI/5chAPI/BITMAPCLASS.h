#pragma once
#include<Windows.h>
#include<iostream>
#include<vector>
#include"resource1.h"
using namespace std;

class BITMAPCLASS
{
private:
	HDC m_HMemDC;
	HBITMAP m_HmyBitmap;
	HBITMAP m_HoldBitmap;
	int width;
	int height;
	int m_ix;
	int m_iy;
	int m_inx;
	int m_iny;
	string name;
public:
	BITMAPCLASS();
	void Init(HDC hdc, HINSTANCE g_hInst,int bitmapnumber);
	void draw(HDC hdc);
	void Information(int x, int y, int w, int h,string Name);
	void Information(int x, int y, int w, int h,int nx,int ny,string Name);
	~BITMAPCLASS();
	int GetWidth() { return width; };
	int GetHeight() { return height; };
	string GetName() {return name;};
	int Getx() {return m_ix;};
	int Gety() {return m_iy;};
};
