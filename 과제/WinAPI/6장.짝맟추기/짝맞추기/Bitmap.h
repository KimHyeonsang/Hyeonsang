#pragma once
#include<Windows.h>

enum ANIMAL
{
	ANIMAL_DOG =101,
	ANIMAL_TIGER,
	ANIMAL_DUCK,
	ANIMAL_ELEPHANT,
	ANIMAL_COW,
	ANIMAL_HORSE,
	ANIMAL_CAT,
	ANIMAL_MONKEY,
	ANIMAL_FROG,
	ANIMAL_CHICKEN
};

class Bitmap
{
private:
	HDC		MemDC;
	HBITMAP	m_pMyBitMap;
	HBITMAP	m_pOldBitMap;
	SIZE	m_size;
	int m_ix;
	int m_iy;
	
	enum ANIMAL animal;
public:
	Bitmap();
	void Init(HDC hdc, HINSTANCE hInst,int x,int y,int imagenumber);
	void Draw(HDC hdc, int spX = 1, int spY = 1);
	void CardCHange();
	inline int Animal()
	{
		return animal;
	}
	inline int Getx()
	{
		return m_ix;
	}
	inline int Gety()
	{
		return m_iy;
	}
	inline int GetWIDH()
	{
		return m_size.cx;
	}
	inline int GetHeight()
	{
		return m_size.cy;
	}
	~Bitmap();
};

