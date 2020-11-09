#pragma once
#include"chess.h"
#include"chesspan.h"
#include"define.h"
using namespace std;
//판 ,킹 ,비숍 룩 나이트 폰 등록
class chessManager
{
private:
	chess* makechess;
	vector<chess*>Chess_piece;
	vector<chess*>::iterator Chess_piece_iter;
	int m_ix;
	int m_iy;
	char m_cteam;

	chess* temporary_makechess;
	vector<chess*>temporary_Chess_piece;
	vector<chess*>::iterator temporary_Chess_piece_iter;

	chess* m_Enemy;
	chess* m_EnemyKing;
	vector<chess*>::iterator m_Enemy_Chess_piece_iter;
public:
	chessManager(char team);
	void Init(HWND hWnd,int x,int y);
	void Draw(HDC hdc);
	bool MoveCheck(POINT pt, vector<chess*> v);//이동이 되는지 체크를 한다.
	void ChessSelect(POINT pt);//무슨말을 클릭한지 확인한다.
	bool Move(POINT pt, int Team, vector<chess*>*enemy);//이동을한다
	void temporaryDelete();
	vector<chess*> Attack();
	bool check(chesspan* pan);
	void DeleteChess(POINT pt, HWND hWnd);
	vector<chess*> Vector();
	void checkmate(vector<chess*>*enemy, HWND hWnd);
	void promotion(HWND hWnd,int y);
	inline int size()
	{
		return temporary_Chess_piece.size();
	}
	
	~chessManager();
};

