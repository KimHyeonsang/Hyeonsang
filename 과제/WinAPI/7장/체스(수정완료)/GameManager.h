#pragma once
#include"define.h"
#include"chessManager.h"
#include"chesspan.h"
//��� �۵��� ���⼭ �Ͼ�� ���� �ȴ� ��� �� ������.
class GameManager
{
private:
	static GameManager* m_pThis;
	chessManager* chess[CHESSPAN_END];
	chesspan* pan;
	vector<chesspan*> ChessPan;
	vector<chesspan*>::iterator ChessPan_iter;

	chesspan* PickPan;
	vector<chesspan*> ChessPanPick;

	int m_ix;
	int m_iy;
	int m_iplayer;
public:
	GameManager();
	static GameManager* GeInstans()
	{
		if (m_pThis == NULL)
			m_pThis = new GameManager;
		return m_pThis;
	}
	void Init(HWND hWnd);
	void Draw(HDC hdc);
	bool ChessCheck(POINT pt, HWND hWnd);
	void checkmate(HWND hWnd,int Team);
	void promotion(HWND hWnd);
	void Play(POINT pt, HWND hWnd);
	void SelectPick(RECT pickpan,HWND hWnd);
	~GameManager();
};

