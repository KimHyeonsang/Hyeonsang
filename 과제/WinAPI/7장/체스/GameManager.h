#pragma once
#include"define.h"
#include"chessManager.h"
#include"chesspan.h"
//모든 작동은 여기서 일어난다 보면 된다 흑과 백 나누기.
class GameManager
{
private:
	static GameManager* m_pThis;
	chessManager* chess[CHESSPAN_END];
	chesspan* pan;
	vector<chesspan*> ChessPan;
	vector<chesspan*>::iterator ChessPan_iter;

	int m_ix;
	int m_iy;
	int m_iplayer;
	bool m_bChessCheck;
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
	void ChessCheck(POINT pt, HWND hWnd);
	void Move(POINT pt, HWND hWnd);
	void checkmate(HWND hWnd);
	void promotion(HWND hWnd);
	~GameManager();
};

