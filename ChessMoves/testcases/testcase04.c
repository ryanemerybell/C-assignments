#include <stdio.h>
#include <stdlib.h>
#include "ChessMoves.h"


void failwhale(void)
{
	printf("fail whale :(\n");
	exit(0);
}

void printBar(void)
{
	int i;
	for (i = 0; i < 8; i++)
		printf("=");
	printf("\n");
}

void printTestCaseBoard(char **board)
{
	int i, j;

	printBar();

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

	printBar();

	if (board[5][5] != 'n' || board[7][6] != ' ')
		failwhale();

	if (board[4][4] != 'p' || board[6][4] != ' ')
		failwhale();

	if (board[3][1] != 'b' || board[7][5] != ' ')
		failwhale();

	printf("\nHooray!\n");
}

int main(void)
{
	Move move;
	char **board = createChessBoard();

	// With this test case, I'm checking whether your movePiece() function
	// correctly moves a piece based on a Move that I know has been properly
	// initialized. (This is to ensure that you don't initialize Move structs
	// incorrectly in your program and then write a movePiece() function that
	// only works with that incorrect struct initialization.)

	// This test case will also help ensure that your movePiece() function does
	// not output the board to the screen. If it does, this program will print
	// the board twice after each move (instead of just once), which is not the
	// expected result.

	move.to_loc.col = 'f';
	move.to_loc.row = 3;
	move.from_loc.col = 'x';
	move.from_loc.row = -1;
	move.piece = 'N';
	move.isCapture = 0;
	move.color = WHITE;

	movePiece(board, &move);

	// Technically, this would be a legal move given this particular board
	// configuration. We would never encounter this situation in a real game,
	// though, because White never moves twice in a row without Black making a
	// move.

	move.to_loc.col = 'e';
	move.to_loc.row = 4;
	move.from_loc.col = 'x';
	move.from_loc.row = -1;
	move.piece = 'P';
	move.isCapture = 0;
	move.color = WHITE;

	movePiece(board, &move);

	move.to_loc.col = 'b';
	move.to_loc.row = 5;
	move.from_loc.col = 'x';
	move.from_loc.row = -1;
	move.piece = 'B';
	move.isCapture = 0;
	move.color = WHITE;

	movePiece(board, &move);

	printTestCaseBoard(board);

	// This program has a nasty memory leak, but I don't want to call your
	// destroyBoard() function in case it's broken. I want this test case's
	// success to be based entirely on your movePiece() function, and no other
	// functions.

	return 0;
}
