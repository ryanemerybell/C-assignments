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
	Move whiteMove;
	Move blackMove;

	// With this test case, I'm checking whether your parseNotationString()
	// function correctly parses through a string of algebraic chess notation.
	// This test case is also designed to help show you exactly which fields
	// should be set, and how they should be set, when parsing these strings.

	parseNotationString("18. R4xe4 h6", &whiteMove, &blackMove);

	// Check that whiteMove has been properly initialized.
	if (whiteMove.from_loc.col != 'x' || whiteMove.from_loc.row != 4)
		failwhale();
	if (whiteMove.to_loc.col != 'e' || whiteMove.to_loc.row != 4)
		failwhale();
	if (whiteMove.piece != 'R' || whiteMove.isCapture != 1 || whiteMove.color != WHITE)
		failwhale();

	// Check that blackMove has been properly initialized.
	if (blackMove.from_loc.col != 'x' || blackMove.from_loc.row != -1)
		failwhale();
	if (blackMove.to_loc.col != 'h' || blackMove.to_loc.row != 6)
		failwhale();
	if (blackMove.piece != 'P' || blackMove.isCapture != 0 || blackMove.color != BLACK)
		failwhale();

	printf("Hooray!\n");

	return 0;
}
