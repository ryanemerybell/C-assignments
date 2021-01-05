#include <stdio.h>
#include <stdlib.h>
#include "ChessMoves.h"


void failwhale(void)
{
	printf("fail whale :(\n");
	exit(0);
}

int main(void)
{
	// Create a game board.
	char **board = createChessBoard();

	// Check that some of the pieces are in the correct positions.
	if (board[0][3] != 'Q')
		failwhale();
	if (board[7][4] != 'k')
		failwhale();
	if (board[6][7] != 'p')
		failwhale();
	if (board[4][7] != ' ')
		failwhale();

	printChessBoard(board);

	printf("Hooray!\n");

	return 0;
}
