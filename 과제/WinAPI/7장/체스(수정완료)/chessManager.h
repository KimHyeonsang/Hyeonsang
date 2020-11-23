#pragma once
#include"chess.h"
#include"chesspan.h"
#include"define.h"
using namespace std;
//�� ,ŷ ,��� �� ����Ʈ �� ���
class chessManager
{
private:
	HDC m_hdc;
	chess* makechess;
	vector<chess*>Chess_piece;
	vector<chess*>::iterator Chess_piece_iter;
	int m_ix;
	int m_iy;
	char m_cteam;

	chess* temporary_makechess;
	Phawn* temporary_chess;
	vector<chess*>temporary_Chess_piece;
	vector<chess*>::iterator temporary_Chess_piece_iter;

	chess* m_Enemy;
	chess* m_EnemyKing;
	vector<chess*>::iterator m_Enemy_Chess_piece_iter;

	chess* ChessPick;
	vector<chess*>temporary_Chess_pick;
public:
	chessManager(char team);
	void Init(HWND hWnd,int x,int y);
	void Draw(HDC hdc);
	bool MoveCheck(RECT rt, vector<chess*> v,int Team);//�̵��� �Ǵ��� üũ�� �Ѵ�.
	void ChessSelect(POINT pt);//�������� Ŭ������ Ȯ���Ѵ�.
	void Move(POINT pt, int Team, vector<chess*>*enemy);//�̵����Ѵ�
	void temporaryDelete();
	vector<chess*> Attack();
	bool check(chesspan* pan);
	void DeleteChess(POINT pt, HWND hWnd);
	vector<chess*> Vector();
	void checkmate(vector<chess*>*enemy, HWND hWnd, int Team);
	void promotion(HWND hWnd,int y);
	inline int size()
	{
		return temporary_Chess_piece.size();
	}
	
	~chessManager();
};

