#pragma once
#include"Bitmap.h"
#include<Windows.h>
#include<vector>
#include<cstdlib>
#include<time.h>
#include<iostream>
using namespace std;

class GameManager
{
private:
	static GameManager* m_pThis;	
	vector<Bitmap*> m_v; //전체 카드
	Bitmap* m_btmap;
	vector<Bitmap*>::iterator iter;

	vector<Bitmap*> m_vClose;
	Bitmap* m_btmapclose;
	vector<Bitmap*>::iterator close; //앞면

	vector<Bitmap*> m_vOpen;
	Bitmap* m_btmapOpen;
	vector<Bitmap*>::iterator open; //앞면

	vector<Bitmap*> m_vtemporaryOpen;
	int m_ix;
	int m_iy;
public:
	static GameManager* GetInstans()
	{
		if (m_pThis == NULL)
			m_pThis = new GameManager;
		return m_pThis;
	}
	GameManager();
	~GameManager();
	void Init(HWND hWnd, HINSTANCE h_Inst);
	void BakcInit(HWND hWnd, HINSTANCE h_Inst);
	int Random();
	void Click(int x,int y, HWND hWnd);
	void ClickCheck(HWND hWnd);
	void Draw(HDC hdc);
	void victory(HWND hWnd);
	void TimeCheck();
	void Release();
};

