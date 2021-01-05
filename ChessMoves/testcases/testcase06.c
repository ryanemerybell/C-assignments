#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ChessMoves.h"


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

	strncpy(row8, "RNBQKBNR", 8);
	strncpy(row7, "PPP   PP", 8);
	strncpy(row6, "        ", 8);
	strncpy(row5, "   PPP  ", 8);
	strncpy(row4, "   ppp  ", 8);
	strncpy(row3, "       p", 8);
	strncpy(row2, "ppp   p ", 8);
	strncpy(row1, "rnbqkbnr", 8);

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
	//   "18. a3 Pfxe4"

	move.to_loc.col = 'e';
	move.to_loc.row = 4;
	move.from_loc.col = 'f';
	move.from_loc.row = -1;
	move.piece = 'P';
	move.isCapture = 1;
	move.color = BLACK;

	printTestCaseBoard(board);

	movePiece(board, &move);

	printTestCaseBoard(board);

	printf(":)\n");

	return 0;
}
