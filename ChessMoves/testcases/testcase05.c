#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	printf("\n");
}

int main(void)
{
	Move move;

	// This is a statically allocated board. Don't use this method. Yours needs
	// to be dynamically allocated.

	char row8[8];
	char row7[8];
	char row6[8];
	char row5[8];
	char row4[8];
	char row3[8];
	char row2[8];
	char row1[8];

	char **board = malloc(sizeof(char *) * 8);

	// This is terrible. I'm really going out of my way not to fully dynamically
	// allocate a 2D array here.

	strncpy(row8, " NBQKBNR", 8);
	strncpy(row7, " PPPPPPP", 8);
	strncpy(row6, "    R   ", 8);
	strncpy(row5, "P       ", 8);
	strncpy(row4, "       p", 8);
	strncpy(row3, "    r   ", 8);
	strncpy(row2, "ppppppp ", 8);
	strncpy(row1, "rnbqkbn ", 8);

	board[0] = row8;
	board[1] = row7;
	board[2] = row6;
	board[3] = row5;
	board[4] = row4;
	board[5] = row3;
	board[6] = row2;
	board[7] = row1;


	// With this test case, I'm checking whether your findFromLoc() function
	// correctly finds the location of a chess piece that is making an attack,
	// when part of that piece's location has already been extracted from the
	// algebraic chess notation string.

	// A move like this could be extracted from a string such as:
	//
	//   "18. Re5 h6"

	// Here I'm testing your findFromLoc() function directly.

	move.to_loc.col = 'e';
	move.to_loc.row = 5;
	move.from_loc.col = 'x';
	move.from_loc.row = -1;
	move.piece = 'R';
	move.isCapture = 0;
	move.color = WHITE;

	findFromLoc(board, &move);

	if (move.to_loc.col != 'e' || move.to_loc.row != 5)
		failwhale();
	if (move.from_loc.col != 'e' || move.from_loc.row != 3)
		failwhale();
	if (move.piece != 'R' || move.isCapture != 0 || move.color != WHITE)
		failwhale();

	// Here, I'm resetting the move (stripping away the from_loc) and checking
	// whether your movePiece() function is working. movePiece() should be
	// calling findFromLoc(); it should not expect that the fromLoc() is filled
	// in already (unless there was a from_loc speficied in the algebraic
	// notation string).

	move.to_loc.col = 'e';
	move.to_loc.row = 5;
	move.from_loc.col = 'x';
	move.from_loc.row = -1;
	move.piece = 'R';
	move.isCapture = 0;
	move.color = WHITE;

	printTestCaseBoard(board);

	movePiece(board, &move);

	printTestCaseBoard(board);

	printf(":)\n");

	return 0;
}
