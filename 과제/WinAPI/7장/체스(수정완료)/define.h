#pragma once
#include<Windows.h>
#include<vector>
#include<string>
#include<time.h>
using namespace std;

enum CHESSPAN
{
	CHESSPAN_BLACK,
	CHESSPAN_WHITE,
	CHESSPAN_END
};

enum MOVEING
{
	MOVEING_STOP,
	MOVEING_GO
};

enum CHESSRANK
{
	CHESSRANK_PHAWN,
	CHESSRANK_KNIGHT,
	CHESSRANK_BISHOP,
	CHESSRANK_ROOK,
	CHESSRANK_QUEEN,
	CHESSRANK_KING,
};